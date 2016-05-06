#include <stdio.h>
#include <stdlib.h>

struct node
{
    int ltag;
    int rtag;
    void *data;
    struct node *rchild;
    struct node *lchild
};
void intread(struct node *root,struct node *pre)
{
    inthread(root->lchild,pre);
    if(root->lchild == NULL)
    {
        root->ltag = 1;
        root->lchild = pre;
    }
    if(root->rchild == NULL)
    {
        root->rtag = 1;
    }
    if(pre && pre->rtag == 1)
    {
        pre->rchild = root;
    }
    pre = t;
    inthread(t->rchild,pre);
}

void insert(struct node **pt,void *n)
{
    struct node *ptmp = malloc(sizeof(struct node));
    ptmp->data = data;
    ptmp->rchild = ptmp->lchild = NULL;
    struct node *p = *pt;
    if(NULL == p)
    {
        *pt = ptmp;
        return ;
    }
    while(NULL != p)
    {
        if(p->data > ptmp->data)
        {
            if(NULL == p->lchild)
            {
                p->lchild = ptmp;
                break;
            }
            else
            {
                p = p->lchild;
            }
        }
        else
        {
            if(NULL == p->rchild)
            {
                 p->rchild = ptmp;
                 break;
            }
            else
            {
                p = p->rchild;
            }
        }
    }

}

struct node *inprenode(struct node *p)
{
    struct node *pre = NULL;
    pre = p->lchild;
    if(p->ltag == 1)
    {
        return pre;
    }
    else
    {
        while(pre->rtag == 0)
        {
            pre = pre->rchild;
        }
    }
    return pre;
}
int main()
{
    struct node *root = NULL;
    for(i = 0;i < 8;i++)
    {
        n = malloc(sizeof(int));
        *n = rand();
        insert(&root,n);
    }
    struct node *pre = NULL;
    inthread(root,pre);
}



