#include <time.h>
#include <stdio.h>
#include <string.h>
#include "costomer.h"
#define PHONE_NODE "phone_hash.dat"
#define COSTOMER "costomer.dat"
#define HASH_NODE "hash_node.dat"
#define DEL_NODE "del_node.dat"
#include <stdlib.h>
enum
{
    ADD_TEST,
    ADD,
    SHOW,
    SHOW_ALL,
    FIND_BY_ID,
    FIND_BY_PHONE,
    DEL,
    QUIT
};
char *cmdstring[]=
{
    "add_test",
    "add",
    "show", 
    "show_all",
    "find_by_id",
    "find_by_phone",
    "del",
    "quit"
};
int getCmdno(char *cmd)
{
    int i;
    int n = sizeof(cmdstring)/sizeof(char *);
    for(i=0;i<n;i++)
    {
        if(strcmp(cmd,cmdstring[i]) == 0)
        {
            break;
        }
    }
    return i;
}
int main()
{  

    printf("*************************************************WELCOME TO COSTOMER SYSTEM*************************************************\n");
    printf("                                             You can ADD your information(Name, costomer ID, Phone)\n");
    
    printf("                                                   FIND_BY_ID to select your information\n");

    printf("                                                   DEL_BY_ID or PHONE to delete your information!\n");
    printf("*****************************************************************************************************************************\n");
    
    printf("                                              This is operation you can do!\n");
    printf("                                         \"add\"   \"find_by_id\"   \"find_by_phone\"   \"delete\"   \"show\"   \"quit\"\n");
    

    FILE *fp_del_node = fopen(DEL_NODE,"r+");
    
    FILE *fp = fopen(COSTOMER,"r+");

    FILE *fp_hash = fopen(HASH_NODE,"r+");
    
    FILE *fp_phone_hash = fopen(PHONE_NODE,"r+");

    
    struct costomer cos;
    struct phone_node * ptmp = NULL; 
    struct stack * phone_stack = malloc(sizeof(struct stack));
    struct stack *del_offset_stack = malloc(sizeof(struct stack));
   
    struct hash_node * phash = malloc(sizeof(struct hash_node)) ;
    struct phone_hash * pphone = malloc(sizeof(struct phone_hash));
    
    init_stack(del_offset_stack);
    init_stack(phone_stack);
    init_hash_node(phash);
    init_phone_hash(pphone);
    
    char buf[20];
    int cmd;
    char name[20];
    char id[20];
    int phone;
    int quit = 0;
    int num = 0;
    long i = 0;
    int n;
    long a,a_tmp,m,a_phone;
   read_hash(fp_hash,phash);
   read_del_node(fp_del_node,del_offset_stack);
   read_phone_hash(fp_phone_hash,pphone);
    
   fclose(fp_hash);
   fclose(fp_del_node);
   fclose(fp_phone_hash);

   fp_hash = fopen(HASH_NODE,"w+");
   fp_del_node = fopen(DEL_NODE,"w+");
   fp_phone_hash = fopen(PHONE_NODE,"w+");
    
    while(0 == quit)
    {
        printf("    Please enter your operation:\n");
        fgets(buf,20,stdin);
        buf[strlen(buf)-1] = '\0';
        if(strlen(buf) == 0)
        {
            continue;
        }
        cmd = getCmdno(buf);
        switch (cmd)
        {
            case ADD_TEST:
                srand((unsigned int)time(0));
                while(num<100000)
                {
                 
                    i = rand();
                    name_rand(i,name); 
                    id_rand(i,id);
                    phone = phone_rand(i);
                    strcpy(cos.id,id);
                    strcpy(cos.name,name);
                    cos.phone = phone;
                    if(1 == find_id_from_hash(id,phash))
                    {
                        continue;
                    }
                    add_costomer(&cos,fp,phash,pphone,del_offset_stack);
                    num++;
                }
                
                break;
            case ADD:
                printf(" This is ADD operation (add your information and create a ID for you)\n");
                printf("Enter your id:\n");
                scanf("%s",id);
                printf("Enter your name\n");
                scanf("%s",name);
                printf("Enter your phone\n");
                scanf("%ld",&phone);
                fgets(buf,20,stdin);
                strcpy(cos.id,id);
                strcpy(cos.name,name);
                cos.phone = phone;
                if(1 == find_id_from_hash(id,phash))
                {
                    printf(" %s is same to a ID in system !\n");
                    break;
                }
                add_costomer(&cos,fp,phash,pphone,del_offset_stack);
                break;
            case SHOW:
                printf("the costomer is\n");
                show_all_chain(fp,phash);
             
                break;
            case SHOW_ALL:
                printf("the file all costomer is :\n");
                show_all(fp);
                break;
            case FIND_BY_ID:
                printf("    Please enter the id your want to find :\n");
               scanf("%s",id); 
               n = find_offset_by_id(id,phash);
               if(n == -1)
               {
                   printf("%s can't find in system !\n",id);
                   break;
               }
                printf("%d",n);
                printf_offset_to_costomer(fp,n);
                break;
            case FIND_BY_PHONE:
                printf("    Please enter the phone yout want to find:\n");
                scanf("%ld",&phone);
                fgets(buf,20,stdin);
                                               
                find_by_phone(phone,pphone,phone_stack);
               
               if(empty(phone_stack))
               {
                   printf(" %ld not in this system ! \n",phone);
                   break;
               }
               printf("This is your want to find :\n");
                while(!empty(phone_stack)) 
                {
                    a = pop(phone_stack);
                    
                    printf_offset_to_costomer(fp,a);
                }
                break;
      /*      case CHANGE:
                printf("enter your id you want to change:\n");
                scanf("%s",id);
                int c = find_by_id(id,phash);
                if(c == -1)
                {
                    printf("can't find the id\n");
                    break;
                }
                printf_offset_to_costomer(fp,c);
                printf("enter 1 to change your name
                        enter 2 to change your phone\n");
                scanf("%d",&c);
                fgets(buf,20,buf);
                if(c == 1)
                {

                }
                else if(c == 2)
                {

                }
                else
                {
                    printf("no this choce!\n");
                    break;
                }
                printf();    */
            case DEL:
                printf("    Please enter your id you want to delete:\n");
                scanf("%s",id);
                m = del_hash_node(id,phash);
                if(-1 == m)
                {
                    printf("can't find \n");
                    break;
                }
                a_tmp = (m-1)*sizeof(struct costomer);
                fseek(fp,0l,SEEK_SET);
                fseek(fp,a_tmp,SEEK_SET);
                fread(&cos,sizeof(struct costomer),1,fp);
                a_phone = cos.phone;
                del_phone_node_in_phone_hash(a_phone,m,pphone);
                del_offset_stack->push(del_offset_stack,m);
                break;
            case QUIT:
                quit  = 1;
               break;

        }
    }
 
    save_hash(fp_hash,phash);
    save_del_node(fp_del_node,del_offset_stack);
    save_phone_hash(fp_phone_hash,pphone);

    del_offset_stack->clear(del_offset_stack);
    phone_stack->clear(phone_stack);
    
    destroy_id_hash(phash);
    destroy_phone_hash(pphone);
    fclose(fp);
    fclose(fp_phone_hash);
    fclose(fp_del_node);
    fclose(fp_hash);
    
    return 0;
}

