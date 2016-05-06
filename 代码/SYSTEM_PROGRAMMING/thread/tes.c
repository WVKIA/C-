#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
struct test
{
    int a;
    char *b;
};
struct test tmp = 
{
    .a = 4,
    .b= "wang"
};

void *start(void *arg)
{
    printf("new thread is created\n");
    return (void *)&tmp;
}
int main()
{
    char *ch = "wang";
    struct test *c;
    pthread_t pid;
    struct test *tmp;
    int rt;
    rt = pthread_create(&pid,NULL,start,NULL);
    if(rt != 0)
    {
        fprintf(stderr,"can't pthread create\n");
        return -1;
    }
    rt = pthread_join(pid,(void *)&tmp);
    if(rt != 0)
    {
        printf("thread is not exit\n");
        return -2;
    }
    printf("thread is exit number is  %d,string is %s\n", tmp->a,tmp->b);
    return 0;

}
