#include <climits>
#include <iostream>
using namespace std;
int main()
{
    char ch = 'M';
    int i = ch;
    cout<<"the ascii code for"<<ch<<"is"<<i<<endl;
    ch =ch + 1;
    i = ch;
    cout<<"put char cout.put() to inout a char"<<endl;
    cout.put(ch);
    cout.put('!');
    return 0;
}
