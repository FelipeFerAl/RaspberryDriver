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

##Compilation 



