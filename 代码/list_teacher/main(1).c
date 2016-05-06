#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "custom.h"
#define CUSFILE "custom.dat"
#define IDFILE "id.dat"
#define PHONEFILE "phone.dat"
#define STACKFILE "stack.dat"
enum
{
    HELP,
    ADD,
    SHOW,
    FIND,
    FPHONE,
    MODIFY,
    DEL,
    DELBP,
    SAVE,
    QUIT,
    NONE
};
char *cmdstring[]={
    "help",
    "add",
    "show",
    "find",
    "fphone",
    "modify",
    "del",
    "delbp",
    "save",
    "quit"
};
int getCmdno(char *cmd)
{
    int i;
    int n=sizeof(cmdstring)/sizeof(char *);
    for(i=0;i<n;i++)
    {
        if(strcmp(cmd,cmdstring[i])==0)
        {
            break;
        }
    }
    return i;
}

int main(int argc,char *argv[])
{
    long mesk=-1;
    int num=0;
    char id[20];
    char name[20];
    char phone[20];
    char buf[1024];
    int cmdno;
    int quit=0;
    struct custom *pcus=NULL;
    struct cus_id *pid=NULL;
    struct cus_phone *pdho=NULL;
    struct custom cus;
    struct hash phash;
    init_list_hash(&phash);
    readhash(&phash,IDFILE);
    struct phone_hash pphone;
    init_phone_hash(&pphone);
    readphonehash(&pphone,PHONEFILE);
    struct mystack mysk;
    init_mystack(&mysk);
    readmystack(&mysk,STACKFILE);
    FILE *fpcus=fopen(CUSFILE,"r+");
    if(NULL==fpcus)
    {
        fpcus=fopen(CUSFILE,"w+");
    }


    printf("****************************************************************\n");
    printf("*********************WELCOM CUSTOM SYSTEM***********************\n");
    printf("****************************************************************\n");
    printf("please input cmd:");
    while(0==quit)
    {
        fgets(buf,1024,stdin);
        buf[strlen(buf)-1] = '\0';
        cmdno=getCmdno(buf);
        switch(cmdno)
        {
            case HELP:
                printf("help\n");
                break;
            case ADD:
                printf("please input customer infor\n");
                printf("please input id\n");
                scanf("%s",id);
                printf("please input name\n");
                scanf("%s",name);
                printf("please input phone\n");
                scanf("%s",phone);
                fgets(buf,1024,stdin);
                strcpy(cus.id,id);
                strcpy(cus.name,name);
                strcpy(cus.phone,phone);
                add_customer(fpcus,&cus,&phash,&pphone,&mysk);
                break;
            case SHOW:
                show(fpcus,&phash);
                break;
            case FIND:
                printf("please input id\n");
                scanf("%s",id);
                pid=find_offset_by_id(&phash,id);
                if(NULL==pid)
                {
                    printf("no this customer\n");
                    break;
                }
                pcus=malloc(sizeof(struct custom));
                if(NULL==pcus)
                {
                    break;
                }
                long id_byte = pid->offset*sizeof(struct custom);
                fseek(fpcus,id_byte,SEEK_SET);
                fread(pcus,sizeof(struct custom),1,fpcus);
                showone(pcus);
                free(pcus);
                break;
            case FPHONE:
                printf("please input phone\n");
                scanf("%s",phone);
                pdho=NULL;
                do
                {
                    pdho=find_by_phone(&pphone,phone,pdho);
                    if(NULL!=pdho)
                    {
                        pcus=malloc(sizeof(struct custom));
                        long phone_byte=pdho->offset*sizeof(struct custom);
                        fseek(fpcus,phone_byte,SEEK_SET);
                        fread(pcus,sizeof(struct custom),1,fpcus);
                        showone(pcus);
                        free(pcus);
                        pcus=NULL;
                    }
                }while(NULL!=pdho);
                break;
            case MODIFY:
                printf("modify\n");
                break;
            case DEL:
                printf("please input id\n");
                scanf("%s",id);
                mesk=del_custombyid(&phash,id);
                if(mesk!=-1)
                {
                    mysk.push(&mysk,&mesk);
                }
                break;
            case DELBP:
                printf("please input phone\n");
                scanf("%s",phone);
                pdho=NULL;
                do
                {
                    pdho=find_by_phone(&pphone,phone,pdho);
                    if(NULL!=pdho)
                    {
                        pcus=malloc(sizeof(struct custom));
                        long phone_byte=pdho->offset*sizeof(struct custom);
                        fseek(fpcus,phone_byte,SEEK_SET);
                        fread(pcus,sizeof(struct custom),1,fpcus);
                        showone(pcus);
                        num++;
                        free(pcus);
                        pcus=NULL;
                    }
                    printf("0\n");
                    /*else{
                        break;
                    }*/
                }while(NULL!=pdho);
                printf("1\n");
                if(0==num)
                {
                    printf("no this phone");
                    break;
                }
                printf("2\n");
                printf("please input cutomer's id\n");
                scanf("%s",id);
                mesk=del_custombyid(&phash,id);
                if(mesk!=-1)
                {
                    mysk.push(&mysk,&mesk);
                }

                break;
            case SAVE:
                break;
            case QUIT:
                savefile(&phash,IDFILE);
                savephonefile(&pphone,PHONEFILE);
                savemystack(&mysk,STACKFILE);
                quit=1;
                break;
            default:
                printf("please input cmd:\n");
                break;
        }
    }
    fclose(fpcus);
    return 0;
}





