#include <iostream>
#include <string.h>
#include <string>
using namespace std;

template <typename T>
T sfunc(T s1,T s2)
{
    cout<<s1 + s2<<endl;
    return s1;
}
int main(int argc,char *argv[])
{
    string s("hello");
    string s1(" world");
    sfunc(s,s1);

    return 0;
}
