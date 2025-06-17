#include <linux/module.h> // Necesario para todos los módulos del kernel
#include <linux/init.h> // Macros __init y __exit
#include <linux/fs.h> // Estructuras y funciones para dispositivos de carácter
#include <linux/uaccess.h> // Para copiar datos entre espacio de usuario y kernel
#include <linux/gpio.h> // API de control de GPIO basada en número
#include <linux/device.h> // Funciones para crear dispositivos en /dev
#include <linux/cdev.h> // Funciones y estructuras para dispositivos de carácter
#include <linux/delay.h> // Funciones de retardo

int initiate(void){
    printk("LED Driver\n");
    return 0;
}

void exiting(void){
    printk("Driver closed\n");
}

module_init(initiate);
module_exit(exiting);

MODULE_LICENSE("GPL");
