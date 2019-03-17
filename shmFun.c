//Mitch Lindsey
//cs 4760
//03-16-19
//
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <wait.h>
#include <sys/shm.h>
#include "shmFun.h"


int shmid;

void sigHandle(int cc){
    cleanSHM();
}
void cleanSHM(){
    int i;
    for (i =0; i< processLimit; i++) {
        if (pids[i] > 0) {

            kill(pids[i], SIGTERM);
        }
    }
    fprintf(ofpt, "final clock time: %is %in\n", );
    deleteMemory(paddr);
    fclose(ofpt);
}
void sigChild() {
    pid_t pid;
    int i, status;
    for (i = 0; i < processLimit; i++) {
        if (pids[i] > 0) {
            pid = waitpid(pids[i], &status, WNOHANG);
            if (WIFEXITED(status) && WEXITSTATUS(status) == 19 && pid != 0) {

                pids[i] = 0;
                fprintf(ofpt, "term pid:%u at %is %in\n", pid, );
                active--;

            }

        }

    }
}

char * createMemory(){
    char * paddr;
    shmid = shmget (SHMKEY, BUFF_SZ, 0777 | IPC_CREAT);

    if (shmid == -1)
        perror("parent - error shmid");

    paddr = ( char * ) ( shmat ( shmid, 0,0));

    return paddr;
}


void deleteMemory(char * paddr) {
    int er;

    shmctl(shmid, IPC_RMID, NULL);
    if ((er = shmdt(paddr)) == -1) {
        perror("err shmdt:");
    }
}