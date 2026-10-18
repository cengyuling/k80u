#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/kprobes.h>

#define TARGET_SYMBOL "mtk_dsi_config_vdo_timing"

static int handler_pre(struct kprobe *p, struct pt_regs *regs)
{
    pr_info("K80U_Overclock: 成功拦截到 %s!\n", TARGET_SYMBOL);
    return 0;
}

static struct kprobe kp = {
    .symbol_name = TARGET_SYMBOL,
    .pre_handler = handler_pre,
};

static int __init oc_init(void)
{
    int ret;
    pr_info("K80U_Overclock: 模块开始加载...\n");
    
    ret = register_kprobe(&kp);
    if (ret < 0) {
        pr_err("K80U_Overclock: 挂载失败，错误码 %d\n", ret);
        return ret;
    }
    pr_info("K80U_Overclock: 挂载成功，正在监听...\n");
    return 0;
}

static void __exit oc_exit(void)
{
    unregister_kprobe(&kp);
    pr_info("K80U_Overclock: 模块已卸载。\n");
}

module_init(oc_init);
module_exit(oc_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("User");
MODULE_DESCRIPTION("Redmi K80 Ultra Display Overclock Hook");
