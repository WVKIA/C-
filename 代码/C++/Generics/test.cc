#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include "test.h"
using namespace std;
int main()
{
    int i;
    char buf[100];
    string c;
    test<string >s;
    for(i = 0; i < 9; i++)
    {
        sprintf(buf,"num %d : %d",i,i);
        s.put(string(buf));
    }
    while(!s.empty())
    {
        c = s.get();
        cout<<c<<endl;
    }
    return 0;
}
