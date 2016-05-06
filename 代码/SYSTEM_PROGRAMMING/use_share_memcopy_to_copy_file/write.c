#include <stdio.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <unistd.h>
int downsem(int semid,int index)
{
    struct sembuf semarray[1];
    semarray[0].sem_num = index;
    semarray[0].sem_op = -1;
    semarray[0].sem_flg = 0;
    return semop(semid,semarray,1);
}
int upsem(int semid,int index)
{
    struct sembuf semarray[1];
    semarray[0].sem_num = index;
    semarray[0].sem_op = 1;
    semarray[0].sem_flg = 0;
    return semop(semid,semarray,1);
}
int main(int argc, char * argv[])
{

    if(argc < 2)
    {
        fprintf(stderr,"please enter the file name in order to recv\n");
        return -1;
    }
    int pid;
    int semid;
    int shmid;
    char *ptmp;
    int *pint = NULL;
    shmid = shmget(0x8000,4096,IPC_CREAT|0664);
    if(-1 == shmid)
    {
        fprintf(stderr,"can't creat share memory\n");
        return -1;
    }
    ptmp = shmat(shmid,NULL,0);
    if(-1 == (int)ptmp)
    {
        fprintf(stderr,"can't attach the shm\n");
        return -1;
    }
    pid = open(argv[1],O_WRONLY,0664);
    if(-1 == pid)
    {
        fprintf(stderr,"can't open the file\n");
        shmdt(ptmp);
        ptmp = NULL;
        shmctl(shmid,IPC_RMID,NULL);
        return -1;
    }
    semid = semget(0x6000,0,0);
    if(-1 == semid)
    {
        shmdt(ptmp);
        ptmp = NULL;
        shmctl(shmid,IPC_RMID,NULL);
        close(pid);
        return -1;
    }
    while(1)
    {
        downsem(semid,1);
        pint = (int *)ptmp;
        if(0 == (*pint))
        {
            upsem(semid,0);
            break;
        }
        write(pid,ptmp+4,*pint);
        upsem(semid,0);
    }
    close(pid);

}
