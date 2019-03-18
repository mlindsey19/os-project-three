//Mitch Lindsey
//cs 4760
//03-16-19
//
#ifndef PROJECT_THREE_SHMFUN_H
#define PROJECT_THREE_SHMFUN_H
#define BUFF_sz 64
#define SHMKEY 0225201 //shared memory key
#define PLIMIT 20
#define SHM_sz sizeof(char[PLIMIT * BUFF_sz])
#define SEM_PALIN "/sem_palin"
#define SEM_NOPALIN "/sem_no_palin"


void cleanSHM();
void sigHandle( int );
void sigChild();
void deleteMemory();

void createMemory();


extern int active;
extern int processLimit;
extern int activeLimit;
extern pid_t pids[ PLIMIT ];
extern char *palinList;
extern int total;
extern char * paddr;



#endif //PROJECT_THREE_SHMFUN_H
