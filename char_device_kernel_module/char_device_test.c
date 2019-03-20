/*
 ============================================================================
 Name        : char_device_test.c
 Author      : Sebastian Murillo
 Version     : 1.0
 Copyright   : GPL
 Description : linux char device module test
 ============================================================================
 */

#include <chardevso1.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

char string[MAX_STRING];
char MODE_NAME[12];
int FD = 0;

void ioctl_changemode(int mode);
int chardev_write(const char* message, const int length);
int chardev_read(char* message, const int length);

int main() {
	/*
	 * sudo mknod SO1codec_char_dev c 555 0
	 * sprintf(string, "mknod %s c %d 0", DEVICE_FILE_NAME, MAJOR_NUM);
	 */
	printf("> char_device_test started\n\n");
	// create device file
	mknod(DEVICE_FILE_NAME, S_IFCHR, makedev(MAJOR_NUM, MINOR_NUM));
	// open file
	FD = open(DEVICE_FILE_NAME, O_RDWR);
	if(FD < 0){
		printf("Can't open device file: [%s]\n", DEVICE_FILE_NAME);
		//printf("Make sure file handler exists in this directory: [\"mknod %s c %d 0\"]\n", DEVICE_FILE_NAME, MAJOR_NUM);
		printf("Make sure file handler exists in this directory: (automatically generated by program)\n");
		printf("Make sure you are running this program with privileges (sudo / chmod...)\n");
		printf("> char_device_test finished\n");
		return EXIT_FAILURE;
	}
	//#define DEVICE_MODE_PLAIN 1
	//#define DEVICE_MODE_CYPHER 2
	printf("> testing plain text:\n");
	ioctl_changemode(DEVICE_MODE_PLAIN);	
	chardev_write("ABCDEF", 6);
	chardev_read(string, 6);
	printf("\n");
	printf("> testing cypher text:\n");
	ioctl_changemode(DEVICE_MODE_CYPHER);
	chardev_write("ABCDEF", 6);
	ioctl_changemode(DEVICE_MODE_PLAIN);
	chardev_read(string, 6);
	ioctl_changemode(DEVICE_MODE_CYPHER);
	chardev_read(string, 6);
	printf("\n");
	printf("> char_device_test finished\n");
	close(FD);
	return EXIT_SUCCESS;
}

void ioctl_changemode(int mode) {
	if(ioctl(FD, IOCTL_CHANGE_MODE, mode) < 0){
		printf("@ioctl_changemode: ERROR changing mode to %d\n", mode);
		exit(EXIT_FAILURE);
	}
	if(mode == DEVICE_MODE_PLAIN) sprintf(MODE_NAME, "PLAIN");
	else if(mode == DEVICE_MODE_CYPHER) sprintf(MODE_NAME, "CYHPER");
	else sprintf(MODE_NAME, "UNKNOWN");
	printf("@ioctl_changemode: mode is now [%s]\n", MODE_NAME);
}

int chardev_write(const char* message, const int length){
	if(length >= MAX_STRING){
		printf("@chardev_write: ERROR - length bigger than buffer.");
		return -1;
	}
	long unsigned result = write(FD, message, length);
	if(result < 0){
		printf("%-41s[%d]\n", "@chardev_write ERROR code:", errno);
		return result;
	}
	printf("%-41s[%s] [%s]\n", "@chardev_write message sent:", message, MODE_NAME);
	return result;
}

int chardev_read(char* message, const int length){
	if(length >= MAX_STRING){
		printf("@chardev_read: ERROR - length bigger than buffer.");
		return -1;
	}
	memset(message, '\0', length + 1);
	long unsigned result = read(FD, message, length);	
	if(result < 0){
		printf("%-41s[%d]\n", "@chardev_read: ERROR code:", errno);
		return result;
	}
	printf("%-41s[%s] [%s]\n", "@chardev_read message read:", message, MODE_NAME);
	return result;	
}