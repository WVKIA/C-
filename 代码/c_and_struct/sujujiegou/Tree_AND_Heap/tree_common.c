#include <stdio.h>
struct node 
{
    int data;
    struct node *lchild;
    struct node *rchild;
};
void preorder(struct node *root)
{
    if(root != NULL)
    {
        visit(root->data);
        preorder(root->lchild);
        preorder(root->rchild);
    }
}
void inorder(struct node *root)
{
    if(root != NULL)
    {
        inorder(root->lchild);
        visit(root->data);
        inorder(root->rchild);
    }
}
void postorder(struct node *root)
{
    if(root != NULL)
    {
        postorder(root->lchild);
        visit(root->data);
        postorder(root->rchild);
    }
}
void preorder(struct node *root)
{
    stack *st = NULL;
    struct node *p = root;
    st = init();
    while(p!= NULL || !empty(st))
    {
        if(p)
        {
            visit(p->data);
            push(p,st);
            p = p->lchild;
        }
        else
        {
            p = pop(st);
            p = p->rchild;
        }

    }
}
void inorder(struct node *root)
{
    stack *st = NULL;
    struct node *p = root;
    st = init();
    while(p != NULL || !empty(st))
    {
        if(p)
        {
            push(p);
            p = p->lchild;
        }
        else
        {
            p = pop(st);
            visit(p->data);
            p = p->rchild;
        }
    }
}

void postorder(struct node *root)
{
    struct node *p = root;
    stack *st = NULL;
    st = init();
    while(p != NULL || !empty(st))
    {
        if(p)
        {
            push(st1,p);
            push(st2,p);
            p = p->rchild;
        }
        else
        {
            p = pop(st1);
            p = p->lchild;
        }
    }
    while(!empty(st2))
    {
        p = pop(st1);
        visit(p->data);
    }

}
count = 0;
void count_tree(struct node *t)
{
    if(t)
    {
        count_tree(t->lchild);
        visit(t->data);
        count+=1;
        count_tree(t->rchild);
    }
}



int count_tree(struct node *t)
{
    int lcount = 0;
    int rconut = 0;
    if(t == NULL)
    {
        return 0;
    }
    lcount = count_tree(t->lchild);
    rcount = count_tree(t->rchild);
    return lcount + rcount;
}
int height(struct node *t)
{
    int h1 = 0;
    int h2 = 0;
    if(t == NULL)
    {
        return 0;
    }
    else
    {
        h1 = height(t->lchild);
        h2 = height(t->rchild);
        if(h1 > h2)
        {
            return h1+1;
        }
        else
        {
            return h2+1;
        }
    }
}

struct node *copytree(struct node *t)
{
    struct node *p,*q,*s;
    if(NULL == t)
    {
        return NULL;
    }
    p = copytree(t->lchild);
    q = copytree(t->rchild);
    s = malloc(sizeof(struct node));
    s->data = t->data;
    s->lchild= p;
    s->rchild = q;
    return s;
}

int num[] = {0};
void levcount(struct node *t,int l,int num[])//l = 1;because the root is pointed by l;
{
    if(t)
    {
        visit(t->data);
        num[l]++;
        levconut(t->lchild,l+1,num);
        levcount(t->rchild,l+1,num);
    }
}
