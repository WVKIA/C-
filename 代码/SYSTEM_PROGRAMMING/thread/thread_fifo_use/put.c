#include <stdio.h>
#include <sys/stat.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
void * write_t(void * arg)
{
    char buf[100];
    int *fsend = arg;
    while(1)
    {
        fgets(buf,100,stdin);
        if(strcmp(buf,"quit\n") == 0)
        {
            break;
        }
        write(*fsend,buf,100);
    }
    close(*fsend);
    return NULL;
}
int main()
{
    pthread_t pthread;

    int n;
    char buf[100];

    int fsend;
    int frecv;
    frecv  =open("fifo0",O_RDONLY);
    if(frecv < 0)
    {
        fprintf(stderr,"can't open the file\n");
        return -1;
    }

    fsend = open("fifo1",O_WRONLY);
    if(fsend < 0)
    {
        fprintf(stderr,"can't open\n");
        close(frecv);
        return -1;
    }

    int pt;
    pt = pthread_create(&pthread,NULL,write_t,&fsend);
    if(pt < 0)
    {
        fprintf(stderr,"can't create\n");
        close(frecv);
        close(fsend);
    }

    while(1)
    {
        n = read(frecv,buf,100);
        if(n ==0)
        {
            
            break;
        }
        printf("%s",buf);
    }
    close(frecv);
 
    pthread_join(pthread,NULL);
    return 0;
}
