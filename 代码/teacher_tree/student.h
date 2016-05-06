
#ifndef  __STUDENT_H__
#define  __STUDENT_H__
#include "mystack.h"
struct student
{
    char id[20];
    char name[20];
    char age;
    char sex;
    struct student *l;
    struct student *r;
};

extern struct student *addstu(struct student *root,struct student *pstu);
extern int showall(struct student *root);
extern int rshowall(struct student *root);
extern void revert(struct student *root);
extern void showone(struct student *pstu);
extern struct student *findbyid(struct student *root,char *id);
extern int findname(struct student *root,char *name,struct mystack *mysk);
extern int destroyall(struct student *root);
extern struct student *delstu(struct student *root,struct student *pstu);
extern struct student *readfromfile(struct student *proot,char *file);
extern int savetofile(struct student *root,char *file);
#endif
