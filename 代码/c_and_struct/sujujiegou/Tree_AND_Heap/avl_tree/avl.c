#include <stdio.h>
struct node 
{
    int data;
    struct node *left;
    struct node *right;
    int height;
};
static int height(struct node *p)
{
    if(NULL == p)
    {
        return -1;
    }
    else
    {
        return p->height;
    }
}
struct node *insert(int data,struct node *t)
{
    if(NULL == t)
    {
        t = malloc(sizeof(struct node));
        if(NULL ==t)
        {
            error;
        }
        else
        {
            t->data = data;
            t->left = t->right = NULL;
            t->height = 0;
        }
    }
    else if(data < t->data)
    {
        t->left  =insert(data,t->left);
        if(height(t->left) - height(t->right) == 2)
        {
            if(data < t->left->data)
            {
                t=ll_rotate(t);
            }
            else
            {
                t = lr_rotate(t);
            }
        }
      
    }
    else if(data > t->data)
    {
        t->right = insert(data,t->right);
        if(height(t->right ) - height(t->left) == 2)
        {
            if(data > t->right->data)
            {
                t = rr_rotate(t);
            }
            else
            {
                t = rl_rotate(t);
            }
        }
    }
    t->height = max(height(t->left),height(t->right))+1;
    return t;
}

