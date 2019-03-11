/*
 * chardevso1.c
 *
 *  Created on: Nov 18, 2018
 *      Author: seba
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <chardevso1.h>
#include <asm/uaccess.h>

#define DEBUG 1

#define SUCCESS 0
#define FAILURE -1
#define DEVICE_NAME "SO1_char_device"

static int dev_used = 0;
static int MODE = DEVICE_MODE_PLAIN;
static char BUFFER[MAX_STRING];

static char dev_cyhper(char C){
	C += 10;
	return C;
}

static char dev_decyhper(char C){
	C -= 10;
	return C;
}

static int dev_open(struct inode *inode, struct file *file) {
	#ifdef DEBUG
	printk ("@dev_open: (%p)\n", file);
	#endif
	if(dev_used) return -EBUSY;
	dev_used++;
	//MOD_INC_USE_COUNT;// deprecated since 2.5.x
	return SUCCESS;
}

static int dev_close(struct inode *inode, struct file *file) {
	#ifdef DEBUG
	printk ("@dev_close: (%p, %p)\n", inode, file);
	#endif
	dev_used--;
	//MOD_DEC_USE_COUNT;// deprecated since 2.5.x
	return 0;
}

static ssize_t dev_read(struct file *file, char *buffer, size_t length, loff_t *offset) {
	int pos = 0;
	for(;pos < length && pos < MAX_STRING;pos++){
		if(MODE == DEVICE_MODE_CYPHER) BUFFER[pos] = dev_decyhper(BUFFER[pos]);
		put_user(BUFFER[pos], buffer++);
	}
	#ifdef DEBUG
	printk("@dev_read:\n");
	printk("|\t%-15s%p\n", "file:", file);
	printk("|\t%-15s%s\n", "BUFFER:", BUFFER);
	printk("|\t%-15s%lu\n", "length:", length);
	#endif
	return pos;
}

static ssize_t dev_write(struct file *file, const char *buffer, size_t length, loff_t *offset) {
	int pos;
	#ifdef DEBUG
	printk("@dev_write:\n");
	#endif
	for(pos = 0;pos < length && pos < MAX_STRING;pos++){
		get_user(BUFFER[pos], buffer + pos);
		if(MODE == DEVICE_MODE_CYPHER) BUFFER[pos] = dev_cyhper(BUFFER[pos]);
	}
	#ifdef DEBUG	
	printk("|\t%-15s%p\n", "file:", file);
	printk("|\t%-15s%s\n", "BUFFER:", BUFFER);
	printk("|\t%-15s%lu\n", "length:", length);
	#endif
	return pos;
}

static long dev_ioctl(struct file *file, unsigned int ioctl_num, unsigned long ioctl_param) {
	// mode change
	if(ioctl_num == IOCTL_CHANGE_MODE){
		if(ioctl_param != DEVICE_MODE_PLAIN && ioctl_param != DEVICE_MODE_CYPHER){
			printk("ERROR @ dev_ioctl() - mode unknown");
			return FAILURE;
		}
		MODE = ioctl_param;
	}
	return SUCCESS;
}

/*
 * seek, read, write,
 * readdir, select, ioclt,
 * mmap, open, flush, release
 */
struct file_operations fops = {
	.read = dev_read,
	.write = dev_write,
	.unlocked_ioctl = dev_ioctl,
	.open = dev_open,
	.release = dev_close
};

int init_module() {
	int result = register_chrdev(MAJOR_NUM, DEVICE_NAME, &fops);
	if(result < 0){
		printk("ERROR @ init_module() code: %d", result);
		return result;
	}
	#ifdef DEBUG
	printk("@init_module(): %s registration OK\n", DEVICE_NAME);
	printk("|\t%-25s%d\n", "major number:", MAJOR_NUM);
	printk("|\t%-25s%s\n\n", "DEVICE_FILE_NAME:", DEVICE_FILE_NAME);
	#endif
	return SUCCESS;
}

void cleanup_module() {
	#ifdef DEBUG
	printk("@cleanup_module(): cleaning up %s\n", DEVICE_NAME);
	#endif
	unregister_chrdev(MAJOR_NUM, DEVICE_NAME);
}