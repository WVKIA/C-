
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"

int addstu(struct listhead *phead,struct student *pstu)
{

    struct listhead *ptmp = NULL;
    struct student *pstu1 = NULL;
    list_for_each(ptmp,phead)
    {
        pstu1 = container_of(ptmp,struct student,list);
        if(strcmp(pstu1->id,pstu->id)>0)
        {
            break;
        }
    }
    list_add_pre(ptmp->pre,&pstu->list);
    return 0;
}
int showall(struct listhead *phead)
{
    struct listhead *ptmp = NULL;
    struct student *pstu = NULL;
    int num = 0;
    list_for_each(ptmp,phead)
    {
        pstu = container_of(ptmp,struct student,list);
        showone(pstu);
    }
    return num;
}
int rshowall(struct listhead *phead)
{
    int num=0;
    struct listhead *ptmp = NULL;
    struct student *pstu = NULL;
    list_for_each_pre(ptmp,phead)
    {
        pstu=container_of(ptmp,struct student,list);
        showone(pstu);
        num++;
    }
    return num;
}

void showone(struct student *pstu)
{    
    printf("id:%s name:%s age:%d sex:%c\n",pstu->id,pstu->name,pstu->age,pstu->sex);
}

int destroyall(struct listhead *phead)
{
    int num = 0;
    struct student *pstu = NULL;
    struct listhead *ptmp = NULL;
    struct listhead *ptmp1 = NULL;
    list_for_each_safe(ptmp,ptmp1,phead)
    {
        pstu = container_of(ptmp,struct student,list);
        free(pstu);
        num++;
    }
    return num;
}

struct student *findnamenext(struct listhead *phead,char *name,struct listhead *pre)
{
    struct listhead *pos = NULL;
    struct student *pstu = NULL;
    for(pos=pre->next;pos!=phead;pos=pos->next)
    {
        pstu = container_of(pos,struct student,list);
        if(strcmp(pstu->name,name) == 0)
        {
            return pstu;
        }
    }
    return NULL;
}
struct student *findbyid(struct listhead *phead,char *id)
{
    struct listhead *pos = NULL;
    struct student *pstu = NULL;
    list_for_each(pos,phead)
    {
        pstu = container_of(pos,struct student,list);
        if(strcmp(pstu->id,id) == 0)
        {
            return pstu;
        }
    }
    return NULL;
}
int delstu(struct student *pstu)
{
    list_del(&pstu->list);
    return 0;
}
int revert(struct listhead *phead)
{
}
int readfromfile(struct listhead *phead,char *file)
{
    int n = 0;
    int num = 0;
    struct student *p = NULL;
    FILE *fp = fopen(file,"r");
    if(NULL == fp)
    {
        return 0;
    }
    while(1)
    {
        p = malloc(sizeof(struct student));
        n = fread(p,sizeof(struct student),1,fp);
        if(0 == n)
        {
            free(p);
            p = NULL;
            break;
        }
        addstu(phead,p);
        num++;
    }
    fclose(fp);
    return num;
}
int savetofile(struct listhead *phead,char *file)
{
    int num = 0;
    struct listhead *ptmp = NULL;
    struct student *pstu  = NULL;
    FILE *fp = fopen(file,"w");
    if(NULL == fp)
    {
        return 0;
    }
    list_for_each(ptmp,phead)
    {
        pstu = container_of(ptmp,struct student,list);
        fwrite(pstu,sizeof(struct student),1,fp);
    }
    fclose(fp);
    return num;
}
