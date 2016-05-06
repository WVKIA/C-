

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

int initallstudent(struct allstudent *all,unsigned int space)
{
    all->pall = (struct student *)malloc(space*sizeof(struct student));
    if(NULL == all->pall)
    {
        return -1;
    }
    all->space = space;
    all->num = 0;
    return 0;
}
int grow(struct allstudent *all)
{
    struct student *p = (struct student *)malloc(all->space*2*sizeof(struct student));
    if(NULL == p)
    {
        return -1;
    }
    memcpy(p,all->pall,all->num*sizeof(struct student));
    free(all->pall);
    all->pall = p;
    all->space *= 2;
    return 0;
}
