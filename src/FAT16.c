//
// Created by mac12 on 17/03/2020.
//
#include "../include/FAT16.h"

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

FAT16Volume getInfoFAT16() {
    FAT16Volume fat16;

    lseek(fd, 3, SEEK_SET);
    read(fd, &fat16.systemName, 8);
    read(fd, &fat16.sectorSize, sizeof(uint16_t));
    read(fd, &fat16.sectorCluster, sizeof(uint8_t));
    read(fd, &fat16.reservedSectors, sizeof(uint16_t));
    read(fd, &fat16.numberFats, sizeof(uint8_t));
    read(fd, &fat16.rootEntries, sizeof(uint32_t));
    lseek(fd, 22, SEEK_SET);
    read(fd, &fat16.sectorsFat, sizeof(uint16_t));

    lseek(fd, 43, SEEK_SET);
    read(fd, &fat16.volumeName, 12);
    fat16.volumeName[11] = 0;

    return fat16;
}

FAT16Directory getInfoFAT16Directory(int fd, unsigned int filePosition) {
    FAT16Directory fatDir;
    lseek(fd, filePosition, SEEK_SET);

    read(fd, &fatDir.name, 8);
    fatDir.name[8] = '\0';
    read(fd, &fatDir.extension, 3);
    fatDir.extension[3] = '\0';
    read(fd, &fatDir.fileAttribute, sizeof(unsigned char));
    read(fd, &fatDir.reserved, 10);
    read(fd, &fatDir.time, sizeof(uint16_t));
    read(fd, &fatDir.date, sizeof(uint16_t));
    read(fd, &fatDir.firstCluster, sizeof(uint16_t));
    read(fd, &fatDir.size, sizeof(uint32_t));

    return fatDir;
}

int findFileFAT16(char *fileName) {
    FAT16Volume fat16 = getInfoFAT16();

    strToUpper(fileName);
    unsigned char fileType;
    int filePosition = findFileFatVolume(fd, fat16, fileName, &fileType);

    if (fileType == FILE_TYPE) {
        FAT16Directory fatDir = getInfoFAT16Directory(fd, filePosition);
        printf("File found! Size: %d bytes\n", fatDir.size);
    } else if (fileType == DIR_TYPE) {
        printf("Directory found!\n");
    } else if(fileType == UNDEFINED_TYPE){
        FAT16Directory fatDir = getInfoFAT16Directory(fd, filePosition);
        printf("Undefined type of file! Size: %d bytes\n", fatDir.size);
    } else {
        printf("File not found!\n");
    }

    return 0;
}

int findFileFatVolume(int fd, FAT16Volume fat16, char *fileName, unsigned char *fileType) {

    char name[10];                      // Found file name
    int nameLength = 0;                 // Found file name length
    char extension[4];                  // Found file extension
    int extensionLength = 0;            // Found file extension length
    char findFileName[14];              // Complete found fileName (name+extension)
    uint32_t fileSize = 0;              // Found file size
    unsigned char fileAttributes = 0;   // Found file properties (file or directory)

    int fileSearchPosition = 0;         // Position to start finding

    // Root directory position
    unsigned int rootDirectory = ((fat16.reservedSectors * fat16.sectorSize) +
                                  (fat16.numberFats * fat16.sectorsFat * fat16.sectorSize));
    lseek(fd, rootDirectory, SEEK_SET);
    fileSearchPosition = rootDirectory;

    // Iterate through current root entrance entries
    for (int i = 0; i < fat16.rootEntries; i++) {

        // Clean variables
        memset(name, 0, 10);
        memset(extension, 0, 4);
        memset(findFileName, 0, 14);

        // Read file name
        read(fd, name, 8);
        nameLength = fatStrLen(name);
        name[nameLength] = '\0';
        strcat(findFileName, name);
        

        if (nameLength > 0) {
            read(fd, extension, 3);
            extensionLength = fatStrLen(extension);
            extension[extensionLength] = '\0';

            if (extensionLength > 0) {
                strcat(findFileName, ".");
                strcat(findFileName, extension);
            }

            // Read fileAttributes to know what type of file is
            read(fd, &fileAttributes, sizeof(unsigned char));
            /*int size1 = UTILS_sizeOf(findFileName);
            int size2 = UTILS_sizeOf(fileName);
            
            printf("Found: [%s] %d == [%s] %d FOUND? %d\n", findFileName, size1, fileName, size2, UTILS_compare(findFileName, fileName, 5)) ;*/
            // Check if it's the file we were looking for
            if (UTILS_compare(findFileName, fileName, UTILS_sizeOf(findFileName)) == 0) {
                // Read file size
                lseek(fd, 16, SEEK_CUR);
                read(fd, &fileSize, sizeof(uint32_t));
                // Save file type
                if ((fileAttributes & 0x20) == 0x20) {
                    *fileType = FILE_TYPE;
                    return fileSearchPosition;
                } else if ((fileAttributes & 0x10) == 0x10) {
                    *fileType = DIR_TYPE;
                    return fileSearchPosition;
                }else{
                    *fileType = UNDEFINED_TYPE;
                    return fileSearchPosition;
                }
            } else {
                // As we already moved 12bits to read name/extension and attributes, we move 32-8 = 24 bits to the next entry
                lseek(fd, 20, SEEK_CUR);
            }
        } else {
            // As we already moved 8bits to read name, we move 32-8 = 24 bits to the next entry
            lseek(fd, 24, SEEK_CUR);
        }
        // Next entrance is 32 bits away
        fileSearchPosition = fileSearchPosition + 32;
    }

    return NOT_FOUND;
}


