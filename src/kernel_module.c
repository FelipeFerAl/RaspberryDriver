#include "kernel_module.h"

// Device number (major and minor)
dev_t dev_num;

// Character device structure
struct cdev led_cdev;
static struct class* led_class = NULL;

// Device structure to create /dev/led_device
static struct device* led_device = NULL;

// Variable to track LED state: 1 = ON, 0 = OFF
static int led_state = 0;

// File operations structure that defines how user-space interacts with this device
static struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = led_open,
    .release = led_release,
    .write = led_write,
    .read = led_read,
};

//Function called when the device is opened from user space
int led_open(struct inode *inode, struct file *file){
    printk(KERN_INFO "LED device opened\n");
    return 0;
}

//Function called when the device is closed from user space
int led_release(struct inode *inode, struct file *file) {
    printk(KERN_INFO "LED device closed\n");
    return 0;
}

//Function to handle write operations to the device
ssize_t led_write(struct file *file, const char __user *buf, size_t len, loff_t *offset) {
    char kbuf[2]; // Buffer to store incoming data (1 char + null terminator)

    if (copy_from_user(kbuf, buf, 1)) // Copy 1 byte from user space
        return -EFAULT;

    kbuf[1] = '\0'; 

    if (kbuf[0] == '1') {
        gpio_set_value(GPIO_PIN, 1); // Turn on LED
        led_state = 1;               // Update state variable
        printk(KERN_INFO "LED ON\n");
    } else if (kbuf[0] == '0') {
        gpio_set_value(GPIO_PIN, 0); // Turn off LED
        led_state = 0;               // Update state variable
        printk(KERN_INFO "LED OFF\n");
    } else {
        printk(KERN_WARNING "Invalid write: %c\n", kbuf[0]); 
    }

    return len; 
}

//Function to handle read operations from the device
ssize_t led_read(struct file *file, char __user *buf, size_t len, loff_t *offset) {
    char value = led_state ? '1' : '0'; // Represent current LED state as char

    if (*offset != 0) // Prevent multiple reads from returning the same data
        return 0;

    if (copy_to_user(buf, &value, 1)) 
        return -EFAULT;

    *offset = 1; // Update offset to prevent further reads
    return 1;    // Return number of bytes read
}

//Function called when the module is loaded into the kernel
int __init led_init(void) {
    int ret;

    printk(KERN_INFO "=== LED Driver INIT ===\n");
    
    // Allocate a device number (major + minor)
    ret = alloc_chrdev_region(&dev_num, 0, 1, DEVICE_NAME);
    if (ret < 0) {
        printk(KERN_ERR "Failed to allocate device number\n");
        return ret;
    }

    // Initialize character device with file operations
    cdev_init(&led_cdev, &fops);
    led_cdev.owner = THIS_MODULE;

    // Add character device to the system
    ret = cdev_add(&led_cdev, dev_num, 1);
    if (ret < 0) {
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ERR "Failed to add cdev\n");
        return ret;
    }

    // Create class for the device (/sys/class/led_class/)
    led_class = class_create(THIS_MODULE, "led_class");
    if (IS_ERR(led_class)) {
        printk(KERN_ERR "Failed to create class\n");
        cdev_del(&led_cdev);
        unregister_chrdev_region(dev_num, 1);
        return PTR_ERR(led_class);
    }

    // Create the device file (/dev/led_device)
    led_device = device_create(led_class, NULL, dev_num, NULL, "led_device");
    if (IS_ERR(led_device)) {
        class_destroy(led_class);
        cdev_del(&led_cdev);
        unregister_chrdev_region(dev_num, 1);
        return PTR_ERR(led_device);
    }
    
    // Request control of the GPIO pin
    ret = gpio_request(GPIO_PIN, "LED_PIN");
    if (ret) {
        cdev_del(&led_cdev);
        unregister_chrdev_region(dev_num, 1);
        printk(KERN_ERR "Failed to request GPIO %d\n", GPIO_PIN);
        return ret;
    }

    // Set the GPIO pin as output and turn LED off initially
    gpio_direction_output(GPIO_PIN, 0);

    printk(KERN_INFO "LED Driver ready. Major: %d Minor: %d\n", MAJOR(dev_num), MINOR(dev_num));
    return 0;
}

//Function called when the module is removed from the kernel
void __exit led_exit(void) {
    gpio_set_value(GPIO_PIN, 0);               // Turn off LED
    gpio_free(GPIO_PIN);                       // Free GPIO pin
    device_destroy(led_class, dev_num);        // Remove device from /dev
    class_destroy(led_class);                  // Remove class from sysfs
    cdev_del(&led_cdev);                       // Remove character device
    unregister_chrdev_region(dev_num, 1);      // Free device number
    printk(KERN_INFO "LED Driver exited\n");
}

//Register module entry and exit points
module_init(led_init);
module_exit(led_exit);

//Module metadata
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Felipe Fernandez Alzate - Paulina Ruiz Bonilla");
MODULE_DESCRIPTION("Character device driver for GPIO LED");

