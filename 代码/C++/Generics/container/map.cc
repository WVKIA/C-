#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <iostream>
using namespace std;
class student
{
    public:
        string id;
        string name;
        student (const char *i = "",const char *n = ""):id(i),name(n)
    {

    }
};
int main()
{  
    int i,n;
    char buf[100];
    map<int,student > s;
    map<int ,student>::iterator it;
    for(i = 9; i > 0;i --)
    {
        sprintf(buf,"%d",i);
        student stu(buf,"xiaomig");
        
        it = s.find(i);
        if(it == s.end())   // if can't find return s.end(),otherwise return the address iterator
        {
            s.insert(pair<int,student>(i,stu));
        }
        else
        {
            cout<<"id "<<stu.id<<"exitd\n";
        }
    }
    for(it = s.begin(); it != s.end(); it++)
    {
        cout<<"key "<<(*it).first<<"id :"<<(*it).second.id<<" name "<<(*it).second.name<<endl;
    }

}
