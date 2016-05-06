#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct namect
{
    char * fname;
    char * lname;
    int letter;
};
void getinfo(struct namect *);
void makeinfo(struct namect *);
void showinfo(const struct namect *);
void cleanup(struct namect *);

int main()
{
    struct namect person;

    getinfo(&person);
    makeinfo(&person);
    showinfo(&person);
    cleanup(&person);
    return 0;
}
void getinfo(struct namect * pst)
{
    char temp[81];
    printf("please enter your first name\n");
    scanf("%s",&temp);
    pst -> fname = (char *)malloc(strlen(temp) + 1);
    strcpy(pst -> fname,temp);
    printf("enter your lname\n");
    scanf("%s",&temp);
    pst -> lname = (char *)malloc (strlen(temp) + 1);
    strcpy(pst -> lname,temp);
}
void makeinfo(struct namect * pst)
{
    pst -> letter = strlen(pst -> fname) + strlen(pst -> lname);
}
void showinfo(const struct namect * pst)
{
    printf("%s %s ,your name contains %d letters\n",pst -> fname,pst -> lname,pst -> letter);
}
void cleanup(struct namect * pst)
{
    free(pst -> fname);
    free(pst -> lname);
}
