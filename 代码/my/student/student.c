#include <stdio.h>
#include "student.h"
#include <stdlib.h>
#include "list.h"
void add(struct list *phead,struct student *stu)

{
    list_add(phead,&stu->phead);
}
void show(struct list *phead)
{
    struct student *p = NULL;
    struct list *tmp = NULL;
    for(tmp = phead->next;tmp != phead;tmp=tmp->next)
    {
    p =(struct student*)( (unsigned long)(tmp) - (unsigned long)(&((struct student *)0)->phead));
    
    
        printf("%s  %s %d %c\n",p->name,p->id,p->age,p->sex);
    
    }
}
struct student * find(struct list *phead,char *pstu)
{
    struct student *p = NULL;
    struct list *ptmp = NULL;
    if(NULL == pstu)
    {
        return NULL;
    }
    for(ptmp = phead->next;ptmp != phead;ptmp = ptmp->next)
    {
    p =(struct student*)( (unsigned long)(ptmp) - (unsigned long)(&((struct student *)0)->phead));
        if(strcmp(p->id,pstu) == 0)
        {
            printf("%s %s %d %c\n",p->name,p->id,p->age,p->sex);
            return p;
        }
    }
    return NULL;
}

void del(struct list *phead)
{
    char buf[20];
    puts("enter id:\n");
    scanf("%s",&buf);
    struct student *ptmp = find(phead,buf);
    list_del(&(ptmp->phead));
}
struct student * findbyname(struct list *phead,char *name,struct student *pre)
{
    struct list *ptmp = NULL;
    struct student *p = NULL;
    if(NULL == pre)
    {
        ptmp = phead;
    }
    for(ptmp = pre->phead.nextl; ptmp != phead; ptmp = ptmp->next)
    {
    p =(struct student*)( (unsigned long)(ptmp) - (unsigned long)(&((struct student *)0)->phead));
        if(strcmp(p->id,name) == 0)
        {
            printf("%s %s %d %c\n",p->name,p->id,p->age,p->sex);
        }
    }
}
void destroy(struct list *phead)
{
    struct list *ptmp = NULL;
    struct student *p = NULL;
    struct list *ptmp1 = NULL;
    for(ptmp = phead->next,ptmp1 = ptmp->next;ptmp != phead;ptmp = ptmp1, ptmp1  = ptmp1->next)
    {
        
    p =(struct student*)( (unsigned long)(ptmp) - (unsigned long)(&((struct student *)0)->phead));
    free(p);
    p = NULL;
    }
    printf("the destroy\n");
    
}
