#include <stdio.h>
#include <stdlib.h>
#include <set>
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
struct stuCmp
{
    bool operator ()(const student &stu1,const student &stu2)//in the set compare function must operator ()
    {
        return stu1.id.compare(stu2.id) < 0;
    }
};
int main()
{
    /*
    int i,n;
    set<int > s;
    set<int>::iterator it;
    set<int>::reverse_iterator rit;
    srand(time(NULL));
    
    for(i = 0; i < 10; i++)
    {
        n = rand()%10;
        cout<<n<<endl;
        it = s.find(n);
        if(it == s.end())
        {
            s.insert(n);
        }
        else
        {
            cout<<n<<" exited\n"<<endl;
        }

    }
    for(it = s.begin(); it !=s.end(); it++)
    {
        cout<<*it<<"  ";
    }
    cout<<endl;
    for(rit = s.rbegin(); rit != s.rend(); rit++)
    {
        cout<<*rit<<" ";
    }
    */
    
    int i,n;
    char buf[100];
    set<student,stuCmp> s;//strCmp be use to compare student by youself define
    set<student ,stuCmp>::iterator it;
    for(i = 9; i > 0;i --)
    {
        sprintf(buf,"%d",i);
        student stu(buf,"xiaomig");
        it = s.find(stu);
        if(it == s.end())   // if can't find return s.end(),otherwise return the address iterator
        {
            s.insert(stu);
        }
        else
        {
            cout<<"id "<<stu.id<<"exitd\n";
        }
    }
    for(it = s.begin(); it != s.end(); it++)
    {
        cout<<"id "<<(*it).id<<" name "<<(*it).name<<endl;
    }

}
