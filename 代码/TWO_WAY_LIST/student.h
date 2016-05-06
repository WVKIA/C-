
#ifndef  __STUDENT_H__
#define  __STUDENT_H__

struct student
{
    char id[20];
    char name[20];
    char age;
    char sex;
    struct student *pre;
    struct student *next;
};

extern int addstu(struct student **pphead,struct student *pstu);
extern int showall(struct student *phead);
extern int rshowall(struct student *phead);
extern void showone(struct student *pstu);
extern struct student *findbyid(struct student *phead,char *id);
extern int destroyall(struct student *phead);
extern void reverse(struct student **phead);
extern struct student *delstu(struct student *phead,struct student *pstu);
extern void readfile(struct student **phead,char *file);
extern void write(struct student *phead, char *file);
#endif
