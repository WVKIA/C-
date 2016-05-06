#include <stdio.h>
struct node *del(int data,struct node *phead)
{
    struct node *tmp = NULL;
    if(phead == NULL)
    {
        fprintf(stderr,"the tree is NULL\n");
        return NULL;
    }
    else if(data > phead->data)
    {
        phead->right = del(data,phead->right);
    }
    else if(data < phead->data)
    {
        phead->left  = del(data,phead->left);
    }
    else if(NULL != phead->left && NULL != phead->right)
    {
        tmp = findmin(phead->right);
        phead->data = tmp->data;
        phead->right = del(phead->right,tmp->data);
    }
    else
    {
        tmp = phead;
        if(NULL== phead->left)
        {
            phead = phead->right;
        }
        else if(NULL == phead->right)
        {
            phead = phead->left;
        }
        free(tmp);
    }
    return phead;
}
