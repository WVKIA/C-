#include <stdlib.h>
#include <stdio.h>
struct node 
{
    int data;
    struct node *left;
    struct node *right;

};
void init(struct node *p)
{
    p->data = 0;
    p->left = NULL;
    p->right = NULL;
}
void add(struct node **phead,int data)
{
    struct node *p = *phead;
    struct node *t = malloc(sizeof(struct node));
    t->data = data;
    t->left = t->right = NULL;
    if(NULL == t)
    {
        fprintf(stderr,"can't malloc\n");
        return ;
    }
    if(NULL == *phead)
    {
        *phead = t;
        return ;
    }
    while(NULL != p)
    {
        if(t->data > p->data)
        {
            if(p->right  == NULL)
            {
                p->right = t;
                break;
            }
            else
            {
                p = p->right;
            }
        }
        else if(t->data < p->data)
        {
            if(p->left == NULL)
            {
                p->left = t;
                break;
            }
            else
            {
                p = p->left;
            }

        }
    }
}
void showone(struct node *p)
{
    printf("the node data is %d\n",p->data);
}
void levcount(struct node *phead,int l,int num[])
{
    if(phead)
    {
        printf("This is %d class\n",l);
        showone(phead);
        num[l]++;
        levcount(phead->left,l+1,num);
        levcount(phead->right,l+1,num);
    }
}
void destroy(struct node *phead)
{
    struct node *p = phead;
    if(NULL ==  p)
    {
        return ;
    }
    destroy(p->left);
    destroy(p->right);
    free(p);
}
int height(struct node *phead)
{
    int h1,h2;
    if(NULL == phead)
    {
        return 0;
    }
    else
    {
        h1 = height(phead->left);
        h2 = height(phead->right);
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
int main()
{
    
    int h = 0;
    int l = 1;
    int i;
    struct node *phead = NULL;
    add(&phead,8);
    add(&phead,5);
    add(&phead ,3);
    add(&phead,10);
    add(&phead,6);
    add(&phead,1);
    h = height(phead);
    int num[h];
    for(i = 0;i < h;i++)
    {
        num[i]=  0;
    }
    levcount(phead,l,num);
    destroy(phead);
}
