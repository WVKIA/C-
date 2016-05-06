#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid;
    pid = fork();
    if(0 == pid)
    {
        execl("./a.out","./a.out",NULL);
    }
    else
    {
        wait(NULL);
        printf("gasdfsdf\n");
    }
}
