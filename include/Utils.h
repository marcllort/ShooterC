//
// Created by mac12 on 21/03/2020.
//

#ifndef SHOOTERC_UTILS_H
#define SHOOTERC_UTILS_H

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include "Types.h"

#define FILE_TYPE 1
#define DIR_TYPE 2
#define UNDEFINED_TYPE 3

void strToUpper(char *string);

int fatStrLen(unsigned char *string);

int UTILS_compare(const char *str1, const char *str2);

int UTILS_sizeOf(const char *str);

#endif //SHOOTERC_UTILS_H
