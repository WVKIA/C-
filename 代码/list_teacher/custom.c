#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "custom.h"

#define CUSFILE "custom.dat"

void add_customer(FILE *fpcus,struct custom *pcus,struct hash *phash,struct phone_hash *pphone,struct mystack *mysk)
{
    long *count=NULL;
    struct cus_id *pid=NULL;
    struct cus_phone *pdho=NULL;
    long index=0;
    if(0!=mysk->empt(mysk))
    {
        printf("1\n");
        fseek(fpcus,0,SEEK_END);
    }
    else
    {
        printf("2\n");
        count=mysk->pop(mysk);
        fseek(fpcus,(*count-1)*sizeof(struct custom),SEEK_SET);
    }
    index=ftell(fpcus)/sizeof(struct custom);
    fwrite(pcus,sizeof(struct custom),1,fpcus);


    pid=malloc(sizeof(struct cus_id));
    strcpy(pid->id,pcus->id);
    pid->offset=index;
    pid->next=NULL;
    phash->add_id(phash,pid);


    pdho=malloc(sizeof(struct cus_phone));
    strcpy(pdho->phone,pcus->phone);
    pdho->offset=index;
    pdho->next=NULL;
    pphone->add_phone(pphone,pdho);



    return;
}
void showone(struct custom *pcus)
{
    printf("id:%s  name:%s  phone:%s  \n",pcus->id,pcus->name,pcus->phone);
    return;
}
struct cus_id *find_offset_by_id(struct hash * p,char *id)
{
    int tmp =0;
    struct custom *pcus;
    tmp=p->id_hash_translate(id);
    for(p->ptmp[tmp] ; p->ptmp[tmp] != NULL;p->ptmp[tmp] = p->ptmp[tmp]->next)
    {
        if(strcmp(p->ptmp[tmp]->id,id) == 0)
        {
            return p->ptmp[tmp];
            break;
        }   
    }   
    return NULL;
}  
//**********************************************************************************************
struct cus_phone *find_by_phone(struct phone_hash *pphone,char *phone,struct cus_phone *pdho)
{
    struct cus_phone *ptmp=NULL;
    int tmp;
    tmp=pphone->phone_translate(phone);
    if(NULL==pphone->phha[tmp])
    {
        return NULL;
    }
    if(NULL==pdho)
    {
        pdho=pphone->phha[tmp];
        printf("6\n");
        if(strcmp(pphone->phha[tmp]->phone,phone)==0)
        {
            return pphone->phha[tmp];
        }
    }
    printf("5\n");
    ptmp=pdho->next;
    for(ptmp;NULL!=ptmp;ptmp=ptmp->next)
    {
        if(strcmp(ptmp->phone,phone)==0)
        {
            return ptmp;
        }
    }
}

//***********************************************************************************************
long del_custombyid(struct hash *phash,char *id)
{

    long n=0;
    int tmp;
    tmp=phash->id_hash_translate(id);
    struct cus_id *pid=phash->ptmp[tmp];
    if(NULL==pid)
    {
        printf("no\n");
        return -1;
    }
    for(pid;pid!=NULL;pid=pid->next)
    {
        if(strcmp(pid->id,id)==0)
        {
            break;
        }
    }
    if(NULL==pid)
    {
        printf("no this custom\n");
        return -1;
    }
    if(phash->ptmp[tmp]==pid)
    {
        phash->ptmp[tmp]=pid->next;
        n=pid->offset;
        free(pid);
        return n;
    }
    for(phash->ptmp[tmp];phash->ptmp[tmp]!=NULL;phash->ptmp[tmp]=phash->ptmp[tmp]->next)
    {
        if(phash->ptmp[tmp]->next=pid)
        {
            phash->ptmp[tmp]->next=pid->next;
            n=pid->offset;
            free(pid);
            return n;

            break;
        }
    }
}

//****************************************************************************************
void showone_list(FILE *fpcus,struct cus_id *pid)
{
    int n=0;
    struct custom pcus;
    for(pid;NULL!=pid;pid=pid->next)
    {
        fseek(fpcus,(pid->offset)*sizeof(struct custom) ,SEEK_SET);
        n=fread(&pcus,sizeof(struct custom),1,fpcus);

        showone(&pcus);
    }
    return;

}
void show(FILE *fpcus,struct hash *phash)
{
    int i=0;
    for(i=0;i<DEND;i++)
    {
        showone_list(fpcus,phash->ptmp[i]);
    }
    return;
}
//*****************************************************************************************
struct hash *readhash(struct hash *phash,char *file)
{
    int n=0;
    struct cus_id *pcus=NULL;
    FILE *fp=fopen(file,"r");
    if(NULL==fp)
    {
        return NULL;
    }
    while(1)
    {
        pcus=malloc(sizeof(struct cus_id));
        n=fread(pcus,sizeof(struct cus_id),1,fp);
        if(0==n)
        {
            free(pcus);
            pcus=NULL;
            break;
        }
        pcus->next=NULL;
        phash->add_id(phash,pcus);
    }

    fclose(fp);
    return phash;
}
int savefile(struct hash *phash,char *file)
{
    int i=0;
    FILE *fp=fopen(file,"w");
    if(NULL==fp)
    {
        return 0;
    }
    for(i=0;i<DEND;i++)
    {
        for(phash->ptmp[i];NULL!=phash->ptmp[i];phash->ptmp[i]=phash->ptmp[i]->next)
        {
            fwrite(phash->ptmp[i],sizeof(struct cus_id),1,fp);
        }
    }
    fclose(fp);
    return 0;
}
//*********************************************************************************************
struct phone_hash *readphonehash(struct phone_hash *pphone,char *file)
{
    int n=0;
    struct cus_phone *pdho=NULL;
    FILE *fph=fopen(file,"r");
    if(NULL==fph)
    {
        return NULL;
    }
    while(1)
    {
        pdho=malloc(sizeof(struct cus_phone));
        n=fread(pdho,sizeof(struct cus_phone),1,fph);
        if(0==n)
        {
            free(pdho);
            pdho=NULL;
            break;
        }
        pdho->next=NULL;
        pphone->add_phone(pphone,pdho);
    }

    fclose(fph);
    return pphone;
}
int savephonefile(struct phone_hash *pphone,char *file)
{
    int i=0;
    FILE *fph=fopen(file,"w");
    if(NULL==fph)
    {
        return 0;
    }
    for(i=0;i<PHON;i++)
    {
        for(pphone->phha[i];NULL!=pphone->phha[i];pphone->phha[i]=pphone->phha[i]->next)
        {
            fwrite(pphone->phha[i],sizeof(struct cus_phone),1,fph);
        }
    }
    fclose(fph);
    return 0;
}
//**************************************************************************************************
struct mystack *readmystack(struct mystack *mysk,char *file)
{
    int n=0;
    struct node *psk=NULL;
    FILE *fps=fopen(file,"r");
    if(NULL==fps)
    {
        return NULL;
    }
    while(1)
    {
        psk=malloc(sizeof(struct node));
        n=fread(psk,sizeof(struct node),1,fps);
        if(0==n)
        {
          free(psk);
          psk=NULL;
          break;
        }
        psk->next=NULL;
        mysk->push(mysk,psk);
    }
    fclose(fps);
    return mysk;
}
int savemystack(struct mystack *mysk,char *file)
{
    struct node *psk=NULL;
    FILE *fps=fopen(file,"w");
    if(NULL==fps)
    {
        return 0;
    }
    while(!mysk->empt(mysk))
    {
        psk=mysk->pop(mysk);
        fwrite(psk,sizeof(struct node),1,fps);
    }
    fclose(fps);
    return 0;
}
//************************************************************************












