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
    if (isEXT2(fd)) {
        showInfoEXT2();
    } else {
        showInfoFAT16(fd);
    }
    close(fd);
}



