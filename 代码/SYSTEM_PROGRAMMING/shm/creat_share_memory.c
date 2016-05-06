#include <stdio.h>
#include <string.h>
#include <sys/shm.h>

int main(int argc, char * argv[])
{
    char * pstr;
    int shmid;
    char *pshm = NULL;
    int *pint = NULL;
    if(argc < 2)
    {
        pstr = "hello world share memroy\n";

    }
    else
    {
        pstr = argv[1];
    }
    shmid = shmget(0x6000,4096,IPC_CREAT|0664);
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
    strcpy(pshm+4, pstr);
    pint  = (int*)pshm;
    *pint =strlen(pstr);

}
