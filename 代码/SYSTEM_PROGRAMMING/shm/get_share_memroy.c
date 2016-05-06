#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

int main()
{
    char * pstr;
    int shmid;
    char *pshm = NULL;
    int *pint = NULL;
    shmid = shmget(0x6000,4096,0);
    if(-1 == shmid)
    {
        fprintf(stderr,"can't create shm\n");
        return -1;
    }
    pshm = shmat(shmid,NULL,0);
    if(-1 == (int)pshm)
    {
        fprintf(stderr,"can't attach shem\n");
        return -1;
    }
    pint =(int *) pshm;
    printf("%d char\n",*pint);
    printf("%s\n",pshm+4);
    shmctl(shmid,IPC_RMID,NULL);
}
