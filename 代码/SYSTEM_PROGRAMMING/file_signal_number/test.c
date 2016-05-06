#include <fcntl.h>
#include <stdio.h>
int main(int argc,char *agrv[])
{
    int n;
    int a;
    char ch;
    char bf[1];
    char buf[1];
    if(argc < 2)
    
    {
        fprintf(stderr,"canshu\n");
        return -1;
    }
    int fd_secret  = open("hello.c",O_RDONLY);
    if(fd_secret < 0)
    {
        fprintf(stderr,"can;t  open the file\n");
        return -1;
    }
    int fd = open("hello.m",O_WRONLY|O_CREAT|O_TRUNC);
    if(fd < 0 )
    {
        fprintf(stderr,"can't open the file\n");
        close(fd_secret);           //  the previous file has been open , you must close the file!!!!!!!!!!!!
        return -1;
    }
    while(1)
    {
        n = read(fd_secret,buf,1);
        if(0 == n)
        {
            break;
        }
        ch = buf[0] ^ 03;
        bf[0] = ch;
        write(fd,bf,n);
    }
    close(fd);
    close(fd_secret);
    return 0;
}
