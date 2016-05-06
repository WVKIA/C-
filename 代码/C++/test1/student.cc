#include "student.h"
student::student(const char *fin = "d",const char *fpl = "s")
{
    int i = 1;
    int n;
    unsigned int m;
    struct node stu;
    fp = fopen(fin,"r+");
    if(fp == NULL)
    {
        fp = fopen(fin,"w+");
        if(fp == NULL)
        {
            return;
        }
    }
    while(1)
    {
        n = fread(&stu,sizeof(struct node),1,fp);
        if(0 == n)
        {
            break;
        }
        idhash.insert(pair<string,int>(string(stu.id),i));
        namehash.insert(pair<string,int>(string(stu.name),i));
        i++;
    }

    fr = fopen(fpl,"r+");
    if(NULL == fr)
    {
        return ;
    }
    while(1)
    {
        n = fread(&i,sizeof(unsigned int),1,fr);
        if(0 == n)
        {
            break;
        }
        vstu.push_back(m);
    }
    
}
void student::add(struct node *stu)
{
    unsigned int offset;
    if(vstu.size() == 0)
    {
        fseek(fp,0l,SEEK_END);
    fwrite(stu,sizeof(struct node),1,fp);
     offset = ftell(fp)/sizeof(struct node);
     idhash.insert(pair<string,int>(string(stu->id),offset));
     namehash.insert(pair<string,int>(string(stu->name),offset));
    }
    else
    {
        offset = vstu.push_back();
        vstu.pop_back();
        fseek(fp,sizeof(struct node) *(offset-1),SEEK_SET);
        fwrite(stu,sizeof(struct node),1,fp);
        idhash.insert(pair<string,int>(string(stu->id),offset));
        namehash.insert(pair<string,int>(string(stu->name),offset));

    }
}
void student::findid(const char *id)
{
    map<string,int>::iterator it;
    it = idhash.find(string(id));
    if(it == idhash.end())
    {
        return;
    }
    showone(it->second);
    return;
}
void student::findname(const char *name)
{
    multimap<string,int>::iterator it;
        pair<multimap<string,int>::iterator ,multimap<string,int>::iterator> rt;
        rt = namehash.equal_range(string(name));
        for(it = rt.first; it != rt.second; it++)
        {
            show(it->second);
        }
}
void student::delid(const char *id)
{
    map<string,int>::iterator it;
    it = idhash.find(string(id));
    if(it == idhash.end())
    {
        return;
    }
    vstu.insert(it->second);
    idhash.erase(it);
}
void showone(const int offset)
{
    struct node stu;
    fseek(fp,0l,SEEK_SET);
    fseek(fp,sizeof(struct node) * (offset - 1),SEEK_END);
    fread(&stu,sizeof(struct node),1,fp);
    cout<<"name:"<<stu.name<<"id :"<<stu.id<<" age:"<<stu.age<<"sex :"<<stu.sex<<endl;

}
void student::showall(void)
{
    int i;
    for(i = 0; i < vstu.size(); i++)
    {
        showone(vstu[i]);
    }
}
student::~student()
{
    if(vstu.size() == 0)
    {
        fclose(fr);
    }
    else
    {
        offset = vstu.push_back();
        vstu.pop_back();
        fwrite(&offset,sizeof(int),);
    }
    fclose(fp);
}
