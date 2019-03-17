//Mitch Lindsey
//cs 4760
//03-16-19
//
#ifndef PROJECT_THREE_SHMFUN_H
#define PROJECT_THREE_SHMFUN_H

void cleanSHM();
void sigHandle( int );
void sigChild();
void deleteMemory( char * );

extern int active;
extern int processLimit;
extern int activeLimit;
extern pid_t pids[20];


#endif //PROJECT_THREE_SHMFUN_H
