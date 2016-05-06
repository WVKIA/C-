#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"
void help(void)
{
    printf("HELP:\n");
    printf("*****************Add Student Please Input 'add'*****************\n");
    printf("\n");
    printf("****************Delete student please input 'del'***************\n");
    printf("\n");
    printf("*************Find Student By Id Please Input 'find'*************\n");
    printf("\n");
    printf("**********Find Student By Name Please Input 'f-name'************\n");
    printf("\n");
    printf("*********Print Student Information Please Input 'show'**********\n");
    printf("\n");
    printf("***************Quit System Please input'quit'*******************\n");
}
int addstu(struct student **pphead,struct student *pstu)
{
    struct student *pre=NULL;
    struct student *ptmp=NULL;
    if(NULL==pstu)
    {
        return 0;
    }
    if(NULL==(*pphead))
    {
        *pphead=pstu;

    }
    else if(strcmp(pstu->id,(*pphead)->id)<0)
    {
        pstu->next=*pphead;
        (*pphead)->pre=pstu;
        *pphead=pstu;
    }
    else
    {
        pre=*pphead;
        ptmp=pre->next;
        while(NULL!=ptmp)
        {
            if(strcmp(ptmp->id,pstu->id)>0)
            {
                break;
            }
            pre=ptmp;
            ptmp = ptmp->next;
        }
        pre->next=pstu;
        pstu->pre=pre;
        pstu->next=ptmp;
        if(NULL!=ptmp)
        {
            ptmp->pre=pstu;
        }
    }
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
    for(phead;NULL!=phead;phead=phead->next)
    {
        num++;
        showone(phead);
    }
    return num;
}
int rshowall(struct student *phead)
  {
  struct student *ptmp=NULL;
  struct student *pltime=NULL;
  if(NULL==phead)
  {
  return 0;
  }
  while(NULL!=phead->next)
  {
      phead=phead->next;
  }
  while(NULL!=phead)
  {
      showone(phead);
      phead=phead->pre;

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
    for(phead;NULL!=phead;phead=ptmp)
    {
        ptmp=phead->next;
        free(phead);
        num++;
    }
    return num;
}
struct student *findbyid(struct student *phead,char *id)
{
    if(NULL==phead)
    {
        return NULL;
    }
    for(phead;NULL!=phead;phead=phead->next)
    {
        if(strcmp(phead->id,id)==0)
        {
            return phead;
            break;
        }

    }
    return NULL;
}
struct student *findbyname(struct student *phead,char *name,struct student *pre)
{
    struct student  *ptmp=NULL;
    if(NULL==pre)
    {
        pre=phead;
        if(strcmp(phead->name,name)==0)
        {
            return phead;
        }
    }

    ptmp=pre->next;
    for(ptmp;NULL!=ptmp;ptmp=ptmp->next)
    {
        if(strcmp(ptmp->name,name)==0)
        {
            return ptmp;

        }
    }
    return NULL;
}


void delstu(struct student **pphead,struct student *pstu)
{
    struct student *p=NULL;
    if(*pphead==pstu)
    {
        *pphead=pstu->next;
        if(*pphead!=NULL)
        {
            (*pphead)->pre=NULL;
        }
        return;

    }
    p=pstu->pre;
    p->next=pstu->next;
    if(NULL!=pstu->next)
    {
       (pstu->next)->pre=p;
    }
    return;
}
/*struct student *reverse(struct student *phead)
  {
  struct student *p=NULL;
  struct student *ptmp=NULL;
  struct student *pre=NULL;
  if(NULL==phead)
  {
  return phead;
  }
  p=phead;
  while(NULL!=p)
  {
  pre=p->next;
  p->next=ptmp;
  ptmp=p;

  p=pre;

  }


  return phead;
  }*/
/*struct student reverse(struct student **pphead)
  {
  struct student *p=NULL;
  struct student *pre=NULL;
  struct student *ptmp=NULL;
  p=*pphead;
  while(NULL!=p)
  {
  pre=p->next;
  p->next=ptmp;
  ptmp=p;
  p=pre;
  }
 *pphead=ptmp;
 }*/
struct student *reverse(struct student *phead)
{
    struct student *nphead=NULL;
    struct student *p=NULL;
    //struct student *ptmp=NULL;
    while(NULL!=phead)
    {
        p=phead;
        phead=phead->next;

        p->next=NULL;
        p->pre=NULL;


        p->next=nphead;
        if(NULL!=nphead)
        {
            nphead->pre=p;
        }
        nphead=p;

    }
    return nphead;
}
struct student *readfromefile(struct student *phead,char *file)
{
    int num=0;
    int n=0;
    struct student *pstu=NULL;
    FILE *fp=fopen(file,"r");
    if(NULL==fp)
    {
        return NULL;
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
        addstu(&phead,pstu);
        num++;
    }
    fclose(fp);
    return phead;
}
int savefile(struct student *phead,char *file)
{
    int num=0;
    FILE *wp=fopen(file,"w");
    if(NULL==wp)
    {
        return 0;
    }
    if(NULL!=phead)
    {
        for(phead;NULL!=phead;phead)
        {
            fwrite(phead,sizeof(struct student),1,wp);
            num++;
            phead=phead->next;

        }
    }
    fclose(wp);
    return num;
}






