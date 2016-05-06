#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"
void help(void)
{
    printf("HELP:\n");
}
/*
int addstu(struct student *phead,struct student *pstu)
{
    phead->pre->next = pstu;
    pstu->pre = phead->pre;
    pstu->next = phead;
    phead->pre = pstu;
    return 0;
}
*/
int addstu(struct student *phead,struct student *pstu)
{
    struct student *ptmp;
    if(pstu == NULL)
    {
        return -1;
    }
    for(ptmp = phead->next;ptmp != phead;ptmp = ptmp->next)
    {
        if(strcmp(ptmp->id,pstu->id) > 0)
        {
            break;
        }
    }
    ptmp->pre->next = pstu;                 // double situation can be merger
    pstu->pre = ptmp->pre;
    pstu->next = ptmp;
    ptmp->pre = pstu;
    return 0;
}



/*int addstu(struct student **pphead,struct student *pstu)
  {
  struct student *ptmp=NULL;
  struct student *p=NULL;
  if(NULL==(*pphead))
  {
 *pphead=pstu;
 }
 p=*pphead;

 else
 {
 for(p;NULL!=p->next;p=p->next)
 {


 }
 p->next=pstu;

 }
 return 0;
 }*/
int showall(struct student *phead)
{
    int num=0;
    struct student *ptmp;
    for(ptmp = phead->next;ptmp!=phead;ptmp=ptmp->next)
    {
        num++;
        showone(ptmp);
    }
    return num;
}
int rshowall(struct student *phead)
{
    struct student *ptmp = NULL;
    for(ptmp = phead->pre;ptmp != phead;ptmp = ptmp->pre)
    {
        showone(ptmp);
    }
    return 0;
}
/*int rshowall(struct student *phead)
{
    if(NULL==phead)
    {
        return 0;
    }
    if(NULL==phead->next)
    {
        showone(phead);
    }
    else
    {
        rshowall(phead->next);
        showone(phead);
    }
    return 0;
}*/

void showone(struct student *pstu)
{
    printf("id:%s   name:%s   age:%d   sex:%c\n",pstu->id,pstu->name,pstu->age,pstu->sex);
}
int destroyall(struct student *phead)
{
    int num=0;
    struct student *ptmp=NULL;
    struct student *ptmp1 = NULL;
    for(ptmp=phead->next ;ptmp!=phead;ptmp=ptmp1)
    {
        ptmp1=ptmp->next;
        free(ptmp);
        num++;
    }
    printf("destroy\n");
    return num;
}
struct student *findbyid(struct student *phead,char *id)
{
    struct student *ptmp = NULL;
    if(NULL==phead)
    {
        return NULL;
    }
    for(ptmp=phead->next;ptmp!=phead;ptmp=ptmp->next)
    {
        if(strcmp(ptmp->id,id)==0)
        {
            return ptmp;
            
        }

    }
    return NULL;
}
struct student *findbyname(struct student *phead,char *name,struct student *pre)
{
    struct student  *ptmp=NULL;
    if(NULL==pre)
    {
        pre=phead->next;
        if(strcmp(pre->name,name)==0)
        {
            return pre;
        }
    }

    ptmp=pre->next;
    for(ptmp;phead!=ptmp;ptmp=ptmp->next)
    {
        if(strcmp(ptmp->name,name)==0)
        {
            return ptmp;

        }
    }
    return NULL;
}


void delstu(struct student *phead,struct student *pstu)
{
    pstu->pre->next = pstu->next;
    pstu->next->pre = pstu->pre;
    free(pstu);
}
int reverse(struct student *phead)
{
    struct student *ptmp = phead->next;
    struct student *ptmp1 = NULL;
    phead->pre = phead->next = phead;
    for(ptmp;ptmp!=phead;ptmp = ptmp1)
    {
        ptmp1 = ptmp->next;
        phead->next->pre = ptmp;
        ptmp->next = phead->next;
        ptmp->pre = phead;
        phead->next = ptmp;
    }
}
int readfromfile(struct student *phead,char *file)
{
    int num=0;
    int n=0;
    struct student *pstu=NULL;
    FILE *fp=fopen(file,"r");
    if(NULL==fp)
    {
        return -1;
    }
    while(1)
    {
        pstu=malloc(sizeof(struct student));
        n=fread(pstu,sizeof(struct student),1,fp);
        if(0 == n)
        {
            free(pstu);
            pstu=NULL;
            break;
        }
        pstu->next=NULL;
        pstu->pre=NULL;
        addstu(phead,pstu);
        num++;
    }
    fclose(fp);
    return 0;
}
int savefile(struct student *phead,char *file)
{
    int num=0;
    struct student *ptmp = NULL;
    FILE *wp=fopen(file,"w");
    if(NULL==wp)
    {
        return 0;
    }
    
    
        for(ptmp = phead->next;ptmp!=phead;ptmp = ptmp->next)
        {
            fwrite(ptmp,sizeof(struct student),1,wp);
            num++;

        }
    
    fclose(wp);
    return num;
}






