//
// Created by mac12 on 17/03/2020.
//

#include "../include/MainUtils.h"

void infoFileSystem(char *filesystem) {
    int fd = open(filesystem, O_RDONLY);
    if (fd < 0) {
        printf("Error, filesystem not found! %s\n", filesystem);
        return;
    }
    if (isEXT2(fd)) {
        Ext2Volume ext2 = getInfoEXT2();
        printInfoExt2(ext2);
    } else if (isFAT16(fd)) {
        FAT16Volume fat16 = getInfoFAT16();
        printInfoFat16(fat16);
    } else {
        printf("Filesystem not recognized! \n");
    }
    close(fd);
}

void searchInFileSystem(char *filesystem, char *filename) {
    int fd = open(filesystem, O_RDONLY);
    if (fd < 0) {
        printf("Error, filesystem not found! %s\n", filesystem);
        return;
    }

    if (isEXT2(fd)) {
        findFileEXT2(filename);
    } else if (isFAT16(fd)) {
        findFileFAT16(filename);
    } else {
        printf("Filesystem not recognized! \n");
    }
    close(fd);
}

void deleteInFileSystem(char *filesystem, char *filename) {
    int fd = open(filesystem, O_RDONLY);
    if (fd < 0) {
        printf("Error, filesystem not found! %s\n", filesystem);
        return;
    }

    if (isEXT2(fd)) {
        deleteFileEXT2(filename);
    } else if (isFAT16(fd)) {
        deleteFileFAT16(filename);
    } else {
        printf("Filesystem not recognized! \n");
    }
    close(fd);
}


