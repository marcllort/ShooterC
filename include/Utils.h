//
// Created by mac12 on 21/03/2020.
//

#ifndef SHOOTERC_UTILS_H
#define SHOOTERC_UTILS_H

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "Types.h"

#define NOT_FOUND -1
#define FILE_TYPE 1
#define DIR_TYPE 2

void strToUpper(char *string);

int fatStrLen(char *string);


void findInFileSystem(char *filesystem, char *filename);

#endif //SHOOTERC_UTILS_H
