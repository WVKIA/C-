#include <stdio.h>
#include "tree.h"


void init_tree(struct node * root)
{
    root->lchild = NULL;
    root->rchild =NULL;
}
struct node * insert(struct node * root,struct node *pt)
{
    struct node *p = root;

    if(NULL == root)
    {
        
        return pt;
    }
    else
    {
        /*
        if(p->data > pt->data)
        {
           p->lchild= insert(p->lchild,pt);
        }
        else
        {
           p->rchild= insert(p->rchild,pt);
        }*/
        while(NULL != p)
        {
            if(pt->data > p->data)
            {
                if(NULL == p->rchild)
                {
                    p->rchild = pt;
                    break;
                }
                else
                {
                    p=p->rchild;
                }
            }
            else
            {
                if(NULL == p->lchild)
                {
                    p->lchild = pt;
                    break;
                }
                else
                {
                    p = p->lchild;
                }
            }
        }
    }
    
    return root;
}
void perorder(struct node *root)
{
    if(NULL != root)
    {
        printf("2");
    printf("%d  ",root->data);
    perorder(root->lchild);
    perorder(root->rchild);
    }
  
}

void inorder(struct node *root)
{
    if(NULL == root)
    {
        return ;
    }
    inorder(root->lchild);
    printf("%d  ",root->data);
    inorder(root->rchild);

}

