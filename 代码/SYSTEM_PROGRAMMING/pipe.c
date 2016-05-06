#include <stdio.h>
#include <sys/wait.h>

#include <unistd.h>
#include <string.h>
int main()
{
    char buf[100];
    char name[20];
    int n;
    int i = 0;
    int tr;
    int pipefid[2];
    pid_t fd;
    int m = 0;
    int rt = 0;
    int pipetmp[2];


    rt = pipe(pipetmp);
    if(rt < 0)
    {
        return -1;
    }

    tr = pipe(pipefid);
    if(tr < 0)
    {
        return -1;
    }

    fd = fork();

    if(fd == 0)
    {
        close(pipetmp[0]);
        close(pipefid[1]);
        while(1)
        {
            n = read(pipefid[0],name,20);
            if(0 == n)
            {
               
                break;

            }
           for(i = 0;i < strlen(name);i++)
           {
               name[i] = toupper(name[i]);
           }
            write(pipetmp[1],name,strlen(name)+1);
           
        }
        close(pipetmp[1]);
        close(pipefid[0]);
    }
    else
    {
        close(pipefid[0]);
        close(pipetmp[1]);
        while(1)
        {
            printf("enter name\n");
            scanf("%s",name);
            if(strcmp(name,"quit") == 0)
            {
                close(pipefid[1]);
                close(pipetmp[0]);
                break;
            }

            write(pipefid[1],name,strlen(name) + 1);
            m = read(pipetmp[0],name,strlen(name)+1);
            if(0 == m)
            {   
                close(pipefid[1]);
                close(pipetmp[0]);
                break;

            }
            printf("%s\n",name);
        }
        wait(NULL);
    }
    return 0;
}
