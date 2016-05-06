#include "student.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int addstu(struct student **pphead)
{
    char buf[1024];
    struct student *stu =NULL;
  
    int ch; 
    char name[20];
    char id[20];
    int age;
    char sex;
    printf("enter id\n");
    scanf("%s",&id);
    printf("enter name\n");
    scanf("%s",&name);
    printf("enter age\n");
    scanf("%d",&age);
    printf("this is age\n");
    
       
   fgets(buf,1024,stdin);
    printf("enter sex\n");    
    
    scanf("%c",&sex);
printf("this is sex\n");
    stu = malloc(sizeof(struct student ));
    strcpy(stu->name,name);
    strcpy(stu->id,id);
    stu->age =(char) age;
    stu->sex = sex;
    stu->next = NULL;
    
    if(NULL == *pphead)
    {
        *pphead = stu;
    }
    else
    {
        struct student *p = *pphead;
        for(;NULL != p->next;p = p->next)
        {
           ; 
        }
        (p->next) = stu;
    }
    printf("this is add\n");
}
int show(struct student *phead)
{
    int num = 0;
    struct student *p;
    for(p = phead;NULL != p;p = p->next)
    
    {
        showone(p);
        num ++;
    }
    return num;
}
void showone(struct student *p)

{
    printf("id %s; name %s; age %d; sex %c;\n",p->id,p->name,p->age,p->name);
}
void destroy(struct student *phead)
{
    struct student *ptemp = NULL;
    for(phead; NULL != phead;phead = ptemp)
    {
        ptemp = phead->next;
        free(phead);
        printf("this is destroy\n");

    }
}
