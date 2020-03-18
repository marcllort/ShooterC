//
// Created by mac12 on 17/03/2020.
//

#include "../include/Utils.h"

void infoFileSystem(char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        printf("Error, filesystem not found! %s\n", filename);
        return;
    }

    int fat = isFAT16(fd);

    if (fat == 1) {
        showInfoFAT16();
    } else if (isEXT2(fd) && fat != -1) {
        showInfoEXT2();
    } else {
        printf("Filesystem not recognized! \n");
    }
    close(fd);
}

void findInFileSystem(char *filesystem, char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        printf("Error, filesystem not found! %s\n", filename);
        return;
    }

    int fat = isFAT16(fd);

    if (fat == 1) {
        findInFAT16(filename);
    } else if (isEXT2(fd) && fat != -1) {
        findInEXT2(filename);
    } else {
        printf("Filesystem not recognized! \n");
    }
    close(fd);
}


