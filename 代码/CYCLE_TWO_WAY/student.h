#ifndef __STUDENT_H__
#define __STUDENT_H__

struct student
{
    struct student *pre;
    char id[20];
    char name[20];
    char age;
    char sex;
    struct student *next;
};
int addstu(struct student *pphead,struct student *pstu);
int showall(struct student *phead);
void showone(struct student *pstu);
int destroyall(struct student *phead);
void help(void);
int reverse(struct student *phead);
struct student *findbyid(struct student *phead,char *id);
void delstu(struct student *pphead,struct student *pstu);
struct student *findbyname(struct student *phead,char *name,struct student *pre);
int rshowall(struct student *phead);
int savefile(struct student *phead,char *file);
int readfromfile(struct student *phead,char *file);
#endif

