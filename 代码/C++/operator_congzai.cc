#include <iostream>
#include <stdio.h>
using namespace std;
class mynumber
{
    private:
        int c;
    public:
        void setnumber(int);
        int getnumber(void);
};
void mynumber::setnumber(int a)
{
    c = a;
}
int mynumber::getnumber(void)
{
    return c;
}
int  operator +(mynumber &a,int b)
{
    int n ;
    n = a.getnumber();
    return n*(n+b);
}
int main()
{
    mynumber h;
    h.setnumber(8);
    int c=  h+9;
    cout<<c<<endl;
}
