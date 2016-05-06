#include <stdio.h>
#include <sys/sem.h>
int main()
{
    int semid;
    int rt = 0;
    union semun
    {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    }semval;

    semid = semget(0x6000,2,0664|IPC_CREAT);
    if(-1 == semid)
    {
        fprintf(stderr,"can't create semid\n");
        return -1;
    }

    semval.val = 1;
    rt = semctl(semid,0,SETVAL,semval);
    if(-1 == rt)
    {
        fprintf(stderr,"can't init_sem\n");
        semctl(semid,0,IPC_RMID);
        return -1;
    }

    semval.val = 0;
    rt = semctl(semid,1,SETVAL,semval);
    if(-1 == rt)
    {
        fprintf(stderr,"can't init_sem\n");
        semctl(semid,0,IPC_RMID);
        return -1;
    }
}
