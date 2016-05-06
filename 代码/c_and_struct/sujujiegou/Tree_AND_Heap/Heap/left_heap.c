#include <stdio.h>
struct treenode
{
    int element;
    struct treenode *left;
    struct treenode *right;
    int npl;
};
struct treenode *merge(struct treenode *h1,struct treenode *h2)
{
    if(NULL == h1)
    {
        return h2;
    }
    if(NULL == h2)
    {
        return h1;
    }
    if(h1->element < h2->element)
    {
        return merge1(h1,h2);
    }
    else
    {
        return merge1(h2,h1);
    }
}

static struct treenode *merge1(struct treenode *h1,struct treenode *h2)
{
    if(h1->left == NULL)
    {
        h1->left = h2;
    }
    else
    {
        h1->right = merge(h1->right,h2);
        if(h1->left->npl < h1->right->npl)
        {
            swapchildren(h1);
        }
        h1->npl = h1->right->npl+1;
    }
    return h1;
}
void swapchildren(struct treenode *h)
{
    struct treenode *ptmp = h->left;
    h->left = h->right;
    h->right = ptmp;
}
struct treenode *insert1(int x,struct treenode *h)
{
    struct treenode *singlenode = NULL;
    singlenode  = malloc(sizeof(struct treenode));
    if(NULL == singlenode)
    {
        fprintf(stderr,"can't malloc\n");
        return NULL;
    }
    else
    {
        singlenode->element = x;
        singlenode->npl = 0;
        singlenode->left = singlenode->right = NULL;
        h = merge(singlenode,h);
    }
    return h;
}
struct treenode deletemin(struct treenode *h)
{
    struct treenode *leftheap;
    struct treenode *rightheap;
    if(isempty(h))
    {
        fprintf(stderr,"h is empty\n");
        return NULL;
    }                               // is empty function

    leftheap = h->left;
    rightheap = h->right;
    free(h);
    return merge(leftheap,rightheap);

}

