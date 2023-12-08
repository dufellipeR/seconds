#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>
#include <asm/param.h>
#include <linux/jiffies.h>

#define BUFFER_SIZE 64

#define PROC_NAME "seconds"

long int initialJiff = 0;


/**
 * Function prototypes
 */
static ssize_t proc_read(struct file *file, char *buf, size_t count, loff_t *pos);

static const struct proc_ops prof_file_fops = {
    .proc_read = proc_read,
};

/* This function is called when the module is loaded. */
static int proc_init(void)
{
    initialJiff = jiffies;
    // creates the /proc/  entry
    proc_create(PROC_NAME, 0, NULL, &prof_file_fops);
    
    printk(KERN_INFO "Loading Module...\n");
    printk(KERN_INFO "/proc/%s created\n", PROC_NAME);

	return 0;
}

/* This function is called when the module is removed. */
static void proc_exit(void) {

        // removes the /proc/ entry
        remove_proc_entry(PROC_NAME, NULL);

        printk(KERN_INFO "Removing Module...\n");
        printk( KERN_INFO "/proc/%s removed\n", PROC_NAME);
}

/**
 * This function is called each time the /proc/ is read.
 */
static ssize_t proc_read(struct file *file, char __user *usr_buf, size_t count, loff_t *pos)
{
        int rv = 0;
        char buffer[BUFFER_SIZE];
        static int completed = 0;

        if (completed) {
                completed = 0;
                return 0;
        }

        completed = 1;

        rv = sprintf(buffer, "%lu\n", (jiffies - initialJiff)/ HZ);

        // copies the contents of buffer to userspace usr_buf
        copy_to_user(usr_buf, buffer, rv);

        return rv;
}

/* Macros for registering module entry and exit points. */
module_init( proc_init );
module_exit( proc_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Seconds Module");
MODULE_AUTHOR("Eduardo");