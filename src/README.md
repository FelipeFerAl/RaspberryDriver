## This carpet contains the following files: 

- ### Makefile:
Build script that is used to automatically compile and build the kernel module without having to type all the commands manually

- ### kernel_module.c:

This code implements a Linux kernel module for driving an LED connected to the GPIO pin 23 on the Raspberry Pi. 
The module creates a character device that allows interaction with the LED from user space using files such as /dev/led_device.

- ### kernel_module.h:

This file contains all the neccesary libraries, packages, definitions and variables to the correct functioning of the main code.

- ### led_control.c:

It is the main code for the logic that allows turns on or off the LED depending of the option that the user chose.  
