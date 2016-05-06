#include <stdio.h>
#include <map>
#include <vector>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include "student.h"
using namespace std;
int main()
{
    int op;
    int offset;
    class ihash hash;
    class sdata fdata;
    struct node nnode;
    int i = 1;
    int *c = (int *)malloc(sizeof(int));
    int n,m,operation;
    struct node *p = NULL;
    FILE *fp = fopen("student.dat","r+");
    while(1)
    {
        n = fread(&nnode,sizeof(struct node),1,fp);
        if(n == 0)
        {
            break;
        }
        hash.add(nnode.id,i);
        i++;
    }
    FILE *fr = fopen("free.dat","r+");
    
    while(1)
    {
        n = fread(c,sizeof(int),1,fr);
        if(n == 0)
        {
            break;
        }
        fdata.insert(*c);
    }
    free(c);
    char name[100];
    char id[20];
    while(1)
    {
        cout<<"please enter the operation"<<endl;
        cout<<"1 :insert information 2: find information 3 :delete information"<<endl;
        cin>>operation;
        switch(operation)
        {
            case 1:
                cout<<"enter the name"<<endl;
                cin>>name;
                cout<<"enter the id"<<endl;
                cin>>id;

                strcpy(nnode.name,name); 
                strcpy(nnode.id,id);
                
                if(fdata.empty())
                {
                fwrite(&nnode,sizeof(struct node),1,fp);
                offset = (ftell(fp))/sizeof(struct node);
                }
                else
                {
                    m = fdata.push();
                    fseek(fp,sizeof(struct node) * (m-1),SEEK_SET);
                    fwrite(&nnode,sizeof(struct node),1,fp);
                }
                hash.add(id,offset);
               
                break;
            case 2:
                cout<<"1 find by name, 2 find by id"<<endl;
                cin>>op;
                cout<<"enter the id";
                cin>>id;
                n = hash.findid(id);
                fseek(fp,sizeof(struct node) * (n-1),SEEK_SET);;
                p = (struct node *)malloc(sizeof(struct node));
                fread(p,sizeof(struct node),1,fp);
                cout<<"id "<<p->id<<"name "<<p->name<<endl;
                free(p);
                break;
            case 3:
                cout<<"enter the id delete\n";
                cin>>id;
                n = hash.findid(id);
                hash.del(id);
                fdata.insert(n);
                break;
        }
    }
    fclose(fr);
    fr =fopen("free.data","w");
    while(!fdata.empty())
    {
        m = fdata.push();
        fwrite(&m,sizeof(int),1,fr);
    }
    fclose(fp);
    fclose(fr);
}

