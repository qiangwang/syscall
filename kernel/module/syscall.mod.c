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
	{ 0xabac11df, "module_layout" },
	{ 0x3deb5ca7, "filp_close" },
	{ 0xe8357875, "syscall_pre_handler" },
	{ 0xd184a4f7, "filp_open" },
	{ 0x50eedeb8, "printk" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xd0d8621b, "strlen" },
	{ 0x91715312, "sprintf" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x2f473be4, "current_task" },
	{ 0xd777ceae, "syscall_id" },
	{ 0xb4390f9a, "mcount" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "7DC6679F7E3650F753FA68A");
