#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "mystack.h"
using namespace std;
int main()
{
    int  n;
    mystack<int> s;
    for(int i = 0;i < 9;i++)
    {
        s.push(i);
    }
    while(!s.empty())
    {
        n = s.pop();
        cout<<n<<endl;
    }
    int *t;
    mystack<int *>h;

    return 0;
}
