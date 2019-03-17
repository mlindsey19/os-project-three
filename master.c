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



int main(int argc, char ** argv) {
    pid_t pids[20];

    int processLimit = 4;
    int activeLimit = 2;
    int active = 0;

    char ** palinList;

    alarm(100);
    signal(SIGINT, sigHandle);
    signal(SIGALRM, sigHandle);
    signal(SIGCHLD, sigChild);

    char  infile[ BUFF_sz ] = "input.txt";
    char  output[ BUFF_sz ] = "output.txt";

    checkArgs(infile, output, argc, argv, &processLimit, &activeLimit);
    readFile(infile, palinList);


    return 0;
}