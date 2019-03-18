//Mitch Lindsey
//cs 4760
//03-16-19
//

#include <stdlib.h>
#include <sys/shm.h>
#include <stdio.h>
#include <memory.h>
#include <unistd.h>
#include "palin.h"
#include "shmFun.h"
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <semaphore.h>
#include <time.h>
#include <assert.h>


int isPalindrome(char []);
void writeFile(char []);
int wairfor(sem_t *sem);
void signal(sem_t *);
void naptime() ;
void criticalSection(char []);
sem_t * sem;
int workIsDone;
char buf[BUFF_sz];
int logIndex;


int main(int argc, char * argv[])
{
    int start = atoi(argv[1]);
    int stop = atoi(argv[2]);
    logIndex = atoi(argv[3]);
    char * palinList;

    int shmid = shmget (SHMKEY, SHM_sz, 0777); //shared memory
    if (shmid == -1)
        perror("child - error shmid");

    palinList =  ( shmat ( shmid, 0, 0));

    int i, p;

    for ( p = 0 , i = start ; i < stop ; i++ )
        buf[ p++ ] = palinList[ i ];
    buf[p]=0;



    char palinFileName[][12] ={"nopalin.out", "palin.out"};
    char * outFilename;

    if(isPalindrome(buf)) {
        sem = sem_open(SEM_PALIN, O_CREAT, 0644, 1);
        outFilename = palinFileName[1];
    } else{
        sem = sem_open(SEM_NOPALIN, O_CREAT, 0644, 1);
        outFilename = palinFileName[0];
    }




    int semValue;

    workIsDone = 0;
    for ( i = 0; i < 5; i++ ){
        if ( workIsDone )
            break;
        naptime();
        if ( !wairfor ( sem ) )
            continue;
        sem_getvalue(sem,&semValue);
        assert( ( semValue == 0 ) && "sem is not 0 going into critical section");
        criticalSection(outFilename);
        signal(sem);
    }


    sem_close(sem);
    exit(808);
}

int isPalindrome(char str[])
{
    int l = 0;
    size_t h = strlen(str) - 1;

    while (h > l)
    {
        if (str[l++] != str[h--])
            return 0;
    }
    return 1;
}

void writeFile(char * outfile){
    FILE* ofptr = fopen(outfile, "a");
    fprintf(ofptr, "pid: %u\t%i\t%s\n", getpid() , logIndex , buf);
    printf( "pid: %u\t%i\t%s\n", getpid() , logIndex , buf);

}

int wairfor(sem_t *sem) {
    time_t now = time(NULL);
    fprintf(stderr, "pid: %u\t- trywait -\t\t %s", getpid(),  ctime( &now ) );
    int n = sem_trywait(sem);
    if (n != 0)
        perror("try wait failed");
    return n;
}
void signal(sem_t * sem) {
    time_t now = time(NULL);
    fprintf(stderr, "pid: %u\t- signal  -\t\t %s", getpid(),  ctime( &now ) );
    int n = sem_post(sem);
    if (n != 0)
        perror("sem_post failed");
}
void naptime() {
    unsigned seed = (unsigned) time(NULL);
    srand(seed);
    sleep((unsigned) ((rand() % 9) + 1));
}
void criticalSection(char *outfile){
    time_t now = time(NULL);
    fprintf(stderr, "pid: %u\t-  enter  -\t\t %s", getpid(),  ctime( &now ) );
    sleep(2);
    int x;
    sem_getvalue(sem, &x);
    writeFile(outfile);
    workIsDone = 1;
    sleep(2);
    now = time(NULL);
    fprintf(stderr, "pid: %u\t-  exit   -\t\t %s", getpid(),  ctime( &now ) );
}
