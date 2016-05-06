#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "costomer.h"

int phone_hash_translate(long n)
{
    int m = n % 19;
    return m;
}
void init_phone_hash(struct phone_hash *ph_hash)
{
    int i;
    for(i = 0;i < 19; i++)
    {
        ph_hash->phone[i] = NULL;
    }
}
struct phone_hash * add_phone_node(struct phone_node *p ,struct phone_hash * pid)
{

    int tmp = phone_hash_translate(p->phone);
    struct phone_hash * pid_tmp = pid;
    struct phone_node * ptmp = NULL;
    ptmp = pid_tmp->phone[tmp];
    if(NULL ==pid)
    {

        return pid;
    }
    if(NULL == ptmp)
    {
        pid_tmp->phone[tmp] = p;
    }
    else
    {
        for(ptmp;ptmp->next != NULL;ptmp = ptmp->next)
        {
            ;
        }
        ptmp->next = p;
        //        pid_tmp->pid[tmp]  = ptmp;
        pid = pid_tmp;
        return pid;
    }


}


struct stack * find_by_phone(long m,struct phone_hash *pphone,struct stack *pstack)
   {
   int tmp = phone_hash_translate(m);
   struct phone_node * ptmp = NULL;
   struct phone_hash * p = pphone;
   ptmp = p->phone[tmp];
   if(NULL == ptmp)
   {
   printf("can't find the phone\n");
   return NULL;
   }
   for(ptmp; ptmp != NULL;ptmp = ptmp->next)
   {
   if(m == ptmp->phone)
   {
   push(pstack, ptmp->offset);
   }
   }
   return pstack;
   }

void del_phone_node_in_phone_hash(long phone,long offset,struct phone_hash * pphone)
{
    long n  =0;
    struct phone_node * ptmp = NULL;
    struct phone_node * ptmp_pre = NULL;
    struct phone_hash * p = pphone;
    int tmp = phone_hash_translate(phone);
    ptmp = p->phone[tmp];
    if(NULL == ptmp)
    {
        return ;
    }
    if(ptmp->offset == offset)
    {
        p->phone[tmp] = ptmp->next;
        pphone = p;
        return ;
    }
    else
    {
        for(ptmp;ptmp != NULL;ptmp_pre = ptmp,ptmp = ptmp->next)
        {
            if(ptmp->offset == offset)
            {
                ptmp_pre->next = ptmp->next;
                free(ptmp);
                pphone = p;
            }
        }
    }
}




   /*
struct phone_node * del_by_phone(struct phone_hash * pphone,long m, struct phone_node * ptmp)
{
    struct phone_node * p = NULL;
    int tmp = phone_hash_translate(m);
    if(NULL == pphone->phone[tmp])
    {
        return NULL;
    }
    if(NULL == ptmp)
    {
        ptmp = pphone->phone[tmp];
        if(m == ptmp->phone)
        {
            return pphone->phone[tmp];
        }
    }
    p = ptmp->next;
    for(p; NULL != p;p = p->next)
    {
        if(m == p->phone)
        {
            return p;
        }
    }
}*/
void read_phone_hash(FILE *fp_phone_hash,struct phone_hash *pphone)
{
    struct phone_node * ptmp = NULL;
    int n = 0;
    int i = 0;
    if(NULL == fp_phone_hash)
    {
        return ;
    }
    fseek(fp_phone_hash,0l,SEEK_SET);
    while(1)
    {
        ptmp = malloc(sizeof(struct phone_node));
        n = fread(ptmp, sizeof(struct phone_node),1,fp_phone_hash);
        if(n == 0)
        {
            free(ptmp);
            ptmp = NULL;
            break;
        }
        ptmp->next = NULL;
        pphone = add_phone_node(ptmp,pphone);
    }
}

void save_phone_hash(FILE *fp_phone_hash, struct phone_hash *pphone)
{
    struct phone_node *ptmp = NULL;
    int i,j;
    if(NULL == pphone)
    {
        printf("can't find hash_phone table!!\n");
        return ;
    }
    if(NULL == fp_phone_hash)
    {
        printf("can't open the file!!\n");
        return ;
    }
    for(i = 0; i < 19; i++)
    {
        for(ptmp = pphone->phone[i]; NULL != ptmp; ptmp = ptmp->next)
        {
            fwrite(ptmp, sizeof(struct phone_node), 1, fp_phone_hash);
        }
    }
}
