#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STUFILE   "studata.dat"

enum
{
    HELP,
    ADD,
    DEL,
    FIND,
    FINDN,
    SHOW,
    RSHOW,
    QUIT,
    SAVE,
    REVERT,
    NONE,
};

char *cmdstring[] = {
    "help",
    "add",
    "del",
    "find",
    "findname",
    "show",
    "rshow",
    "quit",
    "save",
    "revert"
};

int getCmdno(char *cmd)
{
    int i;
    int n = sizeof(cmdstring)/sizeof(char *);
    for(i=0;i<n;i++)
    {
        if(strcmp(cmd,cmdstring[i]) == 0)
        {
            break;
        }
    }
    return i;
}

int main(int argc,char *argv[])//char **argv
{
    char buf[1024];
    int cmdno;
    int rt;
    int quit = 0;
    char name[20];
    char id[20];
    int age;
    char sex;
    struct student stu;
    struct student *pstu = NULL;
    struct listhead *plist = NULL;
    struct listhead head;
    head.pre=head.next=&head;
    rt = readfromfile(&head,STUFILE);
    printf("read %d students\n",rt);
    printf("#####################################################\n");
    printf("#############welcom to student system################\n");
    printf("#####################################################\n");
    while(0 == quit)
    {
        printf("please input cmd:");
        fgets(buf,1024,stdin);
        buf[strlen(buf)-1] = '\0';
        if(strlen(buf) == 0)
        {
            continue;
        }
        cmdno=getCmdno(buf);
        switch(cmdno)
        {
            case HELP:
                printf("help\n");
                break;
            case ADD:
                printf("add\n");
                printf("please input student info\n");
                printf("please input student id\n");
                scanf("%s",id);
                printf("please input student name\n");
                scanf("%s",name);
                printf("please input student age\n");
                scanf("%d",&age);
                printf("please input student sex\n");
                fgets(buf,1024,stdin);
                scanf("%c",&sex);
                fgets(buf,1024,stdin);
                pstu = findbyid(&head,id);
                if(NULL != pstu)
                {
                    printf("id %s has existed now\n",id);
                    break;
                }
                pstu = malloc(sizeof(struct student));
                strcpy(pstu->id,id);
                strcpy(pstu->name,name);
                pstu->age = (char)age;
                pstu->sex = sex;
//                pstu->list.pre = pstu->list.next = NULL;
                addstu(&head,pstu);
                break;
            case DEL:
                printf("del\n");
                printf("please input id:");
                scanf("%s",id);
                fgets(buf,1024,stdin);
                pstu = findbyid(&head,id);
                if(NULL == pstu)
                {
                    printf("id %s is not exist\n",id);
                }
                else
                {
                    delstu(pstu);
                }
                break;
            case FIND:
                printf("find\n");
                printf("please input id:");
                scanf("%s",id);
                fgets(buf,1024,stdin);
                pstu = findbyid(&head,id);
                if(NULL == pstu)
                {
                    printf("id %s is not exist\n",id);
                }
                else
                {
                    showone(pstu);
                }
                break;
            case FINDN:
                printf("please input name:");
                scanf("%s",name);
                fgets(buf,1024,stdin);
                plist = &head;
                while(NULL != plist)
                {
                    pstu = findnamenext(&head,name,plist);
                    if(NULL != pstu)
                    {
                        showone(pstu);
                        plist=&pstu->list;
                    }
                    else
                    {
                        plist = NULL;
                    }
                }
                break;
            case SHOW:
                printf("show\n");
                showall(&head);
                break;
            case RSHOW:
                printf("rshow\n");
                rshowall(&head);
                break;
            case QUIT:
                quit=1;
                break;
            case SAVE:
                savetofile(&head,STUFILE);
                break;
            case REVERT:
                revert(&head);
                break;
            default:
                printf("no this cmd:%s\n",buf);
                break;
        }
    }
    destroyall(&head);
    return 0;
}

