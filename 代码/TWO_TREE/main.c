#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"
#define FI   "student.dat"

enum
{
    HELP,
    ADD,
    DEL,
    FIND,
    FINDN,
    SHOW,
    RSHOW,
    REVERSE,
    QUIT,
    SAVE,
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
    "reverse",
    "quit",
    "save"
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
    struct student *root = NULL;
//    readfile(&phead,FI);
    //rt = readfromfile(&allstu,STUFILE);
    //printf("read %d students from file\n",rt);
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
                pstu = malloc(sizeof(struct student));
                strcpy(pstu->id,id);
                strcpy(pstu->name,name);
                pstu->age = (char)age;
                pstu->sex = sex;
                pstu->left = NULL;
                pstu->right = NULL;
               root= addstu(root,pstu);
                break;
              case DEL:
                printf("del\n");
                printf("please input id:");
                scanf("%s",id);
                fgets(buf,1024,stdin);
                pstu = findbyid(root,id);
                if(NULL == pstu)
                {
                    printf("id %s is not exist\n",id);
                }
                else
                {
                    root = delstu(root,pstu);
                }
                break;
               
            case FIND:
                printf("find\n");
                printf("please input id:");
                scanf("%s",id);
                fgets(buf,1024,stdin);
                pstu = findbyid(root,id);
                if(NULL == pstu)
                {
                    printf("id %s is not exist\n",id);
                }
                else
                {
                    showone(pstu);
                }
                break;/*
            case FINDN:
                printf("please input name:");
                scanf("%s",name);
                fgets(buf,1024,stdin);
                break;  */                    
            case SHOW:
                printf("show\n");
                showall(root);
                break;
            case RSHOW:
                printf("rshow\n");
        //        rshowall(root);
                break;
            case REVERSE:
                printf("reverse");
               // reverse(&phead);
                break;
            case QUIT:
                quit=1;
                break;
            case SAVE:
                write(root,FI);
                break;
            default:
                printf("no this cmd:%s\n",buf);
                break;
        }
    }
    destroyall(root);
    return 0;
}
