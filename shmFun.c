//Mitch Lindsey
//cs 4760
//03-16-19
//
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <wait.h>
#include <sys/shm.h>
#include <semaphore.h>
#include "shmFun.h"
#include <fcntl.h>           /* For O_* constants */



int shmid;
sem_t * palin_sem;
sem_t * nopalin_sem;


void sigHandle(int cc){
    cleanSHM();
}
void cleanSHM(){
    int i;
    for (i =0; i < processLimit; i++) {
        if (pids[i] > 0) {

            kill(pids[i], SIGTERM);
        }
    }
    deleteMemory();
    //   fclose(ofpt);

}
void sigChild() {
    pid_t pid;
    int i, status;
    for (i = 0; i < processLimit; i++) {
        if (pids[i] > 0) {
            pid = waitpid(pids[i], &status, 0);
            if (WIFEXITED(status) && WEXITSTATUS(status) == 808 && pid != 0 ) {
                pids[i] = 0;
                printf( "term pid:%u\n", pid );
                active--;
            }
        }
    }
}

void createMemory(){
    shmid = shmget (SHMKEY, SHM_sz, 0777 | IPC_CREAT);

    if (shmid == -1)
        perror("parent - error shmid");

    paddr = ( char * ) ( shmat ( shmid, 0,0));
    palin_sem = sem_open(SEM_PALIN, O_CREAT, 0644, 1);
    nopalin_sem = sem_open(SEM_NOPALIN, O_CREAT, 0644, 1);


}


void deleteMemory() {
    int er;

    shmctl(shmid, IPC_RMID, NULL);
    if ((er = shmdt(paddr)) == -1) {
        perror("err shmdt:");
    }

    sem_unlink(SEM_PALIN);
    sem_close(palin_sem);
    sem_unlink(SEM_NOPALIN);
    sem_close(nopalin_sem);
}

