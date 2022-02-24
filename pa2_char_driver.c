

#include <linux/errno.h>
#include <linux/fs.h>
#include <linux/gfp.h>
#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/uaccess.h>

#define BUFFER_SIZE 1024

/* Define device_buffer and other global data structures you will need here */
const char* NAME = "simple_char_device";
const unsigned int MAJOR_NO = 240;
int NUM_CLOSES = 0;
int NUM_OPENS = 0;
void* device_buffer;

ssize_t pa2_char_driver_read(struct file* pfile, char __user* buffer,
                             size_t length, loff_t* offset) {
    /* *buffer is the userspace buffer to where you are writing the data you
     * want to be read from the device file*/
    /* length is the length of the userspace buffer*/
    /* offset will be set to current position of the opened file after read*/
    /* copy_to_user function: source is device_buffer and destination is the
     * userspace buffer *buffer */
    // TODO specify count of bytes to copy
    int bytes_read=0;
    while(length&&*device_buffer){
        copy_to_user(*(buffer++), device_buffer++, 1);
        length--;
        bytes_read++;
    }

    return bytes_read;
}

ssize_t pa2_char_driver_write(struct file* pfile, const char __user* buffer,
                              size_t length, loff_t* offset) {
    /* *buffer is the userspace buffer where you are writing the data you want
     * to be written in the device file*/
    /* length is the length of the userspace buffer*/
    /* current position of the opened file*/
    /* copy_from_user function: destination is device_buffer and source is the
     * userspace buffer *buffer */
    // TODO specify count of bytes to copy
    if(copy_from_user(device_buffer, buffer, length)){return -EFAULT;};
    *offset+=length;

    return length;
}

int pa2_char_driver_open(struct inode* pinode, struct file* pfile) {
    /* print to the log file that the device is opened and also print the number
     * of times this device has been opened until now*/
    NUM_OPENS++;
    printk(KERN_INFO "Device Closed %d Times.\n", NUM_OPENS);
    return 0;
}

int pa2_char_driver_close(struct inode* pinode, struct file* pfile) {
    /* print to the log file that the device is closed and also print the number
     * of times this device has been closed until now*/
    NUM_CLOSES++;
    printk(KERN_INFO "Device Closed %d Times.\n", NUM_CLOSES);
    return 0;
}

loff_t pa2_char_driver_seek(struct file* pfile, loff_t offset, int whence) {
    /* Update open file position according to the values of offset and whence */
    return 0;
}

struct file_operations pa2_char_driver_file_operations = {

    .owner = THIS_MODULE,
    .read = pa2_char_driver_read,
    .write = pa2_char_driver_write,
    .llseek = pa2_char_driver_seek,
    .open = pa2_char_driver_open,
    .release = pa2_char_driver_close,
    /* add the function pointers to point to the corresponding file operations.
       look at the file fs.h in the linux souce code*/
};

static int pa2_char_driver_init(void) {
    /* print to the log file that the init function is called.*/
    printk(KERN_INFO "INIT Function Called.\n");
    device_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
    /* register the device */
    int err = register_chrdev(MAJOR_NO, NAME, &pa2_char_driver_file_operations);

    /* Fail gracefully if need be */
    if (err != 0) {
        printk(KERN_NOTICE "Error %d adding %s", err, NAME);
    }
    return 0;
}

static void pa2_char_driver_exit(void) {
    /* print to the log file that the exit function is called.*/
    printk(KERN_INFO "Exit Function Called.\n");
    /* unregister  the device using the unregister_chrdev() function. */
    kfree(device_buffer);
    unregister_chrdev(MAJOR_NO, NAME);
}

/* add module_init and module_exit to point to the corresponding init and exit
 * function*/
module_init(pa2_char_driver_init);
module_exit(pa2_char_driver_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Character Device Driver Module");
MODULE_AUTHOR("TralahM");
