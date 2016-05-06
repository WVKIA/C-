#include <stdio.h>
#include <string.h>
#include <vector>
#include <iostream>
#include <stdlib.h>
using namespace std;
bool vectorinsert(vector<int> *pv,int n)
{
    vector<int>::iterator  it;
    for(it = pv->begin(); it != pv->end(); it++)
    {
        if((*it) > n)
        {
            break;
        }
    }
    pv->insert(it,n);
    return true;
}
int main()
{
    vector<int > v;
    vector<int> ::iterator it;
    int i = 0;
    int n;
    srand(time(NULL));
    for(i = 0; i < 9; i++)
    {
        n = rand()%100;
        cout<<"rand"<<n<<endl;
        vectorinsert(&v,n);
    }
    for(i= 0; i < v.size() ; i++)
    {
        cout<<v[i]<<endl;
    }
    return 0;

}
