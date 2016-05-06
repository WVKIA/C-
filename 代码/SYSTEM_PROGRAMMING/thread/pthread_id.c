#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>
void *create(void *arg)
{
    printf("new thread >>>");
    printf("thread_tid == %u \n",(unsigned int)pthread_self());
    printf("thread pid is %d\n",getpid());
    return (void *)0;
}
int main()
{
    pthread_t pid;
    int error;
    printf("Main thread is starting...");
    error =  pthread_create(&pid,NULL,create,NULL);
    if(0 != error)
    {
        printf("thread is not created...\n");
        return -1;
    }
    printf("main pid is %d\n",getpid());
    pthread_join(pid,NULL);
    return 0;
}
