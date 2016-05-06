#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;
class exceptionf
{
    public :
        string s;
        exceptionf(const char *c)
        {
            s = c;
        }

};
class exceptionc:public exceptionf
{
    public:
        exceptionc(const char *c):exceptionf(c)
    {

    }
};

class mystring
{
    public:
        ~mystring(void);
        mystring(void);
        mystring(const char *s);
        char *c_str(void);
    private:
        char *data;
        unsigned int space;

};
mystring::mystring(void)
{
    data = (char *)malloc(1);
    if( NULL == data)
    {
        free(data);
        throw string("can not malloc\n");//behind without return 
    }
    strcpy(data,"");
    space = 1;
}   

mystring::mystring(const char *s)
{
    unsigned int len = strlen(s);
    data = (char *)malloc(len + 1);
    if(NULL != data)
    {
        free(data);
        throw new exceptionc("can not malloc len\n");//throw a pointer (exceptionc child's pointer)
    }
    strcpy(data, s);
    space = len + 1;
}
mystring::~mystring()
{
    free(data);
}
char * mystring::c_str(void)
{
    return data;
}
int main()
{
    try
    {
        mystring s;
        cout<<"empty string :"<<s.c_str()<<endl;;
        mystring s1("hello world");
        cout<<"string:"<<s1.c_str()<<endl;
    }
    catch(string e)
    {
        cout<<e;
    }
    catch(exceptionf * e)//father pointer can catch because father argment can catch son class pointer
    {

        cout<<"catch int :"<<e->s<<endl;
    }
    return 0;

}
