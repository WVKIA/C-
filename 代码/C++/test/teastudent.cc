#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;
struct student
{
    char id[20];
    char name[20];
    char sex;
    char age;
};
class studata
{
    private:
        vector<unsigned int> freepos;
        FILE *fp;
        string freeposfname;
    public:
        studata(const char *fname,const char *freename);
        bool addstu(struct student *pstu,unsigned int &index);
        bool delstu(unsigned int index);
        bool getstu(struct student *pstu,unsigned int index);
        bool showstu(unsigned int index);
        bool savepos(void);
        ~studata();
};
studata::studata(const char *fname,const char *freefname)
{
    int n = 0;
    unsigned int pos = 0;
    fp = fopen(fname,"r+");
    if(NULL == fp)
    {
        fp = fopen(fname,"w+");
        if(NULL == fp)
        {
            return;
        }
    }
    freeposfname = string(freename);
    FILE *fpos = fopen(freefname,"r");
    if(NULL == fpos)
    {
        return;
    }
    while(1)
    {
        n = fread(&pos,sizeof(sizeof(unsigned int),1,fpos));
        if(0 == n)
        {
            break;
        }
        freepos.push_back(pos);
    }
    fclose(fpos);
}
bool studata::addstu(struct student *pstu,unsigned int &index)
{
    unsigned int pos = 0;
    if(0 == freepos.size())
    {
        fseek(fp,0l,SEEK_END);
        pos = ftell(fp)/sizeof(struct student);
    }
    else
    {
        pos = freepos.back();
        freepos.pop_back();
    }
    index  = pos;
    fseek(fp,pos*sizeof(struct student),SEEK_SET);
    fwrite(pstu,sizeof(struct student),1,fp);
    return true;
}
bool studata::getstu(struct student *pstu,unsigned int index)
{
    int n=  0;
    if(find(freepos.begin(),freepos.end(),index) != freepos.end())
    {
        return false;
    }
    fseek(fp,index * sizeof(struct student),SEEK_SET);
    n = fread(pstu,sizeof(struct student),1,fp);
    if(-1 != n)
    {
        return false;

    }
    return true;
}
bool studata::showstu(unsigned int index)
{
    int n = 0;
    struct student stu;
    if(find(freepos.begin(),freepos.end(),index) != freepos.end())
    {
        return false;

    }
    if(NULL == fp)
    {
        return false;
    }
    fseek(fp,index * sizeof(struct student),SEEK_SET);
    n = fread(&stu,sizeof(struct student),1,fp);
    if(-1!= n)
    {
        return false;
    }
    cout<<"id "<<stu.id<<" name"<<stu.name<<" age"<<(int)stu.age<<" sex"<<stu.sex<<endl;
    return true;
}
bool studata::delstu(unsigned int index)
{
    freepos.push_back(index);
    return true;
}
bool studata::savepos(void)
{
    unsigned int pos;
    FILE *fpos = fopen(freeposfname.c_str(),"w+");
    if(NULL == fpos)
    {
        
    }
}
