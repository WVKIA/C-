#include <stdio.h>
#include <stdlib.h>
#include "costomer.h"
#include <string.h>

int hash_translate(char *id)
    
{
    int i;
    int tmp = 0;
    int ch = 0;
    if('\0' != id)
    {
        for(i = 0; i < strlen(id);i++)
        {
            ch = id[i] - '0';
            tmp = ch + tmp;
        }
    }
    return (tmp%19);
}   

//  get translate number
void init_hash_node(struct hash_node *p)
{
    int i;
    for(i = 0;i < 19;i++)
    {
        p->pid[i] = NULL;
    }
}
struct hash_node*  add_hash_node(struct id_node * p ,struct hash_node *pid)
{
    int tmp = hash_translate(p->id);
    struct hash_node * pid_tmp = pid;
    struct id_node * ptmp = NULL;
    ptmp = pid_tmp->pid[tmp];
    if(NULL ==pid)
    {
        
        return pid;
    }
    if(NULL == ptmp)
    {
        pid_tmp->pid[tmp] = p;
    }
    else
    {
        for(ptmp;ptmp->next != NULL;ptmp = ptmp->next)
        {
           ; 
        }
        ptmp->next = p;
        pid_tmp->pid[tmp]  = ptmp;
        pid = pid_tmp;
        return pid;
    
   
    }
   

}

void showone(struct costomer *p)
{
    printf("the id:%s  the name:%s  the phone:%d  \n",p->id,p->name,p->phone);
}

int add_costomer( struct costomer * pcos,FILE *fp,struct hash_node * pid,struct del_stack *phead)
{
    long index = 0;
    long count = 0;
    if(empty(phead))
    {
        fseek(fp,0l,SEEK_END);
    }
    else
    {
        count = phead->pop(phead);
        fseek(fp,(count-1) * sizeof(struct costomer),SEEK_SET);
    }
  
    fwrite(pcos,sizeof(struct costomer), 1, fp);           
    index = ftell(fp)/ sizeof(struct costomer);
  
    printf("%s %s %ld\n",pcos->id,pcos->name,pcos->phone);
    struct id_node *pnode = malloc(sizeof(struct id_node));
    strcpy(pnode->id,pcos->id);
    pnode->offset = index;
    pnode->next = NULL;
 
   pid= add_hash_node(pnode,pid);
    
}

int find_offset_by_id(char *id,struct hash_node *pid)
{
    struct id_node *ptmp = NULL;
    struct hash_node *pid_tmp = pid;
    int tmp = hash_translate(id);
    ptmp = pid_tmp->pid[tmp];
    if(NULL ==ptmp)
    {
        printf("can't find the id\n");
        return -1;
    }
    for(ptmp ;ptmp != NULL;ptmp = ptmp->next)
    {
        if(strcmp(id,ptmp->id) == 0)
        {

            return ptmp->offset;

        }
    }
    return -1;
}

//************************print_list_hash*********************************
void printf_list(FILE *fp_hash, struct hash_node *phash)
{
    int i;
    struct id_node * ptmp = NULL;
    for(i = 0;i < 19;i++)
    {
        for(ptmp = phash->pid[i];ptmp != NULL; ptmp = ptmp->next)
        {
            printf("id %s offset %ld\n",ptmp->id,ptmp->offset);
        }
    }
}
void printf_offset_to_costomer(FILE *fp,int offset)
{
    struct costomer pcos;
    long tmp = (offset-1) * sizeof(struct costomer);
    fseek(fp,0l,SEEK_SET);
    fseek(fp,tmp,SEEK_SET);
    fread(&pcos,sizeof(struct costomer),1,fp);
    showone(&pcos);
}
//********************************************************************************
//******************************hash_read_save************************************
void read_hash(FILE * fp_hash,struct hash_node * pid)
{
    struct id_node * ptmp = NULL;
    int n = 0;
    int i = 0;
    if(NULL == fp_hash)
    {
        return ;
    }
    fseek(fp_hash,0l,SEEK_SET);
    while(1)
    {
        ptmp  = malloc(sizeof(struct id_node));
        n = fread(ptmp,sizeof(struct id_node),1,fp_hash);
        if(n == 0)
        {
            free(ptmp);
            ptmp = NULL;
            break;
        }
        ptmp->next = NULL;
        pid = add_hash_node(ptmp,pid);
    }
    
    
   
}
void save_hash(FILE * fp_hash,struct hash_node * pid)
{
   
    struct id_node *p = NULL;
    int i,j;
    if(NULL == pid)
    {
        printf("can't find hash table\n");
        return ;
    }
    if(NULL == fp_hash)
    {
        printf("the file can't open\n");
    }
    for(i = 0;i < 19;i++)
    {   
        for(p = pid->pid[i];p != NULL;p = p->next)
        {   
            fwrite(p,sizeof(struct id_node ),1,fp_hash);
            
        }
    }
}
//******************************************************************************************
//******************************************del********************************************

long  del_hash_node(char *id,struct hash_node * pid)
{
    long n = 0;
    struct id_node * ptmp = NULL;
    struct hash_node * pid_tmp = pid;
    int tmp = hash_translate(id);
    struct id_node * ptmp_pre = NULL;
    ptmp = pid_tmp->pid[tmp];
    if(strcmp(id,ptmp->id) == 0)
    {
        pid_tmp->pid[tmp] = ptmp->next;
        n = ptmp->offset;
        pid = pid_tmp;
        return n;
    }
    else
    {
    for(ptmp;ptmp != NULL;ptmp_pre = ptmp,ptmp = ptmp->next)
    {
        
        if(strcmp(ptmp->id,id) == 0)
        {
            ptmp_pre->next = ptmp->next;
            n = ptmp->offset;
            free(ptmp);
            pid = pid_tmp;
            return n;
        }
    }
   
    }
}


int push(struct del_stack *phead ,long offset)
{
    struct del_node * p = malloc(sizeof(struct del_node));
    if(NULL== p)
    {
        printf("no memroy\n");
        return -1;
    }
    p->offset = offset;
    p->next = phead->del_head;
    phead->del_head = p;
    return 0;
}

long pop(struct del_stack *phead)
{
    long tmp = 0;
    struct del_node * ptmp = NULL;
    if(empty(phead))
    {
        return -1;
    }
    ptmp = phead->del_head;
    phead->del_head = phead->del_head->next;
    tmp  =ptmp->offset;
    return tmp;
}

int empty(struct del_stack *phead)
{
    return NULL == phead->del_head;
}
void clear(struct del_stack *phead)
{
    while(!empty(phead))
    {
        pop(phead);
    }
}

int init_del_stack(struct del_stack *phead)
{
    phead->del_head = NULL;
    phead->push = push;
    phead->pop = pop;
    phead->empty = empty;
    phead->clear = clear;
}


void save_del_node(FILE *fp_del_node,struct del_stack * phead)
{
    long tmp = 0;
    if(NULL == fp_del_node)
    {
        printf("the file can't open!!!\n");
        return ;
    }
    while( !empty(phead))
    {
        tmp = pop(phead);
        fwrite(&tmp,sizeof(long),1,fp_del_node);
    }
}

void read_del_node(FILE *fp_del_node,struct del_stack *phead)
{
    long tmp = 0;
    int n = 0;
    if(NULL == fp_del_node)
    {
        return ;
    }
    fseek(fp_del_node,0l,SEEK_SET);
    while(1)
    {
        n = fread(&tmp,sizeof(long),1,fp_del_node);
        if(n == 0)
        {
            break;
        }
        push(phead,tmp);
    }

}
             

 //  ***********************************SHOW******************************
void show_all(FILE *fp)
{
    int n = 0;
  
    struct costomer  ptmp;
    if(NULL == fp)
    {
        printf("can't open the file\n");
    }
    fseek(fp,0L,SEEK_SET);
    while(1)
    {
       
        n = fread(&ptmp,sizeof(struct costomer),1,fp);
        if(0 == n)
        {
           
            
            break;
        }
        showone(&ptmp);
    }
    
}

void show_one_chain(FILE *fp,struct hash_node *phash, int n)
{
    int offset = 0 ;
    struct id_node *p = NULL;
    struct id_node * ptmp = phash->pid[n];
    if(NULL != ptmp)
    {
        for(p = ptmp; p != NULL; p = p->next)
        
        {
            offset = p->offset;
            printf_offset_to_costomer(fp,offset);
        }
    }
}
    
void show_all_chain(FILE *fp, struct hash_node *phash)
{
    int i = 0;
    for(i = 0;i < 19; i++)
    {
        show_one_chain(fp,phash,i);
    }

}

//******************************************phone*****************************************


