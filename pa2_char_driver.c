

#include <linux/init.h>
#include <linux/kdev_t.h>
#include <linux/kernel.h>
#include <linux/module.h>

#include <linux/fs.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/uaccess.h>

#define BUFFER_SIZE 1024

/* Define device_buffer and other global data structures you will need here */
dev_t pa2_dev = MKDEV(240, 0);

ssize_t pa2_char_driver_read(struct file *pfile, char __user *buffer,
                             size_t length, loff_t *offset) {
  /* *buffer is the userspace buffer to where you are writing the data you want
   * to be read from the device file*/
  /* length is the length of the userspace buffer*/
  /* offset will be set to current position of the opened file after read*/
  /* copy_to_user function: source is device_buffer and destination is the
   * userspace buffer *buffer */

  return 0;
}

ssize_t pa2_char_driver_write(struct file *pfile, const char __user *buffer,
                              size_t length, loff_t *offset) {
  /* *buffer is the userspace buffer where you are writing the data you want to
   * be written in the device file*/
  /* length is the length of the userspace buffer*/
  /* current position of the opened file*/
  /* copy_from_user function: destination is device_buffer and source is the
   * userspace buffer *buffer */

  return length;
}

int pa2_char_driver_open(struct inode *pinode, struct file *pfile) {
  /* print to the log file that the device is opened and also print the number
   * of times this device has been opened until now*/
  return 0;
}

int pa2_char_driver_close(struct inode *pinode, struct file *pfile) {
  /* print to the log file that the device is closed and also print the number
   * of times this device has been closed until now*/
  return 0;
}

loff_t pa2_char_driver_seek(struct file *pfile, loff_t offset, int whence) {
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
  /* register the device */
  int k =
      register_chrdev_region(pa2_dev, BUFFER_SIZE, "simple_character_device");
  if (k != 0) {
    return -1;
  }
  return 0;
}

static void pa2_char_driver_exit(void) {
  /* print to the log file that the exit function is called.*/
  /* unregister  the device using the register_chrdev() function. */
  unregister_chrdev_region(pa2_dev, BUFFER_SIZE);
}

/* add module_init and module_exit to point to the corresponding init and exit
 * function*/
module_init(pa2_char_driver_init);
module_exit(pa2_char_driver_exit);
