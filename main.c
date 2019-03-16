#include <stdio.h>
#include <unistd.h>
#include <sys/shm.h>
#include <bits/signum.h>
#include <signal.h>
#include <stdlib.h>
#include <wait.h>

pid_t pids[20];

int maxEver = 20;
int active = 0;

void cleanSHM();
void sigHandle(int);
void sigChild();

int main(int argc, char ** argv) {
    alarm(100);
    signal(SIGINT, sigHandle);
    signal(SIGALRM, sigHandle);
    signal(SIGCHLD, sigChild);

    char * infile = "input.txt";
    char * output = "output.txt";

    return 0;
}
void sigHandle(int cc){
    cleanSHM();
}
void cleanSHM(){
    int i;
    for (i =0; i< maxEver; i++) {
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
    for (i = 0; i < maxEver; i++) {
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