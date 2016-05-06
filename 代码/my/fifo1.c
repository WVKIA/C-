#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
int main()
{
    int n;
    char buf[10];
    int frecv;
    frecv = open("fifo",O_RDONLY);
    if(frecv < 0)
    {
        fprintf(stderr,"can't open\n");
        return -1;
    }

    int fsend;
    fsend = open("fifo1",O_WRONLY);
    if(frecv < 0)
    {
        close(frecv);
        return -1;
    }

    pid_t pid;
    pid = fork();
    if(0 == pid)
    {
        close(frecv);
        while(1)
        {
            fgets(buf,10,stdin);
            if(strcmp(buf,"quit\n") == 0)
            {
                close(fsend);
                break;
            }
            write(fsend,buf,10);
        }
    }
    else
    {
        close(fsend);
        while(1)
        {
            n = read(frecv,buf,10);
            if(n == 0)
            {
                close(fsend);
                break;
            }
            printf("%s\n",buf);
        }
        wait(NULL);
    }
    close(fsend);
    close(frecv);
}
