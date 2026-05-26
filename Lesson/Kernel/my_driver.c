#include <linux/init.h> 
#include <linux/module.h>
#include <linux/kernel.h> 

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Senior Student");
MODULE_DESCRIPTION("Ilk Kernel Modulum");
MODULE_VERSION("0.1");

static int __init my_driver_init(void) {
    printk(KERN_INFO ">>> [KERNEL] Merhaba Dunya! Ben artik icerideyim.\n");
    return 0;
}

static void __exit my_driver_exit(void) {
    printk(KERN_INFO "<<< [KERNEL] Gorusuruz! Modul bellekten silindi.\n");
}

module_init(my_driver_init);
module_exit(my_driver_exit);