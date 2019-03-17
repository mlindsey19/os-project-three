//Mitch Lindsey
//cs 4760
//03-16-19
//
#include "palin.h"

int isPalindrome(char []);


int main(int argc, char * argv[])
{
    int lineNumber = atoi(argv[1]);

    *palinList

    int shmid = shmget (SHMKEY, BUFF_SZ, 0777); //shared memory

    if (shmid == -1)
        perror("child - error shmid");

    palinList = ( int * ) ( shmat ( shmid, 0, 0));



    exit(19);
}

int isPalindrome(char str[])
{
    int l = 0;
    int h = strlen(str) - 1;

    while (h > l)
    {
        if (str[l++] != str[h--])
            return 1;
    }
    return 0;
}

