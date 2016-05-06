
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"

#if 0
int addstu(struct student **pphead,struct student *pstu)
{
    struct student *p=NULL;
    if(NULL == (*pphead))
    {
        *pphead = pstu;
    }
    else
    {
        p = *pphead;
        for(p;NULL != p->next;p=p->next)
        {
            ;
        }
        p->next = pstu;
    }
    return 0;
}
#endif
int addstu(struct student **pphead,struct student *pstu)
{
    struct student *pre = NULL;
    struct student *ptmp = NULL;
    if(NULL == pstu)
    {
        return 0;
    }
    if(NULL == *pphead)
    {
        *pphead = pstu;
    }
    else if(strcmp(pstu->id,(*pphead)->id)<0)
    {
        pstu->next = *pphead;
        *pphead    = pstu;
    }
    else
    {
        pre = *pphead;
        ptmp = pre->next;
        while(NULL != ptmp)
        {
            if(strcmp(ptmp->id,pstu->id)>0)
            {
                break;
            }
            pre = ptmp;
            ptmp = ptmp->next;
        }
        pstu->next = ptmp;
        pre->next = pstu;
    }
    return 0;
}
int showall(struct student *phead)
{
    int num = 0;
    for(phead;NULL!=phead;phead=phead->next)
    {
        num++;
        showone(phead);
    }
    return num;
}
#if 0
int rshowall(struct student *phead)
{
    int num = 0;
    struct student *ptmp = NULL;
    struct student *pltime  = NULL;
    if(NULL == phead)
    {
        return 0;
    }
    while(pltime != phead)
    {
        ptmp = phead;
        while(pltime != ptmp->next)
        {
            ptmp=ptmp->next;
        }
        num++;
        showone(ptmp);
        pltime = ptmp;
    }
    return num;
}
#endif
int rshowall(struct student *phead)
{
    if(NULL == phead)
    {
        return 0;
    }
    if(NULL == phead->next)
    {
        showone(phead);
    }
    else
    {
        rshowall(phead->next);
        showone(phead);
    }
}
/*void reverse(struct student **phead)
{
    if(NULL == *phead)
    {
        return ;
    }
    struct student *ptmp = NULL;
    struct student *current = *phead;
    struct student *new = NULL;
    struct student *old = NULL;
    while(NULL != current)
    {
        old = current->next;
        new = current;
        current->next = ptmp;
        ptmp = current;
        current = old;
    }
    *phead = new;
}
*/
void reverse(struct student **phead)

{
    struct student *current = *phead;
    struct student *pnew = NULL;
    struct student *pold = NULL;

    current = *phead;
    while(NULL != current)
    {
        pold = current->next;
        current->next = pnew;
        pnew = current;
        current = pold;
    }
    *phead = pnew;
}
/*
struct student *reverse(struct student *phead)
{
    struct student *newphead = NULL;
    struct student *current = NULL;
    while(NULL != phead)
    {
        current = phead;
        phead = phead->next;            //delete "current" from the first list
        current->next = NULL;
        current->next = newphead;
        newphead = current;              //use the head_insert to insert "current"
    }
    return newphead;
}
*/
/*void reverse(struct student **phead)                 // 
{


    struct student *currentp = *phead;
    struct student *pleft = NULL;
    struct student *pright = NULL;


    while (currentp != NULL)
    {
        pright = currentp->next;
        currentp->next = pleft;
        pleft = currentp;
        currentp = pright;
    }
    *phead = pleft;
}
*/



void showone(struct student *pstu)
{    
    printf("id:%s name:%s age:%d sex:%c\n",pstu->id,pstu->name,pstu->age,pstu->sex);
}

int destroyall(struct student *phead)
{
    int num = 0;
    struct student *ptmp = NULL;
    for(phead;NULL!=phead;phead=ptmp)
    {
        ptmp = phead->next;
        free(phead);
        num++;
    }
    return num;
}

struct student *findbyid(struct student *phead,char *id)
{
    while(NULL != phead)
    {
        if(strcmp(phead->id,id) == 0)
        {
            break;
        }
        phead = phead->next;
    }
    return phead;
}
struct student *delstu(struct student *phead,struct student *pstu)
{
    struct student *pre=NULL;
    struct student *ptmp=NULL;
    if((NULL == phead) || (NULL == pstu))
    {
        return phead;
    }
    if(phead == pstu)
    {
        //phead = phead->next;
        return phead->next;
    }
    else
    {
        pre = phead;
        ptmp= phead->next;
        while(NULL != ptmp)
        {
            if(ptmp == pstu)
            {
                break;
               
            }
            pre = ptmp;
            ptmp = ptmp->next;
        }
        if(NULL != ptmp)
        {
            pre->next = pstu->next;
            free(pstu);
            ptmp = NULL;
            printf("free success!\n");
        }
        else
        {
            printf("can not find pstu\n");
        }
    }
    return phead;
}
void write(struct student *phead,char *file)
{
    FILE *p = fopen(file,"w");
    if(NULL == p)
    {
        return ;
    }
    while(NULL != phead)
    {
        fwrite(phead,sizeof(struct student),1,p);
        phead = phead->next;
    }
    fclose(p);
}
void readfile(struct student **pphead,char*file)
{
    int n;
    struct student *p = NULL;
    FILE *fp = fopen(file,"r");
    if(NULL == fp)
    {
        return ;
    }
    while(1)
    {
        p = malloc(sizeof(struct student));
        n = fread(p,sizeof(struct student),1,fp);
        if(0 == n)
        {
            free(p);
            break;
        }
        p->next = NULL;
        addstu(pphead,p);
    }
    printf("read\n");
    fclose(fp);
}
