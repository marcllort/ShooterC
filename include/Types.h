//
// Created by mac12 on 17/03/2020.
//

#ifndef SHOOTERC_TYPES_H
#define SHOOTERC_TYPES_H

#include <stdint.h>

typedef struct {
    // Inode Info
    uint32_t inodesCount;
    uint32_t freeInodesCount;
    uint32_t inodesGroup;
    uint32_t inodeSize;
    uint32_t firstInode;

    // Block Info
    uint32_t blockCount;
    uint32_t freeBlockCount;
    uint32_t reservedBlocksCount;
    uint32_t firstDataBlock;
    uint32_t blocksGroup;
    uint32_t blockSize;
    uint32_t fragsGroup;

    // Volume Info
    char volumeName[16];
    uint32_t lastCheck;
    uint32_t lastMounted;
    uint32_t lastWritten;
} Ext2Volume;

typedef struct {
    uint32_t inode;
    uint16_t recordLength;
    unsigned char nameLength;
    unsigned char fileType;
    char fileName[255];
} Ext2Directory;

typedef struct {
    unsigned long i_mode;
    unsigned long i_uid;
    unsigned long i_size;
    unsigned long i_atime;
    unsigned long i_ctime;
    unsigned long i_mtime;
    unsigned long i_dtime;
    unsigned long i_gid;
    unsigned long i_links_count;
    unsigned long i_blocks;
    unsigned long i_flags;
    unsigned long i_osd1;
    unsigned long i_block[15];
    unsigned long i_generation;
    unsigned long i_file_acl;
    unsigned long i_dir_acl;
    unsigned long i_faddr;
    unsigned long i_osd2;
} InodeEntry;

typedef struct {
    char systemName[8];
    uint16_t sectorSize;
    uint8_t sectorCluster;
    uint16_t reservedSectors;
    uint8_t numberFats;
    uint16_t rootEntries;
    uint32_t sectorsFat;
    char volumeName[12];
} FAT16Volume;

typedef struct {
    char name[12];
    char extension[4];
    unsigned char fileAttribute;
    uint16_t reserved;
    uint16_t time;
    uint16_t date;
    uint16_t firstCluster;
    uint32_t size;
} FAT16Directory;


#endif //SHOOTERC_TYPES_H
