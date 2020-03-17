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

#endif //SHOOTERC_TYPES_H
