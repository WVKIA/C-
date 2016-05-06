#include <map>
#include <iostream>
#include <vector>
#include "student.h"
class student:public sdata,ihash
{
    private:
        sdata vec;
        ihash hash;
    public:
        student(const char *fhash,const char *fempty,);
        ~student();
        void add(char *id,char *name);
        void findid(char *id);
        void findname(char *name);
        void del(char *id);
        void delname(char *name);
        void showoffset(int offset);
        void showall(void);
        
};
student::student(const char *fhash = "idhash,dat",const char* fempty = "sdata.dat")
{
    int n,m;
    struct node stu;
    FILE *fp = fopen(fhash,"r+");
    if(NULL == fp)
    {
        fp = fopen(fhash,"w+");

    }
    while(1)
    {
        n = read(&stu,sizeof(struct node),1,fp);
        if(0 == n)
        {
            break;
        }
        hash.add(pair<string,int>(stu.id));
    }
    FILE *fr = fopen(fempty,"r+");
    if(NULL == fr)
    {
      return ;
    }
    while(1)
    {
        n = fread(&m,sizeof(int),1,fr);
        
            if(n == 0)
            {
                break;
            }
            
        vec.insert(m);
    }
   

}
void student::add(char *id, char *name)
{
    int n,offset;
    struct node stu;
    strcpy(stu.id,id);
    strpcy(stu.name,name);
    if(0 == vec.size())
    {
        fseek(fp,0l,SEEK_END);
 
    offset = ftell(fp)/sizeof(struct node);
    }
    else
    {
        offset = vec.back();
        vec.pop_back();
    }

    fwrite(&stu,offset * sizeof(struct node),1,fp);
    hash.add(id,offset);

}

student::~student()
{

}
