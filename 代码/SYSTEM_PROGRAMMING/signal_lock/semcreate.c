#include <stdio.h>
#include <sys/sem.h>

int main()
{
    int semid = 0;
    int rt;
    union semun
    {
        int val;
    }semval;
    semid = semget(0x6000,2,0664|IPC_CREAT);  //  semid jian li liang ba suo  semid build in two lock to 
    if(-1 == semid)
    {
        fprintf(stderr,"can't not create sem\n");
        return -1;
    }
    semval.val = 1;                                   // she zhi wei baio zhi wei 1;
    rt = semctl(semid,0,SETVAL,semval);                      //di biao zhi wei 0 de xin hao liang 
                                                        // di yi  ba shuo  wei 1
    if(-1 == rt)
    {
        fprintf(stderr,"can not init sem\n");
        semctl(semid,0,IPC_RMID);
        return -1;
    }
    semval.val = 0;                                 // she zhi wei biao zhi wei 0
                                                                    // di er ba suo wei 0
    rt = semctl(semid,1,SETVAL,semval);                   //xia biao wei 0 de she zhi wei 0  
    if(-1 == rt)
    {
        fprintf(stderr,"can't not init sem\n");
        semctl(semid,0,IPC_RMID);
        return -1;
    }
    return 0;
}
