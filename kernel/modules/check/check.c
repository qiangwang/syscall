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

typedef void (*check_handler) (void);
/*extern check_handler do_check;*/
extern unsigned long do_check;

static void real_do_check(void){
    printk("doing check...\n");
}

static int __init check_init(void){
    printk("place check handler...\n");
    do_check = (unsigned long)real_do_check;
    printk("ok.\n");
    return 0;
}

static void __exit check_exit(void){
    do_check = 0;
    printk("check exit.\n");
}

module_init(check_init);
module_exit(check_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("XYS");
