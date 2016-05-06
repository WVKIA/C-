#include <string.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
class mystring
{
    private:
        char *data;
        unsigned int space;
    public:
        mystring(void);
        mystring(const char *p);
        mystring(mystring &s); // copy constration
        ~mystring(void);
        char *c_str(void);
        bool clear(void);
        const mystring  operator +(const char *s);
        mystring & operator =(const char *s);
        mystring & operator =(const mystring &s);
};
mystring::mystring(mystring &s)
{
    data = (char *)malloc(s.space);
    strcpy(data,s.data);
    space = s.space;
}
mystring::mystring(void)
{
    data = (char *)malloc(sizeof(char));
    data = '\0';
    space = 1;
}
mystring::mystring(const char *p)
{
    int n = strlen(p);
    data = (char *)malloc(sizeof(char) * (n+1));
    memcpy(data,p,n);
    *(data+n) = '\0';
    space = n+1;
}
mystring::~mystring(void)
{
    free(data);
}
char *mystring::c_str(void)
{
    return data;
}
const mystring mystring::operator+(const char *s)
{
    mystring tmp(*this);
    if(strlen(s) + strlen(tmp.data) <= tmp.space-1 )
    {
        strcat(tmp.data,s);
        return  tmp;
    }
    else
    {
        int n = strlen(s);
        char *newdata = (char *)malloc(sizeof(char) * (n + strlen(tmp.data) + 1));
        memcpy(newdata,tmp.data,space-1);
        memcpy(newdata+tmp.space-1,s,n);
        *(newdata+n+tmp.space) = '\0';
        tmp.space = n + tmp.space;
        free(tmp.data);
        tmp.data = newdata;
    }
    return  tmp;
}
mystring & mystring::operator =(const char *s)
{
    if(strlen(s) < space)
    {
        strcpy(data,s);
        return *this;
    }

    int n = strlen(s);
    char *newdata = (char *)malloc(sizeof(char )  * (n+1));
    memcpy(newdata,s,n);
    *(newdata+n) = '\0';
    free(data);
    data = newdata;
    return *this;

}
mystring& mystring::operator =(const mystring &s)
{
    if(this ==  &s)
    {
        return *this;
    }
    free(data);
    data = (char *)malloc(s.space * sizeof(char));
    strcpy(data,s.data);
    space = s.space;
    return *this;
}
int main()
{
    char *ch = NULL ;
    mystring s("hello");
    mystring s1 ;
  
   
    s1 = (s+"world");
    mystring s2 = s1;
    cout << s2.c_str()<<endl;
}
