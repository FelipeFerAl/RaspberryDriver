#include "kernel_module.h"

static int __init module_start(void){
    return initiate();
}

static void __exit module_end(void){
    exiting();
}

module_init(module_start);
module_exit(module_end);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Felipe Fernandez Alzate - Paulina Ruiz Bonilla");
MODULE_DESCRIPTION("Modularized LED Kernel Driver");
