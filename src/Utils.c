//
// Created by mac12 on 21/03/2020.
//

#include "../include/Utils.h"

void strToUpper(char *string) {
    int size = strlen(string);
    int i = 0;

    for (i = 0; i < size; i++) {
        string[i] = toupper(string[i]);
    }
}

int fatStrLen(unsigned char *string) {
    int size = strlen(string);
    int i = 0;

    for (i = 0; i < size; i++) {
        // FAT16 doesn't support spaces, so if found space or \0, return size
        if (string[i] == ' ' || string[i] == '\0') {
            break;
        }
        if ((string[i] == '+') || (string[i] == ',') || (string[i] == ';') || (string[i] == '=') ||
            (string[i] == '[') || (string[i] == ']')) {
            // Check invalid FAT16 characters, if found, error
            return 0;
        }
    }
    return i;
}

// String comparator
int UTILS_compare(const char *str1, const char *str2) {
    int size1 = UTILS_sizeOf(str1);
    int size2 = UTILS_sizeOf(str2);

    if (size1 != size2) {
        return 1;
    }

    int i;
    for (i = 0; i < size1; i++)
        if (str1[i] != str2[i])
            return 1;
    return 0;
}

// String sizeOf, returns int with the size
int UTILS_sizeOf(const char *str) {
    int j = 0;
    int i = 0;

    while (j != 1) {
        if (str[i] == '\0') {
            j = 1;
        }
        i++;
    }
    i--;
    return i;
}