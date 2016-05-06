#ifndef __STUDNET_H__
#define __STUDENT_H__
#include "list.h"
struct student
{
    char name[20];
    char id[20];
    int age;
    char sex;
    struct list phead;
};
void add(struct list *phead,struct student *stu);
void show(struct list *stu);
void destroy(struct list *phead);
struct student * find(struct list *phead,char *pstu);
void del(struct list *);
#endif
