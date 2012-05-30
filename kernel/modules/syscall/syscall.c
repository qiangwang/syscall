#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h> //current
#include <asm/unistd.h>
#include <asm/uaccess.h> //get_ds,set_fs,get_fs
#include <linux/stat.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/ioctl.h>
#include <linux/string.h>

/*日志文件*/
#define LOG_FILE "/var/log/syscall/syscall.log"
#define MAX_WHITE 10

static struct file *log;

/*系统调用号*/
extern unsigned long syscall_id;
/*钩子函数*/
extern unsigned long syscall_pre_handler;
/*保存原来的处理函数*/
static unsigned long old_handler;

/*将检测集成进内核*/
typedef void (*check_handler) (void);
unsigned long do_check;
EXPORT_SYMBOL(do_check);    

/*待测进程ID*/
static int pids[MAX_WHITE];
static int nr_pid;
module_param_array(pids, int, &nr_pid, 0644);

/*待测进程comm*/
static char *comms[MAX_WHITE];
static int nr_comm;
module_param_array(comms, charp, &nr_comm, 0644);

/*
 * 如果进程的pid在pids数组中或
 * 进程的comm在comms数组中
 * 则会记录其调用序列，否则跳过
 * */
static int is_white(void){
    int i;

    for(i=0; i < nr_pid ; i++){
        if(current->pid == pids[i]){
            return 1;
        }
    }
   
    for(i=0; i < nr_comm ; i++){
        if(strcmp(current->comm, comms[i]) == 0){
            return 1;
        }
    }

    return 0;
}

/*
 *钩子函数的实现
 *
 * 1.判断当前进程是否需要处理
 * 2.扩展内核模块访问文件空间的范围
 * 3.记录调用到日志文件
 * 4.恢复文件系统访问空间
 * 5.检查并执行检测算法
 * 
 * */
static void new_pre_handler(void){
    mm_segment_t old_fs;
    char buf[32];

    /* handle it ?*/
    if(!is_white()) return;

    /* record */
    old_fs = get_fs();
    set_fs(get_ds());

    sprintf(buf, "%lu/%d/%s\n", syscall_id, current->pid, current->comm);

    log->f_op->write(log, buf, strlen(buf), &log->f_pos);

    set_fs(old_fs);

    /* check */
    if(do_check) ((check_handler)do_check)();
}

/*
 *模块初始化
 * 
 * 1.打开日志文件
 * 2.替换钩子函数
 * 3.保存原来的处理函数
 *
 * */
static int __init syscall_init(void){

    printk("syscall init.\n");

    printk("opening log file...\n");
    
    log = filp_open(LOG_FILE, O_CREAT|O_WRONLY|O_APPEND, 0644);
    if(IS_ERR(log)) {
        printk("Fail,exit.\n");
        return -1;
    }
   
    printk("place new handler...\n");
    old_handler = syscall_pre_handler;
    syscall_pre_handler = (unsigned long)new_pre_handler;

    printk("ok.\n");

    return 0;
}

/*
 *模块卸载
 *
 * 1.恢复处理函数
 * 2.关闭日志文件
 *
 * */
static void __exit syscall_exit(void){
    printk("place old handler...\n");
    syscall_pre_handler = old_handler;

    printk("close log file...\n");
    filp_close(log, NULL);

    printk("syscall exit.\n");
}

module_init(syscall_init);
module_exit(syscall_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("XYS");
