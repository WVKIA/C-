#include <sys/sem.h>
#include <stdio.h>

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
int main()
{
    int i,semid;
    int n = 0;
    FILE * fp = fopen("data","w");
    if(NULL == fp)
    {
        fprintf(stderr,"can't open the file\n");
        return -1;
    }
    semid = semget(0x6000,0,0);
    if(-1 == semid)
    {
        fprintf(stderr,"can't creat semid\n");
        fclose(fp);
        return -1;
    }
    for(i = 0;i < 10000;i++)
    {
        printf("enter number");
        scanf("%d",&n);
        downsem(semid,0);

        fseek(fp,0l,SEEK_SET);
        fprintf(fp,"%d",n);
        fflush(fp);
        upsem(semid,1);
    }
    fclose(fp);
    return 0;
}
