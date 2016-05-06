
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "student.h"
struct student *addstu(struct student *root,struct student *pstu)
{
    struct student * p = NULL;
    p = root;
    if(NULL == root)
    {
        return pstu;
    }
    while(NULL != p)
    {
        
        if(strcmp(pstu->id,p->id) < 0)
        {
           if(NULL == p->left)
           {
               p->left = pstu;
               return root;
           }
           else
           {
               p = p->left;
           }
        }
        else
        {
            if(NULL == p->right)
            {
                p->right = pstu;
                return root;
            }
            else
            {
                p = p->right;
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
    showall(root->left);
    showone(root);
    showall(root->right);
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
/*
int rshowall(struct student *phead)
{
    int num = 0;
    if(NULL == phead)
    {
        return 0;
    }
    while(NULL != phead->next)
    {
        phead = phead->next;
    }
    while(NULL != phead)
    {
        showone(phead);
        num++;
        phead = phead->pre;
    }
    return num;
}
*/
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

int destroyall(struct student *root)
{
    int num = 0;
  
    if(NULL == root)
    {
        return 0;
    }
    
    
    destroyall(root->left);
  
    destroyall(root->right);
    free(root);
    printf("destroyall!!!!!!!!!!!\n");
    
  
}

struct student *findbyid(struct student *root,char *id)
{
    struct student *note = root;
  if(NULL == root)
  {
      return NULL;
  }
  if(NULL == id)
  {
      return NULL;
  }
  while(NULL != note)
  {
      if(strcmp(note->id,id) == 0)
      {
        return note;
      }
      else if(strcmp(note->id,id) > 0)
      {
          note = note->left;
      }
      else
          {
            note = note->right;
          }
  }

}
struct student * find_min(struct student *root)
{
    struct student *p = NULL;
    struct student * ptmp = NULL;
    p = root;
    if(NULL == root)
    {
        return NULL;
    }
    while(NULL != p)
    {
        ptmp = p;
        p = p->left;
    }
    return ptmp;
}
struct student *find_max(struct student * root)
{
    struct student * p = NULL;
    struct student *ptmp = NULL;
    p = root;
    if(NULL == root)
    {
        return NULL;
    }
    while(NULL != p)
    {
        ptmp = p;
        p = p->right;
    }
    return ptmp;
}
static struct student * _delstu(struct student *root, struct student *pstu)
{
    struct student *tmp = NULL;
    struct student *note = NULL;
    if(NULL == root || NULL == pstu)
    {
        return NULL;
    }
    if(root == pstu)
    {
        root = NULL == root->left?pstu->r:pstu->left;
        return root;
    }
    child = NULL == pstu->left?pstu->right:pstu->left;
    rt = strcmp(pstu->id, root->id);
    rt < 0?(node = root->left):(node = root->right);
    while(NULL != node)
    {
        if(node == pstu)
        {
            parent->left == node?(parent->left = child):(parent ->right = child);
            break;
        }
        parent = node;
        rt = strcmp(pstu->id,node->id);
        node = rt<0 ? node->left:node->right;
    }
    return root;


}

struct student *delstu(struct student *root,struct student *pstu)
{
        

}
void revert(struct student *root)
{
    struct student *tmp = NULL;
    if(NULL == root)
    {
        return ;
    }
    
    
        tmp = root->left;
        root->left = root->right;
        root->right = tmp;
        
    
    
    

        revert(root->left);
        revert(root->right);
    
}
/*
void write(struct student *root,char *file)
{
    FILE *p = fopen(file,"w");
    if(NULL == root)
    {
        return ;
    }
    while(NULL != root)
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
        p->pre = NULL;
        addstu(pphead,p);
    }
    printf("read\n");
    fclose(fp);
}
*/
