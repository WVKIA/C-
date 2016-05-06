#include <stdio.h>
#include <stdlib.h>

struct node 
{
    int data;
    struct node *left;
    struct node *right;
};
void inti(struct node *p)
{
    p->left = NULL;
    p->right = NULL;
}
struct node *insert(struct node *p,int data)
{
    if(p == NULL)
    {
        p = malloc(sizeof(struct node ));
        if(p == NULL)
        {
            fprintf(stderr);
            return NULL;
        }
        else
        {
            p->data = data;
            p->left = p->right = NULL;
        }
    }
    else if(x < p->data)
    {
        p->left = insert(p->left,data);
    }
    else if(x > p->data)
    {
        p->right = insert(p->right,data);
    }
    return p;
}
struct node *find(int data,struct node *p)
{
    if(NULL == p)
    {
        return NULL;

    }
    if(x < p->data)
    {
        return find(x,p->left);
    }
    else if(x > p->data)
    {
        return find(x,p->right);
    }
    else
    {
        return p;
    }
}
struct node *del(struct node *p,int data)
{
    struct node *tmp = NULL;
    if(NULL ==p)
    {
        error;
    }
    else if(x <p->data)
    {
        p->left = del(p->left,data);
    }
    else if(x > p->data)
    {
        p->right = del(p->right,data);
    }
    else if(p->left && p->right)
    {
        tmp = findmin(p->right);
        p->data = tmp->data;
        p->right = del(tmp->data,p->right);
    }
    else
    {
        tmp = p;
        if(p->left == NULL)
        {
            p = p->right;
        }

    }
}
