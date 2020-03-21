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

int fatStrLen(char *string) {
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
int UTILS_compare(const char *str1, const char *str2, int size)
{
    int i;
    for (i = 0; i < size; i++)
        if (str1[i] != str2[i])
            return 1;
    return 0;
}