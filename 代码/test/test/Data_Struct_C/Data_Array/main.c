#include <stdio.h>
#include <string.h>
#include "student.h"
#define FILENAME "student.dat"
enum
{
    //HELP,
    ADD,
  //  DEL,
   // FIND,
   // FIND_NAME,
    SHOW,
    QUIT,
   // SAVE,
    NONE
};
char * cmdstring[] = {
   // "help",
    "add",
   // "del",
   // "find",
   // "find_name",
    "show",
    "quit",
   // "save"

};

int getCmdno(char *cmd)
{
    int i;
    int n = sizeof(cmdstring) / sizeof(char *);
    for(i = 0; i < n; i++)
    {
        if(strcmp(cmd,cmdstring[i]) == 0)
        {
            break;
        }
    }
    return i;
}

int main(int argc,char *argv[])
{
    struct student * pstu;
    struct student stu;
    struct allstudent allstu;
    int rt = initallstudent(&allstu);
    if(-1 == rt)
    {
        printf("Can't malloc!");
    }
    
    

    char name[20];
    char id[20];
    int age;
    char sex;
    char buf[1024];
    int cmdno;
    int quit = 0;
    
//   rt = readfile(&allstu,FILENAME);
   printf("there are %d student has been read!\n",rt);
    printf("*******************************STUDENT SYSTEM****************************\n");
    while(quit == 0)
    {
        printf("Enter your operation!\n");
        printf("**Enter add ,find ,del***\n");
        printf("***      show (or quit)****** \n");
        fgets(buf,1024,stdin);
        buf[strlen(buf) - 1] = '\0';
        if(strlen(buf) == 0)
        {
            continue;
        }
        cmdno = getCmdno(buf);
        switch (cmdno)
        {
     /*       case HELP:
                printf("HELP\n");
                printf("please chioce add ,find , del , or show!\n");
                break;               */
            case ADD:
                printf("ADD you want to insert\n");
                printf("please input student id\n");
                scanf("%s",&id);
                printf("please input student name\n");
                scanf("%s",&name);
                printf("please input student age\n");
                scanf("%d",&age);
                printf("please input student sex\n");
                fgets(buf,1024,stdin);
                scanf("%c",&sex);
                strcpy(stu.id,id);
                strcpy(stu.name,name);
                stu.age = age;
                stu.sex = sex;
                addstu(&allstu,&stu);
                int ch;
                while(( ch = getchar()) != '\n')
                {
                    continue;
                }
                break;
   /*         case DEL:
                printf("DEL\n");
                printf("Enter the id that you want to delete:");
                scanf("%s",&id);
                delstu(&allstu,id);
                printf("%s has been deleted!\n",id);
                break;
            case FIND:
                printf("FIND\n");
                printf("Enter the id that you want to find:");
                scanf("%s",&id);
                printf("The student you want to find is :");
                
                pstu = findstu(&allstu,id);
                if(NULL == pstu)
                {
                    printf("Can't find the id!\n");
                }
                break;
            case FIND_NAME:
                printf("Enter the name you want to find:\n");
                scanf("%s",&name);
                pstu = NULL;
                printf("The student you want to find is:\n");
              do
              {
                pstu = find_name(&allstu,name,pstu);
                if(NULL == pstu)
                {
                    printf("Can't find the name!\n");
                }
              }while(NULL != pstu);
              */
/*            case SHOW:
                printf("SHOW\n");
                show(&allstu);
                printf("Enter your next operation!\n");
                break;
                */
            case QUIT:
                quit = 1;
                printf("quit\n");
                break;
        /*    case SAVE:
               rt= savefile(&allstu,FILENAME);
               printf("the %d student has been saved!\n",rt);
               break;
               */
            default:
                printf("can't find the cmd: %s\n",buf);
                break;
        }
    }
 destroyallstudent(&allstu);
    return 0;
}










