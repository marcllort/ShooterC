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

    ext2.blockSize = 1024 << ext2.blockSize;       // 3.1.7 Documentation EX2

    return ext2;
}

Ext2Directory getInfoEXT2Directory(int fd, unsigned int filePosition) {
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

    lseek(fd, groupDescriptor + 8, SEEK_SET);
    read(fd, &inodeTablePosition, 4);

    inodeSeekPosition = inodeTablePosition * ext2.blockSize;
    seekPosition = inodeSeekPosition + (inodeNum - 1) * ext2.inodeSize;

    seekPosition += 4;
    lseek(fd, seekPosition, SEEK_SET);
    read(fd, &inodeEntry.i_size, 4);

    seekPosition += 36;
    lseek(fd, seekPosition, SEEK_SET);

    for (int i = 0; i < 15; i++) {
        lseek(fd, seekPosition, SEEK_SET);
        inodeEntry.i_block[i] = 0;
        read(fd, &inodeEntry.i_block[i], sizeof(uint32_t));
        seekPosition = seekPosition + 4;
    }

    return inodeEntry;
}

int findFileInEXT2(char *fileName) {
    Ext2Volume ext2 = getInfoEXT2();

    unsigned char fileType;
    int filePosition = findFileExtVolume(fd, ext2, fileName, &fileType, 2);

    if (fileType == FILE_TYPE) {
        Ext2Directory extDir = getInfoEXT2Directory(fd, filePosition);
        InodeEntry extInode = getInodeData(fd, ext2, extDir.inode);
        printf("File found! Size: %lu bytes\n", extInode.i_size);
    } else if (fileType == DIR_TYPE) {
        printf("Directory found!\n");
    } else {
        printf("File not found!\n");
    }

    return 0;
}


int findFileExtVolume(int fd, Ext2Volume ext2, char *fileName, unsigned char *fileType, int inodeNumber) {

    unsigned long retorno = 0;
    unsigned long dirOffset = 0;

    int blockPoint = 0;
    InodeEntry inode;
    Ext2Directory ext2Dir;
    unsigned long sumBlock = 0;


    inode = getInodeData(fd, ext2, inodeNumber);


    // Primeros 12 bloques del inodo
    for (blockPoint = 0; blockPoint < 12; blockPoint++) {
        sumBlock = 0;
        if (inode.i_block[blockPoint] == 0) {
            return 0;
        }

        dirOffset = inode.i_block[blockPoint] * ext2.blockSize;

        do {

            ext2Dir = getInfoEXT2Directory(fd, dirOffset);
            // Comprobamos si el nombre coincide y si es una entrada de directorio valida!
            if (ext2Dir.inode != 0) {
                if (strcmp(ext2Dir.fileName, fileName) == 0) {
                    if (ext2Dir.fileType == 1) {
                        //printf("Es un fichero: %s \n", ext2Dir.fileName);
                        *fileType = 1;
                        return dirOffset;    // Devolvemos el offset de la dirEntry, para mostrar podremos volver a leer el size y para copiar podremos mirar el inode.
                    }
                    if (ext2Dir.fileType == 2) {
                        //printf("Es un directorio: %s \n", ext2Dir.fileName);
                        *fileType = 2;
                        return dirOffset;
                    }

                } else {
                    // Solo nos interesan los directorios en esta zona
                    if (ext2Dir.fileType == 2) {

                        if (strcmp(ext2Dir.fileName, ".") != 0 && strcmp(ext2Dir.fileName, "..") != 0) {
                            //printf(">> Entrando en el directorio %s \n",ext2Dir.fileName);

                            // Entramos en el directorio y nos lo pateamos!
                            retorno = findFileExtVolume(fd, ext2, fileType, fileName, ext2Dir.inode);
                            if (retorno != 0) {
                                return retorno;
                            }
                        }
                    }
                }
            }

            dirOffset += ext2Dir.recordLength;
            sumBlock += ext2Dir.recordLength;
            //printf("Valor de sumblock %lu - valor de offset %lu \n",sumBlock, dirOffset);
        } while (sumBlock < ext2.blockSize);

    }

    // Primer puntero indirecto



    return retorno;

}