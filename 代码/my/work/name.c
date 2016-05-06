#include <stdio.h>
#include <string.h>

struct namect
{
    char fname[20];
    char lname[20];
    int letters;
};

struct namect getinfo(void);
struct namect  makeinfo(struct namect );
void showinfo( struct namect );

int main()
{
    struct namect person;
    person = getinfo();
    person = makeinfo(person);
    showinfo(person);
    return 0;
}
struct namect getinfo(void)
{
    struct namect temp;
    printf("please enter your first name\n");
    gets(temp.fname);
    printf("please enter yout last name\n");
    gets(temp. lname);

}

struct namect makeinfo(struct namect info)
{
    info.letters = strlen(info.fname) + strlen( info.lname);
    return info;
}
void showinfo(const struct namect info)

{
    printf("%s %s .you name contains %d letters\n",info.fname,info.lname,info.letters);
}
