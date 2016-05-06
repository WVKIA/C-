#include <iostream>
#include <map>
using namespace std;

int main()
{
    multimap<char,int> mmap;
    mmap.insert(pair<char,int>('a',10));
    mmap.insert(pair<char ,int>('b',9));
    mmap.insert(pair<char,int>('e',6));
    mmap.insert(pair<char,int>('a',3));
    multimap<char,int>::iterator it;
    pair<multimap<char,int>:: iterator,multimap<char,int>::iterator> ret;
  
    {
        ret = mmap.equal_range('a');
        for(it = ret.first;it != ret.second; it++)
        {
            cout<<it->first<<"  "<<it->second<<endl;
            mmap.erase(it);
        }
    }
}
