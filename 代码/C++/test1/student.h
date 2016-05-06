#ifndef __STUDENT_H__
#define __STUDENT_H_
#include <map>
#include <vector>
#include <iostream>
using namespace std;
struct node
{
    char name[20];
    char id[20];
    char age;
    char sex;
};
class student
{
    private:
        FILE *fp;
        FILE *fr;
        vector< int> vstu;
        map<string,int>  idhash;
        multimap<string,int> namehash;
    public:
        student(const char *,const char *);
        ~student();
        void add(struct node *);
        void findid(const char *);
        void findname(const char *);
        void delid(const char *);
        void delname(const char *);
        void showone(int offset);
        void showall(void);
};
#endif
