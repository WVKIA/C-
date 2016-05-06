#include <stdio.h>
#include <string.h>
#include <poll.h>
#include <fcntl.h>
#include <unistd.h>

int main()
{
    int i;
    int fdsend;
    int fdrecv;
    int n;
    int rt;
    int quit = 0;
    char buf[1024];
    struct pollfd fds[2];
    fdsend = open("fifo0",O_WRONLY);
    if(fdsend < 0)
    {
        fprintf(stderr,"can't open\n");
        return -1;
    }
    fdrecv = open("fifo1",O_RDONLY);
    if(fdrecv < 0)
    {
        close(fdsend);
        fprintf(stderr,"can't open");
        return -1;
    }
    fds[0].fd = 0;
    fds[0].events = POLLIN;
    fds[1].fd = fdrecv;
    fds[1].events = POLLIN;
    while(quit == 0)
    {
        rt = poll(fds,2,-1);
        if(rt < 0)
        {
            fprintf(stderr,"can;t poll\n");
            continue;
        }
        for(i = 0;i < 2;i++)
        {
            if(POLLIN == fds[i].revents)
            {
                n = read(fds[i].fd,buf,1023);
                if(n == 0)
                {
                    quit = 1;
                    break;
                }
                buf[n] = '\0';
                if(i == 0)
                {
                    if(strcmp(buf,"quit\n") == 0)
                    {
                        quit = 1;
                        break;
                    }
                    write(fdsend,buf,n);
                }
                else
                {
                    printf("%s",buf);
                }
            }
        }
    }
    close(fdsend);
    close(fdrecv);
}
