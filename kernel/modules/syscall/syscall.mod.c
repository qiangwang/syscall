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
	{ 0x706ac060, "module_layout" },
	{ 0x3ec8886f, "param_ops_int" },
	{ 0xd0d8621b, "strlen" },
	{ 0x67e0fe38, "filp_close" },
	{ 0x91715312, "sprintf" },
	{ 0xe2d5255a, "strcmp" },
	{ 0x72aa82c6, "param_ops_charp" },
	{ 0x68530620, "current_task" },
	{ 0x50eedeb8, "printk" },
	{ 0xb4390f9a, "mcount" },
	{ 0xf0fdf6cb, "__stack_chk_fail" },
	{ 0xd777ceae, "syscall_id" },
	{ 0xe8357875, "syscall_pre_handler" },
	{ 0xf59f197, "param_array_ops" },
	{ 0xed6b9c39, "filp_open" },
};

static const char __module_depends[]
__used
__attribute__((section(".modinfo"))) =
"depends=";


MODULE_INFO(srcversion, "0CB81F36FC63C9C56DE3056");
