//
// Created by mac12 on 17/03/2020.
//

#ifndef SHOOTERC_EXT2_H
#define SHOOTERC_EXT2_H

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>
#include <math.h>
#include <stdarg.h>
#include <time.h>
#include "Types.h"

int fd;

// Inode Info
#define INODE_INFO "INODE INFO\n"
#define INODE_SIZE "Inode Size: %d\n"
#define NUMBER_INODES "Number of Inodes: %d\n"
#define FIRST_INODE "First Inode: %d\n"
#define INODES_GROUP "Inodes Group: %d\n"
#define FREE_INODES "Free Inodes: %d\n\n"

// Block Info
#define BLOCK_INFO "BLOCK INFO\n"
#define BLOCK_SIZE "Block Size: %.2f\n"
#define RESERVED_BLOCK "Reserved Blocks: %d\n"
#define FREE_BLOCKS "Free Blocks: %d\n"
#define TOTAL_BLOCKS "Total Blocks: %d\n"
#define FIRST_BLOCK "First Block: %d\n"
#define BLOCK_GROUP "Block Group: %d\n"
#define FRAGS_GROUP "Frags Group: %d\n\n"

// Volume Info
#define VOLUME_INFO "VOLUME INFO\n"
#define VOLUME_NAME "Volume name: %s\n"
#define LAST_CHECK_VOL "Last check: %s"
#define LAST_MOUNT_VOL "Last mount: %s"
#define LAST_WRITTEN "Last written: %s"

void showInfoEXT2();

void printInfoExt2(Ext2Volume ext2);

struct tm *getTime(uint32_t time);

int isEXT2(int fileDescriptor);

Ext2Volume getInfoEXT2();

#endif //SHOOTERC_EXT2_H
