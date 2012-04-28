#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h> //current
#include <asm/unistd.h>
#include <linux/syscalls.h> 
#include <asm/uaccess.h> //get_ds,set_fs,get_fs
#include <linux/stat.h>
#include <linux/fs.h>
#include <linux/types.h>
#include <linux/ioctl.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");

#define LOG_FILE "/var/log/syscall/syscall.log"

extern unsigned long syscall_id;

extern unsigned long syscall_pre_handler;
static unsigned long old_handler;
    
static struct file *log;

int black_calls[10] = {265,119,240};
char *black_comms[10] = {};
/*{
    "Xorg","chrome","Chrome_ChildIOT","Chrome_IOThread","Chrome_CacheThr",
    "gnome-terminal","gnome-shell"
};
*/
static void new_pre_handler(void){
    mm_segment_t old_fs;
    char buf[32];
    int i;

    for(i=0;black_calls[i]!=0;i++){
        if(syscall_id == black_calls[i]) return;
    }

    for(i=0;black_comms[i]!=NULL;i++){
        if(strcmp(current->comm, black_comms[i]) == 0) return;
    }

    old_fs = get_fs();
    set_fs(get_ds());

    sprintf(buf, "%lu,%d,%s\n", syscall_id, current->pid, current->comm);

    log->f_op->write(log, buf, strlen(buf), &log->f_pos);

    set_fs(old_fs);
}

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

static void __exit syscall_exit(void){
    printk("place old handler...\n");
    syscall_pre_handler = old_handler;

    printk("close log file...\n");
    filp_close(log, NULL);

    printk("syscall exit.\n");
}

module_init(syscall_init);
module_exit(syscall_exit);
