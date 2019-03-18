//Mitch Lindsey
//cs 4760
//03-16-19
//


#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "readFile.h"


void readFile(const char *infile, int *palinLen)
{
    int len =0;
    int totlen = 0;
    char temp[BUFF_sz];
    int listSize = 0;

    FILE * fptr = fopen(infile, "r");
    if (!fptr){
        perror("could not open file");
        return;
    }
    memset( palinList, 0, sizeof(char) * BUFF_sz * PLIMIT );

    while( !feof( fptr ) ) {
        fgets(temp, BUFF_sz, fptr);
        len = (int) strlen(temp) - 1;
        palinLen[ listSize++ ] = len + totlen;
        totlen += len;
        temp[ len ] = 0; //replace newline '\n' with null
        strcat(palinList, temp);
        memset( temp, 0, sizeof(temp) );

    }
}
