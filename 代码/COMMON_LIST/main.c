#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#define STUFILE "studata.dat"
enum
{
    HELP,
    ADD,
    DEL,
    FIND,
    FNAME,
    SHOW,
    RSHOW,
    REVER,
    QUIT,
    SAVE,
    MODIFY,
    NONE
};
char *cmdstring[]={
    "help",
    "add",
    "del",
    "find",
    "f-name",
    "show",
    "rshow",
    "rever",
    "quit",
    "save",
    "modify"



};
int getCmdno(char *cmd)
{
    int i;
    int n=sizeof(cmdstring)/sizeof(char *);
    for(i=0;i<n;i++)
    {
        if(strcmp(cmd,cmdstring[i])==0)
        {
            break;
        }
    }
    return i;
}

int main(int argc,char *argv[])
{
    int a=0;
    char buf[1024];
    int cmdno;
    int quit=0;
    char name[20];
    char id[20];
    int rt;
    int age;
    char sex;
    struct student *pstu;
    struct student stu;
    struct listhead phead;
    phead.next = phead.pre = &phead;
   // readfromfile(&phead,STUFILE);
    //struct allstudent allstu;
    //rt=init_allstu(&allstu);
    printf("****************************************************************\n");
    printf("please input cmd:");
    if(rt==-1)
    {
        return -1;
    }
    while(0==quit)
    {
        fgets(buf,1024,stdin);
        buf[strlen(buf)-1] = '\0';
        cmdno=getCmdno(buf);
        switch(cmdno)
        {
            case HELP:
                 help();

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
               // strcpy(stu.id,id);
               // strcpy(stu.name,name);
               // stu.age=(char)age;
               // stu.sex = sex;
               // addbyorder(&allstu,&stu);
                pstu = malloc(sizeof(struct student));
                if(NULL==pstu)
                {
                    printf("no\n");
                    break;
                }
                strcpy(pstu->id,id);
                strcpy(pstu->name,name);
                pstu->age=(char)age;
                pstu->sex=sex;
               
                addstu(&phead,pstu);
                
                break;
            case DEL:
                printf("please input student id\n");
                scanf("%s",id);
  //              pstu=findbyid(&phead,id);
                if(NULL==pstu)
                {
                    printf("%s can not exit\n",id);
                    break;
                }
                
                    delstu(pstu);
                    free(pstu);
                    pstu=NULL;
                
                
                break;
    /*        case FIND:
                printf("please input student id\n");
                scanf("%s",id);
                pstu=findbyid(&phead,id);
                if(NULL==pstu)
                {
                    printf("no this student\n");
                    break;
                }
                showone(pstu);
                 
                break;
            case FNAME:
                printf("please input name:");
                scanf("%s",name);
                pstu=NULL;
                do
                {
                    pstu=findbyname(&phead,name,pstu);
                    if(NULL!=pstu)
                    {
                        showone(pstu);
                    }
                }while(NULL!=pstu);
                break;*/
            case SHOW:
                showall(&phead);
                printf("please input cmd:");
                break;
    /*        case RSHOW:
                rshowall(&phead);
                printf("please input cmd:");
                break;
            case REVER:

               reverse(&phead);
               printf("please input cmd:");
                break;*/
            case QUIT:


                quit=1;
                break;
         /*   case SAVE:
                savefile(&phead,STUFILE);
                printf("please input cmd:");
               break;
            case MODIFY:
              
               break;
*/


            default:
                printf("please input cmd:");
                break;
                
        }
    }
    destroyall(&phead);

    return 0;
}


