
#ifndef __STUDENT_H__
#define __STUDENT_H__

struct student
{
    char id[20];
    char name[20];
    char age;
    char sex;
};

struct allstudent
{
    struct student *pall;
    unsigned int space;
    unsigned int num;
};

extern int initallstudent(struct allstudent *all,unsigned int space);
extern int grow(struct allstudent *all);

#endif
