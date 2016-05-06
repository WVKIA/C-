#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "test.h"
#include <vector>
using namespace std;
int main()
{
    /*
    int i,n;
    mystack<int> v;
    srand(time(NULL));
    for(i = 0;i <10; i++)
    {
        n = rand()%100;
        v.push(n);
        cout<<n<<endl;
    }
    
    while(!v.empty())
    {
        n = v.pop();
        cout<<n<<endl;
    }*/
    vector<int> v;
    int i = 0;
    int n;
    srand(time(NULL));
    for(i = 0; i < 10; i++)
    {
        n = rand()%100;
        v.push_back(n);
        cout<<n<<endl;
    }
    vector <int> v1(v.begin()+1, v.begin()+4);
    while(!v1.empty())
    {
        n = v1.back();
        v1.pop_back();
        cout<<n<<endl;
    }
}
