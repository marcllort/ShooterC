//
// Created by mac12 on 17/03/2020.
//
#include "../include/EXT2.h"

// GENERAL

int isEXT2(int fileDescriptor) {
    uint32_t compat;
    uint32_t incompat;
    int extent, journal;

    // Saving the file to our global fd
    fd = fileDescriptor;

    // Check compat field and check if it's set to 1 or 0
    lseek(fd, 1116, SEEK_SET);
    read(fd, &compat, sizeof(uint32_t));
    journal = compat & 0x4;
    // Check incompat field and check if it's set to 1 or 0
    lseek(fd, 1120, SEEK_CUR);
    read(fd, &incompat, sizeof(uint32_t));
    extent = incompat & 0x40;

    if (!journal && !extent) {
        return 1;
    }

    return 0;
}

// FASE 1

void printInfoExt2(Ext2Volume ext2) {

    printf("------ Filesystem Information ------\n\n");
    printf("Filesystem: EXT2\n\n");

    printf("INODE INFO\n");
    printf(INODE_SIZE, ext2.inodeSize);
    printf(NUMBER_INODES, ext2.inodesCount);
    printf(FIRST_INODE, ext2.firstInode);
    printf(INODES_GROUP, ext2.inodesGroup);
    printf(FREE_INODES, ext2.freeInodesCount);

    printf("BLOCK INFO\n");
    printf(BLOCK_SIZE, pow(2, (10 + ext2.blockSize)));
    printf(RESERVED_BLOCK, ext2.reservedBlocksCount);
    printf(FREE_BLOCKS, ext2.freeBlockCount);
    printf(TOTAL_BLOCKS, ext2.blockCount);
    printf(FIRST_BLOCK, ext2.firstDataBlock);
    printf(BLOCK_GROUP, ext2.blocksGroup);
    printf(FRAGS_GROUP, ext2.fragsGroup);

    printf("VOLUME INFO\n");
    printf(VOLUME_NAME, ext2.volumeName);
    printf(LAST_CHECK_VOL, asctime(getTime(ext2.lastCheck)));
    printf(LAST_MOUNT_VOL, asctime(getTime(ext2.lastMounted)));
    printf(LAST_WRITTEN, asctime(getTime(ext2.lastWritten)));

}

struct tm *getTime(uint32_t time) {
    time_t rawTime;
    struct tm *timeInfo;

    rawTime = (time_t) time;
    timeInfo = localtime(&rawTime);

    return timeInfo;
}

void showInfoEXT2() {
    Ext2Volume ext2;

    lseek(fd, 1024, SEEK_SET);
    read(fd, &ext2.inodesCount, sizeof(uint32_t));

    lseek(fd, 0, SEEK_CUR);
    read(fd, &ext2.blockCount, sizeof(uint32_t));

    lseek(fd, 0, SEEK_CUR);
    read(fd, &ext2.reservedBlocksCount, sizeof(uint32_t));

    lseek(fd, 0, SEEK_CUR);
    read(fd, &ext2.freeBlockCount, sizeof(uint32_t));

    lseek(fd, 0, SEEK_CUR);
    read(fd, &ext2.freeInodesCount, sizeof(uint32_t));

    lseek(fd, 0, SEEK_CUR);
    read(fd, &ext2.firstDataBlock, sizeof(uint32_t));

    lseek(fd, 0, SEEK_CUR);
    read(fd, &ext2.blockSize, sizeof(uint32_t));

    lseek(fd, 4, SEEK_CUR);
    read(fd, &ext2.blocksGroup, sizeof(uint32_t));

    lseek(fd, 0, SEEK_CUR);
    read(fd, &ext2.fragsGroup, sizeof(uint32_t));

    lseek(fd, 0, SEEK_CUR);
    read(fd, &ext2.inodesGroup, sizeof(uint32_t));

    lseek(fd, 1108, SEEK_SET);
    read(fd, &ext2.firstInode, sizeof(uint32_t));

    lseek(fd, 0, SEEK_CUR);
    read(fd, &ext2.inodeSize, sizeof(uint32_t));

    lseek(fd, 1144, SEEK_SET);
    read(fd, &ext2.volumeName, sizeof(uint32_t));

    lseek(fd, 1088, SEEK_SET);
    read(fd, &ext2.lastCheck, sizeof(uint32_t));

    lseek(fd, 1068, SEEK_SET);
    read(fd, &ext2.lastMounted, sizeof(uint32_t));

    lseek(fd, 0, SEEK_CUR);
    read(fd, &ext2.lastWritten, sizeof(uint32_t));


    printInfoExt2(ext2);
}

// FASE 2

void findInEXT2(char* filename){

}