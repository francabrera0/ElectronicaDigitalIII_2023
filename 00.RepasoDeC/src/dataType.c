#include <stdio.h>
#include "dataType.h"

void printDataType(void){
    /* Hay más tipos de datos que estos, estos son los primitivos
     * Los datos pueden ser signed o unsigned. En caso de no explicitarlo se interpreta como signed.
     * Rangos:
     *      signed --> -2^(n-1) a 2^(n-1)-1 (complemento a 2)
     *      unsigned --> 0 a 2^(n)-1 
     */


    //Char --> 1 byte --> -128 a 127
    printf("char size %lu\n", sizeof(char));
    //Imprime la representación en ascii 
    char character = 64;
    printf("Variable tipo char: %c \n",character);

    //Unsigned char --> 1 byte --> 0 a 255
    printf("unsigned char size %lu\n", sizeof(unsigned char));
    //Imprime la representación en ascii 
    unsigned char ucharacter = 126;
    printf("Variable de tipo unsigned char: %c \n",ucharacter);

    //int --> 4 byte --> -2147483648 a 2147483647
    printf("int size %lu\n", sizeof(int));
    int integer = 12;
    printf("Variable tipo int: %d \n",integer);

    /**
     * Probar hacer lo mismo con:
     *  unsigned int, short, unsigned short, long, unsigned long, float, double, long double
     *
    */
}