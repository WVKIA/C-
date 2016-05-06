#include <stdio.h>
#include "tree.h"
#include <stdlib.h>
int main()
{
    int i = 0;
    struct node * root = NULL;
    
    for(i = 0;i < 4;i++)
    {
        struct node *p = malloc(sizeof(struct node));
        init_tree(p);
        p->data = rand();
        root = insert(root,p);
    }
    perorder(root);
    return 0;

}

