#ifndef __TREE_H__
#define __TREE_H__

struct node
{
    int data;
    struct node * lchild;
    struct node * rchild;

};
struct node * insert(struct node *,struct node *);
void perorder(struct node *);
void inorder (struct node *);
#endif
