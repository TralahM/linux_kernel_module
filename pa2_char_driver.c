

#include <linux/cdev.h>
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
static int MAJOR_NO = 250;
static int MINOR_NO = 0;
static int NUM_CLOSES = 0;
static int NUM_OPENS = 0;
char* device_buffer;
static dev_t devno;
static struct cdev cdev;
static int ALLOC_MODE = 0;

ssize_t pa2_char_driver_read(struct file* pfile, char __user* buffer,
                             size_t length, loff_t* offset) {
    /* *buffer is the userspace buffer to where you are writing the data you
     * want to be read from the device file*/
    /* length is the length of the userspace buffer*/
    /* offset will be set to current position of the opened file after read*/
    /* copy_to_user function: source is device_buffer and destination is the
     * userspace buffer *buffer */
    // TODO specify count of bytes to copy
    ssize_t len;
    int err;
    len = min(BUFFER_SIZE - *offset, length);
    if (len < 0) {
        return 0;
    }
    err = copy_to_user(buffer, device_buffer + *offset, len);
    if (err) {
        printk(KERN_ALERT "Unable to copy to user");
        return -EFAULT;
    }
    *offset += len;

    return len;
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
    ssize_t len;
    len = min(BUFFER_SIZE - *offset, length);
    if (copy_from_user(device_buffer + *offset, buffer, len)) {
        printk(KERN_ALERT "Unable to copy from user");
        return -EFAULT;
    };
    *offset += len;

    return len;
}

int pa2_char_driver_open(struct inode* pinode, struct file* pfile) {
    /* print to the log file that the device is opened and also print the number
     * of times this device has been opened until now*/
    NUM_OPENS++;
    printk(KERN_INFO "Device OPENED %d Times.\n", NUM_OPENS);
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
    loff_t new_pos = 0;
    switch (whence) {
        case 0:  // SEEK_SET
            new_pos = offset;
            break;
        case 1:  // SEEK_CUR
            new_pos = pfile->f_pos + offset;
            break;
        case 2:  // SEEK_END
            new_pos = BUFFER_SIZE - offset;
            break;
    }
    if (new_pos > BUFFER_SIZE) {
        new_pos = BUFFER_SIZE;
    }
    if (new_pos < 0) {
        new_pos = 0;
    }
    pfile->f_pos = new_pos;
    return new_pos;
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

static int __init pa2_char_driver_init(void) {
    /* print to the log file that the init function is called.*/
    int err;
    printk(KERN_INFO "INIT Function Called.\n");
    device_buffer = kmalloc(BUFFER_SIZE, GFP_KERNEL);
    /* register the device */
    devno = MKDEV(MAJOR_NO, MINOR_NO);
    err = register_chrdev(MAJOR(devno), NAME, &pa2_char_driver_file_operations);
    /* Fail gracefully if need be */
    if (err < 0) {
        if ((err = alloc_chrdev_region(&devno, 0, 1, NAME))) {
            printk(KERN_ALERT
                   "[%s ]:FUNC: %s: LINE: %d \nError %d registering "
                   "and adding %s\n",
                   __FILE__, __FUNCTION__, __LINE__, err, NAME);
            return err;
        } else {
            ALLOC_MODE = 1;
        }
    }
    cdev_init(&cdev, &pa2_char_driver_file_operations);
    err = cdev_add(&cdev, devno, 1);  // register
    if (err < 0) {
        printk(KERN_ALERT
               "[%s ]:FUNC: %s: LINE: %d \nError %d adding cdev_add "
               "%s\n",
               __FILE__, __FUNCTION__, __LINE__, err, NAME);
        unregister_chrdev_region(devno, 1);  // Logout equipment number
        return err;
    }

    printk(KERN_INFO "Device Number %d MAJ:%d MIN:%d\n", devno, MAJOR(devno),
           MINOR(devno));

    printk(KERN_INFO "I was assigned major number %d. To talk to\n",
           MAJOR(devno));
    printk(KERN_INFO "the driver, create a dev file with\n");
    printk(KERN_INFO "'mknod /dev/%s -m 777 c %d 0'.\n", NAME, MAJOR(devno));
    printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
    printk(KERN_INFO "the device file.\n");
    printk(KERN_INFO "Remove the device file and module when done.\n");
    return 0;
}

static void __exit pa2_char_driver_exit(void) {
    /* print to the log file that the exit function is called.*/
    printk(KERN_INFO "Exit Function Called.\n");
    /* unregister  the device using the unregister_chrdev() function. */
    kfree(device_buffer);
    cdev_del(&cdev);
    if (ALLOC_MODE) {
        unregister_chrdev_region(devno, 1);
        return;
    }
    unregister_chrdev(MAJOR(devno), NAME);
}

/* add module_init and module_exit to point to the corresponding init and exit
 * function*/
module_init(pa2_char_driver_init);
module_exit(pa2_char_driver_exit);
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Character Device Driver Module");
MODULE_AUTHOR("TralahM");
