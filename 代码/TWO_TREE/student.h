
#ifndef  __STUDENT_H__
#define  __STUDENT_H__

struct student
{
    char id[20];
    char name[20];
    char age;
    char sex;
    struct student *left;
    struct student *right;
};

extern struct student *  addstu(struct student *root,struct student *pstu);
extern int showall(struct student *root);
//extern int rshowall(struct student *root);
extern void showone(struct student *pstu);
extern struct student *findbyid(struct student *root,char *id);
extern int destroyall(struct student *root);
extern struct student *delstu(struct student *root,struct student *pstu);
//extern void reverse(struct student **phead);
//extern void readfile(struct student **root,char *file);
//extern void write(struct student *root, char *file);
#endif
