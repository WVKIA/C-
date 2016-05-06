
#ifndef  __STUDENT_H__
#define  __STUDENT_H__

#include "list.h"

struct student
{
    char id[20];
    char name[20];
    struct listhead list;
    char age;
    char sex;
};

extern int addstu(struct listhead *phead,struct student *pstu);
extern int showall(struct listhead *phead);
extern int rshowall(struct listhead *phead);
extern int revert(struct listhead *phead);
extern void showone(struct student *pstu);
extern struct student *findbyid(struct listhead *phead,char *id);
extern struct student *findnamenext(struct listhead *phead,char *name,struct listhead *pre);
extern int destroyall(struct listhead *phead);
extern int delstu(struct student *pstu);
extern int readfromfile(struct listhead *phead,char *file);
extern int savetofile(struct listhead *phead,char *file);
#endif
