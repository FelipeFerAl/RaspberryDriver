#include <linux/module.h> // Necesario para todos los módulos del kernel
#include <linux/init.h> // Macros __init y __exit
#include <linux/gpio.h>

#define PIN 23

static int __init initiate(void){
    int ret;
    printk(KERN_INFO "LED Driver\n");

    ret = gpio_request(PIN, "LED_PIN");
    if (ret){
        printk(KERN_ERR "Failed to request GPIO %d\n", PIN);
        return ret;
    }

    ret = gpio_direction_output(PIN, 1);
    if (ret){
        printk(KERN_ERR "Failed to set GPIO %d as output\n", PIN);
        gpio_free(PIN);
        return ret;
    }

    printk(KERN_INFO "GPIO %d set HIGH\n",PIN);
    return 0;
}


static void __exit exiting(void){
    printk(KERN_INFO "Driver closed\n");
    gpio_set_value(PIN, 0);
    gpio_free(PIN);

    printk(KERN_INFO "GPIO %d released and set LOW\n", PIN);
}

module_init(initiate);
module_exit(exiting);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Felipe Fernandez Alzate");
MODULE_DESCRIPTION("A Linux kernel module for a LED driver");
