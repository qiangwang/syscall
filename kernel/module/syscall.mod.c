#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

MODULE_INFO(vermagic, VERMAGIC_STRING);

struct module __this_module
__attribute__((section(".gnu.linkonce.this_module"))) = {
 .name = KBUILD_MODNAME,
 .init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
 .exit = cleanup_module,
#endif
 .arch = MODULE_ARCH_INIT,
};

static const struct modversion_info ____versions[]
__used
__attribute__((section("__versions"))) = {
	{ 0x218802da, "module_layout" },
	{ 0xd22b39b, "filp_close" },
	{ 0xe8357875, "syscall_pre_handler" },
	{ 0x157f3841, "filp_open" },
	{ 0x50eedeb8, "printk" },
	{ 0xd0d8621b, "strlen" },
	{ 0x3c2c5af5, "sprintf" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x2b1992af, "current_task" },
	{ 0xd777ceae, "syscall_id" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "60E88AC1735A6FEB2739E2D");
