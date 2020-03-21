//
// Created by mac12 on 17/03/2020.
//

#ifndef SHOOTERC_MAINUTILS_H
#define SHOOTERC_MAINUTILS_H

#include "EXT2.h"
#include "FAT16.h"
#include "Types.h"
#include <ctype.h>

void infoFileSystem(char *filesystem);

void searchInFileSystem(char *filesystem, char *filename);

#endif //SHOOTERC_MAINUTILS_H
