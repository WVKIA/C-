#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main()
{
    pid_t pid;
    int fdsent;
    char buf[100];

    fdsent = open("fifo0",O_WRONLY);
    int n;
    if(fdsent < 0)
    {
        fprintf(stderr,"can;t open the file\n");
        return -1;
    }

    int fdrecv;
    fdrecv = open("fifo1",O_RDONLY);
    if(fdrecv < 0)
    {
        fprintf(stderr,"can't open the file\n");
        close(fdsent);
        return -1;
    }
    pid = fork();
    if(pid == 0)
    {
        close(fdsent);
        while(1)
        {
            n = read(fdrecv,buf,100);
            if(n == 0)
            {
             
                break;
            }
            printf("%s",buf);
        }
        close(fdrecv);
    }
    else
    {
        close(fdrecv);
        while(1)
        {
        fgets(buf,100,stdin);
        if(strcmp(buf,"quit\n") == 0)
        {
            break;
        }
        write(fdsent,buf,100);
        }
       close(fdsent);
       wait(NULL);
    }
    close(fdrecv);
    close(fdsent);
    return 0;
}
