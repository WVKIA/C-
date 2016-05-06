#ifndef __STUDENT_H__
#define __STUDENT_H__
#include "list.h"
struct student
{
    struct listhead list;
    
    char id[20];
    char name[20];
    char age;
    char sex;
    
};
int addstu(struct listhead *pphead,struct student *pstu);
int showall(struct listhead *phead);
void showone(struct student *pstu);
int destroyall(struct listhead *phead);
void help(void);
int reverse(struct listhead *phead);
struct student *findbyid(struct listhead *phead,char *id);
void delstu (struct listhead *pstu);
struct student *findbyname(struct listhead *phead,char *name,struct listhead *pre);
//int rshowall(struct listhead *phead);
int savefile(struct listhead *phead,char *file);
int readfromfile(struct listhead *phead,char *file);
#endif

