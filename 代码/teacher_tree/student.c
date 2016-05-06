
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"

struct student *addstu(struct student *root,struct student *pstu)
{
    struct student *node = root;
    if(NULL == root)
    {
        return pstu;
    }
    while(NULL != node)
    {
        if(strcmp(pstu->id,node->id)<0)
        {
            if(NULL == node->l)
            {
                node->l = pstu;
                break;
            }
            else
            {
                node = node->l;
            }
        }
        else
        {
            if(NULL == node->r)
            {
                node->r = pstu;
                break;
            }
            else
            {
                node = node->r;
            }
        }
    }
    return root;
}
int showall(struct student *root)
{
    if(NULL == root)
    {
        return 0;
    }
    showall(root->l);
    showone(root);
    showall(root->r);
    return 0;
}
struct student *findmin(struct student *root)
{
    if(NULL == root)
    {
        return root;
    }
    while(NULL != root->l)
    {
        root = root->l;
    }
    return root;
}
struct student *findmax(struct student *root)
{
    if(NULL == root)
    {
        return root;
    }
    while(NULL != root->r)
    {
        root = root->r;
    }
    return root;
}
static struct student * _delstu(struct student *root,struct student *pstu)
{
    int rt = 0;
    struct student *node = NULL;
    struct student *parent = NULL;
    struct student *child = NULL;
    if(NULL == root)
    {
        return root;
    }
    if(root == pstu)
    {
        child = NULL==root->l?root->r:root->l;
        return child;
    }
    child = NULL==pstu->l?pstu->r:pstu->l;
    rt = strcmp(pstu->id,root->id);
    //rt<0?(node=root->l):(node=root->r);
    node=rt<0?root->l:root->r;
    parent = root;
    while(NULL!=node)
    {
        if(node == pstu)
        {
            parent->l==node?(parent->l=child):(parent->r=child);
            break;
        }
        parent = node;
        rt = strcmp(pstu->id,node->id);
        node=rt<0?node->l:node->r;
    }
    return root;
}
struct student *delstu(struct student *root,struct student *pstu)
{
    struct student *p=NULL;
    if((NULL!=pstu->l) && (NULL!=pstu->r))
    {
        p = findmin(pstu->r);
        pstu->r = _delstu(pstu->r,p);


        strcpy(pstu->id,p->id);
        strcpy(pstu->name,p->name);
        pstu->age = p->age;
        pstu->sex = p->sex;


        free(p);
    }
    else
    {
        root = _delstu(root,pstu);
        free(pstu);
    }
    return root;
}
int rshowall(struct student *root)
{
}

void showone(struct student *pstu)
{    
    printf("id:%s name:%s age:%d sex:%c\n",pstu->id,pstu->name,pstu->age,pstu->sex);
}

int destroyall(struct student *root)
{
    if(NULL == root)
    {
        return 0;
    }
    destroyall(root->l);
    destroyall(root->r);
    free(root);
    return 0;
}
struct student *findbyid(struct student *root,char *id)
{
    int rt = 0;
    struct student *node = root;
    if(NULL == root)
    {
        return root;
    }
    while(NULL != node)
    {
        rt = strcmp(id,node->id);
        if(0 == rt)
        {
            break;
        }
        else if(rt < 0)
        {
            node = node->l;
        }
        else
        {
            node = node->r;
        }
    }
    return node;
}
struct student *readfromfile(struct student *root,char *file)
{
    int n = 0;
    struct student *pstu = NULL;
    FILE *fp = fopen(file,"r");
    if(NULL == fp)
    {
        return root;
    }
    while(1)
    {
        pstu = malloc(sizeof(struct student));
        if(NULL == pstu)
        {
            break;
        }
        n = fread(pstu,sizeof(struct student),1,fp);
        if(0 == n)
        {
            free(pstu);
            break;
        }
        pstu->l=pstu->r=NULL;
        root = addstu(root,pstu);
    }
    fclose(fp);
    return root;
}
void savefile(struct student *root,FILE *fp)
{
    if(NULL == root)
    {
        return;
    }
    fwrite(root,sizeof(struct student),1,fp);
    savefile(root->l,fp);
    savefile(root->r,fp);
    return;
}
int savetofile(struct student *root,char *file)
{
    FILE *fp = NULL;

    if(NULL == root)
    {
        return 0;
    }
    fp = fopen(file,"w");
    if(NULL == fp)
    {
        return 0;
    }
    savefile(root,fp);
    fclose(fp);
    return 0;
}

void revert(struct student *root)
{
    struct student *ptmp = NULL;
    if(NULL == root)
    {
        return;
    }
    ptmp = root->l;
    root->l = root->r;
    root->r = ptmp;

    revert(root->l);
    revert(root->r);
    return;
}
int findname(struct student * root,char *name,struct mystack *mysk)
{
    struct student *p = root;
    if(NULL == root)
    {
        return 0;
    }
    while((NULL != root) || (!mysk->empty(mysk)))
    {
        if(p)
        {
            showone(p);
            mysk->push(mysk,p);
            p = p->l;
        }
        else
        {
            p = mysk->pop(mysk);
            p = p->r;
        }
    }
}

