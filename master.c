//Mitch Lindsey
//cs 4760
//03-16-19
//

#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <signal.h>
#include <stdlib.h>
#include <wait.h>
#include <memory.h>
#include "checkArgs.h"
#include "readFile.h"
#include "shmFun.h"

pid_t pids[PLIMIT];

int processLimit = 6;
int activeLimit = 3;
int active = 0;
int total = 0;
char * paddr;



char * palinList;

int main(int argc, char ** argv) {
//    int errno;
//    int status;
    char execArg[3][3];
    char palin[] = "palin";
    char path[] = "./palin";
    int *palinLen = malloc( PLIMIT * sizeof( int ) );


    alarm(100);
    signal(SIGINT, sigHandle);
    signal(SIGALRM, sigHandle);

    char infile[BUFF_sz] = "input.txt";
    char output[BUFF_sz] = "output.txt";


    checkArgs(infile, output, argc, argv, &processLimit, &activeLimit);
    createMemory();
    palinList = paddr;
    readFile(infile, palinLen);


    for (total = 0 ; total < processLimit ; ) {

        if ( ( pids[ total ] = fork() ) < 0 ) {
            perror("error forking new process");
            return 1;
        }
        if ( pids[ total ] == 0 ) {
            int a = total ? palinLen[ total - 1 ] : 0;
            int b = palinLen[ total ];
            sprintf( execArg[0],"%i", a );
            sprintf( execArg[1],"%i", b );
            sprintf(execArg[2], "%i", total);

            execl( path, palin, execArg[0], execArg[1], execArg[2], NULL );
        }
        total++, active++;
        if( active >= activeLimit )
            sigChild();
    }

    while( ( total < processLimit ) && ( active != 0 ) );

    free(palinLen);
    cleanSHM();
    return 0;
}