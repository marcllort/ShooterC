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
#include "Utils.h"

int fd;
char *filename;

// Inode Info
#define INODE_SIZE "Inode Size: %d\n"
#define NUMBER_INODES "Number of Inodes: %d\n"
#define FIRST_INODE "First Inode: %d\n"
#define INODES_GROUP "Inodes Group: %d\n"
#define FREE_INODES "Free Inodes: %d\n\n"

// Block Info
#define BLOCK_SIZE "Block Size: %d\n"
#define RESERVED_BLOCK "Reserved Blocks: %d\n"
#define FREE_BLOCKS "Free Blocks: %d\n"
#define TOTAL_BLOCKS "Total Blocks: %d\n"
#define FIRST_BLOCK "First Block: %d\n"
#define BLOCK_GROUP "Block Group: %d\n"
#define FRAGS_GROUP "Frags Group: %d\n\n"

// Volume Info
#define VOLUME_NAME "Volume name: %s\n"
#define LAST_CHECK_VOL "Last check: %s"
#define LAST_MOUNT_VOL "Last mount: %s"
#define LAST_WRITTEN "Last written: %s"


void printInfoExt2(Ext2Volume ext2);

struct tm *getTime(uint32_t time);

int isEXT2(int fileDescriptor);

Ext2Volume getInfoEXT2();

Ext2Directory getInfoEXT2Directory(int fd, unsigned long filePosition);

InodeEntry getInodeData(int inode, Ext2Volume ext2, unsigned int inodeNum);

InodeEntry getInode(Ext2Volume ext2, unsigned int inodeNum);

int findFileEXT2(char *fileName);

unsigned long
findFileExtVolume(int fd, Ext2Volume ext2, char *fileName, unsigned char *fileType, unsigned char *rootDir,
                  int inodeNumber);

int deleteFileEXT2(char *fileName, char *fileSystem);

int deleteFileEXT2Volume(int fd, unsigned long filePosition);

#endif //SHOOTERC_EXT2_H
