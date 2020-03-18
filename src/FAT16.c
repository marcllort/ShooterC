//
// Created by mac12 on 17/03/2020.
//
#include "../include/FAT16.h"

// GENERAL

int isFAT16(int fileDescriptor) {
    fd = fileDescriptor;
    char aux[8];
    lseek(fd, 54, SEEK_SET);
    read(fd, &aux, 8);

    if (memcmp(aux, "FAT16", sizeof(char) * 5) == 0) {
        return 1;
    } else if (memcmp(aux, "FAT32", sizeof(char) * 5) == 0){
        return -1;
    } else if (memcmp(aux, "FAT12", sizeof(char) * 5) == 0){
        return -1;
    }

    return 0;
}

// FASE 1

void printInfoFat16(FAT16Volume fat16) {
    printf("------ Filesystem Information ------ \n\n");
    printf("FileSystem: FAT16\n\n");

    printf(SYSTEM_NAME, fat16.systemName);
    printf(SECTOR_SIZE, fat16.sectorSize);
    printf(SECTOR_CLUSTER, (fat16.sectorCluster));
    printf(RESERVED_SECTORS, (fat16.reservedSectors));
    printf(NUMBER_FATS, (fat16.numberFats));
    printf(ROOT_ENTRIES, (fat16.rootEntries));
    printf(SECTORS_FAT, (fat16.sectorsFat));
    printf(LABEL, fat16.volumeName);
}

void showInfoFAT16() {
    FAT16Volume fat16;

    lseek(fd, 3, SEEK_SET);
    read(fd, &fat16.systemName, 8);
    read(fd, &fat16.sectorSize, sizeof(uint16_t));
    read(fd, &fat16.sectorCluster, sizeof(uint8_t));
    read(fd, &fat16.reservedSectors, sizeof(uint16_t));
    read(fd, &fat16.numberFats, sizeof(uint8_t));
    read(fd, &fat16.rootEntries, sizeof(uint32_t));
    read(fd, &fat16.sectorsFat, sizeof(uint16_t));

    lseek(fd, 43, SEEK_SET);
    read(fd, &fat16.volumeName, 12);
    fat16.volumeName[11] = 0;

    printInfoFat16(fat16);
}

// FASE 2

void findInFAT16(char* filename){

}