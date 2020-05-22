//
// Created by mac12 on 17/03/2020.
//
#include "../include/EXT2.h"

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
    printf(BLOCK_SIZE, ext2.blockSize);
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

int isEXT2(int fileDescriptor) {
    uint32_t compat;
    uint32_t incompat;
    int extent, journal;

    // Saving the file to our global fd
    fd = fileDescriptor;

    // Check feature_compat field and check if it's set to 1 or 0
    lseek(fd, 1116, SEEK_SET);
    read(fd, &compat, sizeof(uint32_t));
    journal = compat & 0x4;
    // Check feature_incompat field and check if it's set to 1 or 0
    lseek(fd, 1120, SEEK_CUR);
    read(fd, &incompat, sizeof(uint32_t));
    extent = incompat & 0x40;

    if (!journal && !extent) {
        return 1;
    }

    return 0;
}

Ext2Volume getInfoEXT2() {
    Ext2Volume ext2;

    // Move to info ext2 start position
    lseek(fd, 1024, SEEK_SET);
    read(fd, &ext2.inodesCount, sizeof(uint32_t));
    read(fd, &ext2.blockCount, sizeof(uint32_t));
    read(fd, &ext2.reservedBlocksCount, sizeof(uint32_t));
    read(fd, &ext2.freeBlockCount, sizeof(uint32_t));
    read(fd, &ext2.freeInodesCount, sizeof(uint32_t));
    read(fd, &ext2.firstDataBlock, sizeof(uint32_t));
    read(fd, &ext2.blockSize, sizeof(uint32_t));
    ext2.blockSize = 1024 << ext2.blockSize;

    // Jump to blocksgroup position
    lseek(fd, 4, SEEK_CUR);
    read(fd, &ext2.blocksGroup, sizeof(uint32_t));
    read(fd, &ext2.fragsGroup, sizeof(uint32_t));
    read(fd, &ext2.inodesGroup, sizeof(uint32_t));

    // Move to firstNode info position
    lseek(fd, 1108, SEEK_SET);
    read(fd, &ext2.firstInode, sizeof(uint32_t));
    read(fd, &ext2.inodeSize, sizeof(uint32_t));
    // Move to volumeName info position
    lseek(fd, 1144, SEEK_SET);
    read(fd, &ext2.volumeName, sizeof(uint32_t));
    // Move to lastCheck info position
    lseek(fd, 1088, SEEK_SET);
    read(fd, &ext2.lastCheck, sizeof(uint32_t));
    // Move to lastMounted info position
    lseek(fd, 1068, SEEK_SET);
    read(fd, &ext2.lastMounted, sizeof(uint32_t));
    read(fd, &ext2.lastWritten, sizeof(uint32_t));

    // Reset position
    lseek(fd, 1024, SEEK_SET);

    return ext2;
}

Ext2Directory getInfoEXT2Directory(int fd, unsigned long filePosition) {
    Ext2Directory extDir;
    lseek(fd, filePosition, SEEK_SET);
    memset(extDir.fileName, 0, 255);            // Clear fileName var

    read(fd, &extDir.inode, sizeof(uint32_t));
    read(fd, &extDir.recordLength, sizeof(uint16_t));
    read(fd, &extDir.nameLength, sizeof(unsigned char));
    read(fd, &extDir.fileType, sizeof(unsigned char));
    read(fd, &extDir.fileName, extDir.nameLength);

    return extDir;
}

InodeEntry getInodeData(int fd, Ext2Volume ext2, unsigned int inodeNum) {

    InodeEntry inodeEntry;
    unsigned long seekPosition = 0;
    unsigned long inodeTablePosition = 0;
    unsigned long inodeSeekPosition = 0;
    unsigned long groupDescriptor = 0;

    if (ext2.firstDataBlock == 0) {
        groupDescriptor = ext2.blockSize;
    } else {
        groupDescriptor = 2048;
    }

    // Jump to start of inode table position
    lseek(fd, groupDescriptor + 8, SEEK_SET);
    read(fd, &inodeTablePosition, 4);

    inodeSeekPosition = inodeTablePosition * ext2.blockSize;
    seekPosition = inodeSeekPosition + (inodeNum - 1) * ext2.inodeSize;

    // Jump to start of inode i_size table position
    seekPosition += 4;
    lseek(fd, seekPosition, SEEK_SET);
    read(fd, &inodeEntry.i_size, 4);

    // Jump to start of inode table position
    seekPosition += 36;
    lseek(fd, seekPosition, SEEK_SET);


    for (int i = 0; i < 15; i++) {
        if (inodeNum == 2) {
            lseek(fd, ((i * 4) + seekPosition), SEEK_SET);
        } else {
            lseek(fd, ((i * ext2.blockSize) + seekPosition), SEEK_SET);
        }
        inodeEntry.i_block[i] = 0;
        read(fd, &inodeEntry.i_block[i], sizeof(uint32_t));
    }

    return inodeEntry;
}

int findFileEXT2(char *fileName) {
    Ext2Volume ext2 = getInfoEXT2();
    filename = fileName;
    unsigned char fileType;
    unsigned char rootDir = 1;
    unsigned long filePosition = findFileExtVolume(fd, ext2, fileName, &fileType, &rootDir, 2);

    if (fileType == FILE_TYPE) {
        Ext2Directory extDir = getInfoEXT2Directory(fd, filePosition);
        printf("FILE POSITION: %lu -- INODE: %d\n", filePosition, extDir.inode);
        InodeEntry extInode = getInodeData(fd, ext2, extDir.inode);
        printf("File found! Size: %lu bytes\n", extInode.i_size);
    } else if (fileType == DIR_TYPE) {
        printf("Directory found!\n");
    } else {
        printf("File not found!\n");
    }

    return 0;
}

InodeEntry getInode(Ext2Volume ext2, unsigned int inodeNum) {
    int address = 0;
    unsigned int inodeTable, position;
    InodeEntry inodeEntry;

    if (inodeNum != 2) {
        address = ((inodeNum - 1) / ext2.inodesGroup) * ext2.blocksGroup * ext2.blockSize;
    }

    lseek(fd, 2048 + address + 8, SEEK_SET);
    read(fd, &inodeTable, 4);

    position = (inodeNum - 1) % ext2.inodesGroup;
    unsigned int seekPosition;

    if (inodeNum == 2) {
        seekPosition = inodeTable * ext2.blockSize + ext2.inodeSize;
    } else {
        seekPosition = inodeTable * ext2.blockSize + (ext2.inodeSize * position) + address;
    }

    // Jump to start of inode i_size table position
    seekPosition += 4;
    lseek(fd, seekPosition, SEEK_SET);
    read(fd, &inodeEntry.i_size, 4);

    // Jump to start of inode table position
    seekPosition += 36;
    lseek(fd, seekPosition, SEEK_SET);


    for (int i = 0; i < 15; i++) {
        if (inodeNum == 2) {
            lseek(fd, ((i * 4) + seekPosition), SEEK_SET);
        } else {
            lseek(fd, ((i * ext2.blockSize) + seekPosition), SEEK_SET);
        }
        inodeEntry.i_block[i] = 0;
        read(fd, &inodeEntry.i_block[i], sizeof(uint32_t));
    }

    return inodeEntry;
}

unsigned long
findFileExtVolume(int fd, Ext2Volume ext2, char *fileName, unsigned char *fileType, unsigned char *rootDir,
                  int inodeNumber) {

    unsigned long filePosition = 0;
    unsigned long offset = 0;
    unsigned int blockAddress;

    InodeEntry inodeEntry = getInode(ext2, inodeNumber);

    Ext2Directory ext2Dir;
    InodeEntry inode = getInodeData(fd, ext2, inodeNumber);

    for (int blockPointer = 0; blockPointer < 12; blockPointer++) {

        if (inode.i_block[blockPointer] != 0) {
            blockAddress = inodeEntry.i_block[blockPointer] * ext2.blockSize;

            while (offset < ext2.inodeSize) {
                ext2Dir = getInfoEXT2Directory(fd, blockAddress);

                if (UTILS_compare(ext2Dir.fileName, filename) == 0) {
                    // Return the offset, so we can later find easily the size
                    if (ext2Dir.fileType == FILE_TYPE) {
                        *fileType = FILE_TYPE;
                        return blockAddress;
                    } else if (ext2Dir.fileType == DIR_TYPE) {
                        *fileType = DIR_TYPE;
                        return blockAddress;
                    }
                } else {
                    // If it's a folder, we do a recursive call to look for the file
                    if (ext2Dir.fileType == DIR_TYPE) {
                        if (strcmp(ext2Dir.fileName, "..") != 0 && strcmp(ext2Dir.fileName, ".") != 0) {
                            filePosition = findFileExtVolume(fd, ext2, fileName, fileType, rootDir, ext2Dir.inode);
                            // If returned a position different than 0, it means we found the file
                            if (filePosition != 0) {
                                return filePosition;
                            }
                        }
                    }
                }

                blockAddress += ext2Dir.recordLength;
                offset += ext2Dir.recordLength;
            }
        }

    }
    return filePosition;
}

int deleteFileEXT2(char *fileName, char *fileSystem) {
    Ext2Volume ext2 = getInfoEXT2();
    filename = fileName;
    unsigned char fileType;
    unsigned char rootDir = 1;
    int fdEXT = open(fileSystem, O_RDWR);
    unsigned long filePosition = findFileExtVolume(fd, ext2, fileName, &fileType, &rootDir, 2);

    // Only deletes on root directory
    if ((fileType == FILE_TYPE || fileType == UNDEFINED_TYPE) && rootDir == 1) {
        deleteFileEXT2Volume(fdEXT, filePosition);
        printf("File %s has been deleted!\n", fileName);
    } else {
        printf("Unsupported delete!\n");
    }

    return 0;
}

int deleteFileEXT2Volume(int fd, unsigned long filePosition) {

    lseek(fd, filePosition, SEEK_SET);

    Ext2Directory newDir;
    newDir.inode = 0;
    bzero(newDir.fileName, sizeof(unsigned char));
    lseek(fd, filePosition, SEEK_SET);

    write(fd, &newDir.inode, sizeof(uint32_t));
    read(fd, &newDir.recordLength, sizeof(uint16_t));
    read(fd, &newDir.nameLength, sizeof(unsigned char));
    read(fd, &newDir.fileType, sizeof(unsigned char));
    write(fd, &newDir.fileName, newDir.nameLength);

    return 0;
}
