#include <stdio.h>
#include "./include/Utils.h"

int main(int argc, char* argv[]) {
    if (!argc) {
        printf("Parameters are needed to run the program. Try again! \n");
    } else {
        if (strcmp(argv[1], "/info") == 0) {
            if (argc != 3) {
                printf("Incorrect number of parameters for the Info function! \n");
            } else {
                infoFileSystem(argv[2]);
            }
        } else {
            printf("Functionality not supported yet! \n");
        }
    }
    return 0;
}