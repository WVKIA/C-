#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "student.h"
enum
{
    ADD,
    FIND,
    SHOW,
    DEL,
    QUIT,
    NONE
};
char *cmdstring[]=
{
    "add",
    "find",
    "show",
    "del",
    "quit"
};
int getcmd(char *cmd)
{
    int i;
    int n = sizeof(cmdstring) / sizeof(char *);
    for(i = 0;i < n;i++)
    {
        if(strcmp(cmd,cmdstring[i]) == 0)
        {
            break;
        }
    }
    return i;
}
int main()
{
    int quit = 0;
    struct student *stu = NULL;
    struct list phead;
    phead.next = phead.pre = &phead;
    char name[20];
    char id[20];
    int age;
    char sex;
    char buf[30];
    while(0 == quit)
    {
        fgets(buf,30,stdin);
        buf[strlen(buf) -1] = '\0';
        int n = getcmd(buf);
        switch (n)
        {
            case ADD:
                printf("enter name");
                scanf("%s",&name);
                puts("enter id");
                scanf("%s",&id);
                printf("enter age");
                scanf("%d",&age);
                printf("enter sex");
                fgets(buf,30,stdin);
                scanf("%c",&sex);
                fgets(buf,30,stdin);
                stu = malloc(sizeof(struct student));
                strcpy(stu->name,name);
                strcpy(stu->id,id);
                stu->age = (char)age;
                stu->sex = sex;

                add(&phead,stu);
                break;
            case FIND:
                puts("enter the id your want to find");
                scanf("%s",&buf);
                stu = find(&phead,buf);
                break;
            case SHOW:
                show(&phead);
                break;
            case DEL:
                del(&phead);

                puts("del");
                break;
            case QUIT:
                quit  = 1;
                break;
           default:
                printf("enter another cmd\n");
        }
    }
    destroy(&phead);
    return 0;
}
