//Mitch Lindsey
//cs 4760
//03-16-19
//


#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "readFile.h"


void readFile(const char *infile, char **palinList)
{
    size_t len;
    char temp[BUFF_sz];
    static int listSize = 0;

    palinList = ( char** ) malloc( ( size_t ) processLimit * sizeof( char * ) );


    FILE * fptr = fopen(infile, "r");
    if (!fptr){
        perror("could not open file");
        return;
    }
    while( feof( fptr ) ) {
        fgets(temp, BUFF_sz, fptr);
        len = strlen(temp);
        palinList[ listSize++ ] = ( char * ) malloc( len * sizeof( char ) );
    }
}

void freePalinList(char ** palinList){
    int i = 0;
    static int listSize;
    for (; i < listSize; i++){
        free(palinList[i]);
    }
    free(palinList);
}