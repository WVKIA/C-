#include <iostream>
#include <string.h>
using namespace std;
class test
{
    private:
       char id[20];
    public:
        test(const char *idn)
        {
            strcpy(id,idn);
        }
        char *getid(void)
        {
            return id;
        }
};

class father
{
    private:
        char name[20];
        test id;
    public:
        father(const char *n,const char *i);
        void setName(const char *);
        char *getName(void);
        char *getId(void);
        virtual void show(void);   // xu han shu 
};
void father::show(void)
{
    cout<<"father------>"<<name<<"id"<<id.getid()<<endl;
}
char *father::getId(void)
{
    return id.getid();
}
father::father(const char *n,const char *i):id(i)
{
    strcpy(name,n);
}
void father::setName(const char *buf)
{
    strcpy(name,(char *)buf);
}
char *father::getName(void)
{
    return name;
}
class child:public father
{
    public:
        void show(void);
        child(const char *n,const char *i);
};
child::child(const char *n,const char *i):father(n,i)
{

}

void child::show(void)
{
    cout<< "child----->>"<<"name :"<<getName()<<"id :"<<getId()<<endl;
}



//---func father zhi zhen 
void func(father *p)
{
    p->show();
}
//ru guo  p zhi xiang de dui xiang wei child   ze zhixing father show() ,zhi xiang child zhi xing child show


int main()
{
    child s("xiaoming","1001");
  
    s.show();
    s.father::show();

    father p("xiaohong","1001");
    func(&p);

    func(&s);
    return 0;
}


