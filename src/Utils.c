//
// Created by mac12 on 21/03/2020.
//

#include "../include/Utils.h"

void strToUpper(char *string) {
    int size = strlen(string);
    int i=0;

    for ( i=0; i<size; i++ ) {
        string[i] = toupper(string[i]);
    }
}

int fatStrLen(char *string) {
    // Despues de comprobar que el strlen no devuelve correctamente la longitud y ya que en FAT no pueden haber espacios.
    int fakeSize = strlen(string);
    int i = 0;

    for ( i = 0; i<fakeSize; i++) {
        if (string[i]==' ' || string[i]=='\0' ) {
            break;
        }
        if ( (string[i]=='+') || (string[i] == ',') || (string[i] == ';') || (string[i] == '=') || (string[i] == '[') || (string[i] == ']') ) {
            // Entrada no valida, contiene caracteres no validos para FAT
            // por lo tanto devolvemos 0 como si no hubieramos encontrado nada.
            return 0;
        }
    }

    return i;
}