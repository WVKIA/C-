#include <stdio.h>


struct student
{
    char id[20];
    char name[20];
    int age;
    char sex;
    struct student * next;
};
int addstu(struct student**phead);
int show(struct student *phead);
void showone(struct student *stu);
void destroy(struct student *phead);
