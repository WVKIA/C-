#ifndef __STUDENT_H__
#define __STUDENT_H__

struct student
{
    char name[20];
    char id[20];
    int age;
    char sex;


};

struct allstudent
{
    int number;
    struct student  **allstu ;
    int space;
};
extern int destroyallstudent(struct allstudent *);
extern int addstu(struct allstudent * ,struct student *);
extern void show(struct allstudent *);
extern int initallstudent(struct allstudent * allstu);
extern void show_find(struct allstudent *,int );
extern struct student* findstu(struct allstudent *,char *);
extern void delstu(struct allstudent *,char *);
extern struct student *find_name(struct allstudent *,char *name,struct student *);
extern int readfile(struct allstudent *,char *);
extern int savefile(struct allstudent *,char *);
   
    



#endif
