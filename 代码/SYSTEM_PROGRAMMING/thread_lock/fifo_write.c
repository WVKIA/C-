#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
struct mytask
{
    char c;
};

int main()
{
    int pid;
    struct mytask * p= NULL;
    char ch[1024];
    pid = open("fifo",O_WRONLY);
    if(-1 == pid)
    {
        fprintf(stderr,"can't create\n");
        return -1;
    }
    while(1)
    {
        int i = 0;
        scanf("%s",ch);
        if(strcmp("quit",ch) == 0)
        {
            close(pid);
            break;
        }
        while('\0' != ch[i])
        {
            p = malloc(sizeof(struct mytask));
            p->c = ch[i];
            i++;
            write(pid,p,sizeof(struct mytask));
        }

    }
    return 0;
}
