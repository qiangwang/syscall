#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>
#include <asm/unistd.h>
#include <linux/syscalls.h>

MODULE_LICENSE("GPL");

extern int handler_switch;

static int __init syscall_init(void){
    printk("syscall init.\n");
    
   handler_switch = 1; 
    return 0;
}

static void __exit syscall_exit(void){
    
   handler_switch = 0; 

    printk("syscall exit.");
}

module_init(syscall_init);
module_exit(syscall_exit);
