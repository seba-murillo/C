#ifndef CHARDEV_H
#define CHARDEV_H
#include <linux/ioctl.h>
#define DEVICE_FILE_NAME "SO1codec_char_dev"
#define MAJOR_NUM 555
#define MINOR_NUM 0
#define DEVICE_MODE_PLAIN 1
#define DEVICE_MODE_CYPHER 2
#define MAX_STRING 256
#define IOCTL_CHANGE_MODE _IOR(MAJOR_NUM, 0, int)
#endif