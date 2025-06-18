#include "kernel_module.h"

dev_t dev_num;
struct cdev led_cdev;
static struct class* led_class = NULL;
static struct device* led_device = NULL;
static int led_state = 0;

static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .release = led_release,
    .write = led_write,
    .read = led_read,
};

int led_open(struct inode *inode, struct file *file){
    printk(KERN_INFO "LED device opened\n");
    return 0;
}

int led_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "LED device closed\n");
    return 0;
}

ssize_t led_write(struct file *file, const char __user *buf, size_t len, loff_t *offset) {
    char kbuf[2];

    if (copy_from_user(kbuf, buf, 1))
        return -EFAULT;

    kbuf[1] = '\0';

    if (kbuf[0] == '1') {
        gpio_set_value(GPIO_PIN, 1);
        led_state = 1;
        printk(KERN_INFO "LED ON\n");
    } else if (kbuf[0] == '0') {
        gpio_set_value(GPIO_PIN, 0);
        led_state = 0;
        printk(KERN_INFO "LED OFF\n");
    } else {
        printk(KERN_WARNING "Invalid write: %c\n", kbuf[0]);
    }

    return len;
}

ssize_t led_read(struct file *file, char __user *buf, size_t len, loff_t *offset) {
    char value = led_state ? '1' : '0';

    if (*offset != 0)
        return 0;

    if (copy_to_user(buf, &value, 1))
        return -EFAULT;

    *offset = 1;
    return 1;
}

int __init led_init(void) {
    int ret;

    printk(KERN_INFO "=== LED Driver INIT ===\n");
    
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        printk(KERN_ERR "Failed to allocate device number\n");
        return ret;
    }

    cdev_init(&led_cdev, &fops);
    led_cdev.owner = THIS_MODULE;

    ret = cdev_add(&led_cdev, dev_num, 1);
    if (ret < 0) {
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ERR "Failed to add cdev\n");
        return ret;
    }

    led_class = class_create(THIS_MODULE, "led_class");
        if (IS_ERR(led_class)) {
            printk(KERN_ERR "Failed to create class\n");
            cdev_del(&led_cdev);
            unregister_chrdev_region(dev_num, 1);
            return PTR_ERR(led_class);
    }

    led_device = device_create(led_class, NULL, dev_num, NULL, "led_device");
        if (IS_ERR(led_device)) {
            class_destroy(led_class);
            cdev_del(&led_cdev);
            unregister_chrdev_region(dev_num, 1);
            return PTR_ERR(led_device);
    }
    
    ret = gpio_request(GPIO_PIN, "LED_PIN");
    if (ret) {
        cdev_del(&led_cdev);
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ERR "Failed to request GPIO %d\n", GPIO_PIN);
        return ret;
    }

    gpio_direction_output(GPIO_PIN, 0);
    printk(KERN_INFO "LED Driver ready. Major: %d Minor: %d\n", MAJOR(dev_num), MINOR(dev_num));
    return 0;
}

void __exit led_exit(void) {
    gpio_set_value(GPIO_PIN, 0);
    gpio_free(GPIO_PIN);
    device_destroy(led_class, dev_num);
    class_destroy(led_class);
    cdev_del(&led_cdev);
    unregister_chrdev_region(dev_num, 1);
    printk(KERN_INFO "LED Driver exited\n");
}

module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Felipe Fernandez Alzate - Paulina Ruiz Bonilla");
MODULE_DESCRIPTION("Character device driver for GPIO LED");
