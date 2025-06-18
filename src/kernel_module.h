#ifndef _KERNEL_MODULE_H_
#define _KERNEL_MODULE_H_

#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define GPIO_PIN 23
#define DEVICE_NAME "led_device"

extern dev_t dev_num;
extern struct cdev led_cdev;

int led_open(struct inode *, struct file *);
int led_release(struct inode *, struct file *);
ssize_t led_write(struct file *, const char __user *, size_t, loff_t *);
ssize_t led_read(struct file *, char __user *, size_t, loff_t *);
int __init led_init(void);
void __exit led_exit(void);

#endif // _KERNEL_MODULE_H_
