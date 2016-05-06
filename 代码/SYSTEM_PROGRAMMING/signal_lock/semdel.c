#include <stdio.h>
#include <sys/sem.h>
int main()
{
    int semid;
    semid = semget(0x6000,0,0);
    if(-1 == semid)
    {
        fprintf(stderr,"can't not create\n");
        return -1;
    }
    semctl(semid,0,IPC_RMID);
    return 0;
}
