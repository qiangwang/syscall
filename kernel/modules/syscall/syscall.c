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

#define LOG_FILE "/var/log/syscall/syscall.log"
#define MAX_WHITE 10

static struct file *log;

extern unsigned long syscall_id;
extern unsigned long syscall_pre_handler;
static unsigned long old_handler;

typedef void (*check_handler) (void);
unsigned long do_check;
EXPORT_SYMBOL(do_check);    

static int white_pids[MAX_WHITE] = {0};
static int white_uids[MAX_WHITE] = {0};
static char *white_comms[MAX_WHITE] = {"mysql","mysqld","nginx"};

static int is_white(void){
    int i;

    for(i=0; white_uids[i] != 0; i++){
        if(current->cred->uid == white_uids[i]){
            return 1;
        }
    }
   
    for(i=0; white_comms[i]!=NULL; i++){
        if(strcasecmp(current->comm, white_comms[i]) == 0 
                || 
                strcasecmp(current->parent->comm, white_comms[i]) == 0){
            return 1;
        }
    }

    return 0;
}

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

MODULE_LICENSE("GPL");
MODULE_AUTHOR("XYS");
