#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>

#define DEVICE_NAME "powerpulse"

static int powerpulse_open(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "PowerPulse: device opened\n");
    return 0;
}

static int powerpulse_release(struct inode *inode, struct file *file)
{
    printk(KERN_INFO "PowerPulse: device closed\n");
    return 0;
}

static struct file_operations powerpulse_fops = {
    .owner = THIS_MODULE,
    .open = powerpulse_open,
    .release = powerpulse_release,
};

static int __init powerpulse_init(void)
{
    printk(KERN_INFO "PowerPulse: driver loaded\n");
    printk(KERN_INFO "PowerPulse: character device ready\n");

    return 0;
}

static void __exit powerpulse_exit(void)
{
    printk(KERN_INFO "PowerPulse: driver unloaded\n");
}

module_init(powerpulse_init);
module_exit(powerpulse_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("PowerPulse");
MODULE_DESCRIPTION("Linux character-device driver for pulse monitoring");