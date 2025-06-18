// kernel_module.c

#include "kernel_module.h"

int initiate(void){
    int ret;

    printk(KERN_INFO "LED Driver\n");

    ret = gpio_request(GPIO_PIN, "LED_PIN");
    if (ret) {
        printk(KERN_ERR "Failed to request GPIO %d\n", GPIO_PIN);
        return ret;
    }

    ret = gpio_direction_output(GPIO_PIN, 1);
    if (ret) {
        printk(KERN_ERR "Failed to set GPIO %d as output\n", GPIO_PIN);
        gpio_free(GPIO_PIN);
        return ret;
    }

    printk(KERN_INFO "GPIO %d set HIGH\n", GPIO_PIN);
    return 0;
}

void exiting(void){
    printk(KERN_INFO "Driver closed\n");
    gpio_set_value(GPIO_PIN, 0);
    gpio_free(GPIO_PIN);
    printk(KERN_INFO "GPIO %d released and set LOW\n", GPIO_PIN);
}
