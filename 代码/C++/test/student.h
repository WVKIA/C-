#ifndef __TEST_H__
#define __TEST_H_
using namespace std;
struct node
{
    char name[20];
    char id[20];
};

class sdata
{
    private:
        vector<int> v;
    public:
        void insert(int );
        int push(void);
        bool empty(void);
        
};
bool sdata::empty(void)
{
    return v.size() == 0;
}

void sdata::insert(int n)
{
    v.push_back(n);
}
int sdata::push(void)
{
    int m = v[v.size()-1];
    v.pop_back();
    return m;
}
class ihash
{
    private:
        map<string ,int> hash;
    public:
        void add(char *id,int offset);
        int findid(char *id);
        void del(char *id);
        bool empty(void);
};
bool ihash::empty(void)
{
    if(hash.size() == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void ihash::add(char *id,int offset)
{
    
    hash.insert(pair<string,int> (string(id),offset));
}
int ihash::findid(char *id)
{
    map<string , int>::iterator i;
   i = hash.find(string(id));
   if(i == hash.end())
   {
       cout<<"can't find"<<endl;
       return -1;
   }
   return (*i).second;
}
void ihash::del(char *id)
{

    for(map<string,int>::iterator i = hash.begin(); i!= hash.end(); )
    {
        if((*i).first == string(id))
        {
            hash.erase(i++);
        }
        else
        {
            i++;
        }
    }
}



#endif
