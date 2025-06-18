#ifndef _KERNEL_MODULE_H_
#define _KERNEL_MODULE_H_

#include <linux/module.h>
#include <linux/init.h>
#include <linux/gpio.h>
#include <linux/fs.h>

#define GPIO_PIN 23

int initiate(void);
void exiting(void);

#endif // _KERNEL_MODULE_H_
