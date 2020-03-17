//
// Created by mac12 on 17/03/2020.
//

#ifndef SHOOTERC_FAT16_H
#define SHOOTERC_FAT16_H

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

#define SYSTEM_NAME "System Name: %s\n"
#define SECTOR_SIZE "Sector Size: %d\n"
#define SECTOR_CLUSTER "Sectors per Cluster: %hhu\n"
#define RESERVED_SECTORS "Reserved Sectors: %d\n"
#define NUMBER_FATS "Number of FATs: %d\n"
#define ROOT_ENTRIES "Maximum Root Entries: %d\n"
#define SECTORS_FAT "Sectors per FAT: %d\n"
#define LABEL "Label: %s\n"
#define ROOT_CLUSTER "\nREMOVE!!\nRootCluster: %hhu\n\n"

void printInfoFat16(FAT16Volume fat16);

int isFAT16(int fileDescriptor);

void showInfoFAT16();

#endif //SHOOTERC_FAT16_H
