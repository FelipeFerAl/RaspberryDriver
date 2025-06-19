# Homework #2 "LED GPIO Driver on Raspberry Pi using Linux Kernel Module"

## Authors:

- Felipe Fernández Alzate - C.C.1056120378
- Paulina Ruiz Bonilla - C.C.1002609493

## Description:

This project implements a character device driver in the form of a Linux Kernel Module (LKM) to control a GPIO-connected LED on a Raspberry Pi. The module allows user-space programs to interact with the LED by writing '1' or '0' to turn it on or off, respectively. It also supports reading the current LED state.

## Learning Objectives: 

- Understand the architecture of Linux character device drivers.
- Learn to register and expose kernel modules through device files.
- Implement GPIO control within the Linux kernel.
- Design user-space applications that interact with device files.
- Apply sound software engineering practices, including documentation, testing, and version
control.

## Features: 
- Custom character device with open, read, write, and release operations.
- GPIO pin configuration and handling using gpio_request, gpio_direction_output, and gpio_set_value.
- Clean module initialization  with proper resource management.
- Debug messages via printk().

## Project Structure: 

![WhatsApp Image 2025-06-18 at 3 16 06 PM](https://github.com/user-attachments/assets/a6d64056-64af-43e0-a0b9-3be81212646b)

## Compilation and results 

- `make` = builds the neccesary modules and the "kernel object" to the correct functioning of each of the functions.
- `make clean` = clean all the system, including temporal files.
- `sudo insmod led_driver.ko` = inserts the module "Kernel object" to upload it to the raspberry pi.
- `sudo dmesg -W` = visualize in real time if the module were correctly installed

![WhatsApp Image 2025-06-18 at 3 17 31 PM](https://github.com/user-attachments/assets/92ef4ef5-9bd4-4199-a5c1-840f2204fed8)

- `sudo ./bin/led_control` = executable for the complete functioning of the system. It allows to visualize the options menu. 

![WhatsApp Image 2025-06-18 at 3 20 01 PM](https://github.com/user-attachments/assets/cd7aafbd-e215-4788-b7c0-4abb13804a84)

- `1`= the LED turns on
  
![WhatsApp Image 2025-06-18 at 3 20 55 PM](https://github.com/user-attachments/assets/af0f74b4-0e15-4562-b207-71625b38b916)

-  `0` = the LED turns off
- `3`= LED state

![WhatsApp Image 2025-06-18 at 3 21 19 PM](https://github.com/user-attachments/assets/4dbf3d53-e242-467a-a552-e93e176f4d23)

- `sudo rmmod temp/kernel_module.ko` = removes the module
  
- When the process has been complete, the resuls displayed are:

  ![WhatsApp Image 2025-06-18 at 3 22 19 PM](https://github.com/user-attachments/assets/cf4b5d6b-d486-4661-b3f8-06ff70ad7bc1)


