#include <string.h>
#include <iostream>
#include <stdlib.h>
#define MAX 1024
using namespace std;
class mystack
{
    private:
        void *data[MAX];
        unsigned int top;
    public:
        mystack(void);
        ~mystack();
        void push(void *p);
        void *pop(void);
        void *peek(void);
        bool isempty(void);
        void clean(void);
        static void play_test(char *buf);
};
void mystack::play_test(char *buf)
{
    cout<<buf<<endl;
}
mystack::mystack(void)
{
    top = 0;
}
mystack::~mystack()
{

}
void  mystack::push(void *p)
{
    if(top >= MAX)
    {
        cout<<"stack is full"<<endl;
        return ;
    }
    data[top] = p;
    top++;
}
void *mystack::pop(void)
{
    if(isempty())
    {
        cout<<"stack is empty"<<endl;
        return NULL;
    }
   
    top--;
    void *x = data[top];
    return x;
}
void *mystack::peek(void)
{
    void *x = data[top-1];
    return x;
}
bool mystack::isempty(void)
{
    if(top == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int main()
{
    int i = 0;
    mystack s;
    int *a = NULL;
    for(i = 0;i < 9;i++)
    {
        a = (int *)malloc(sizeof(int));
        *a = i;
      
        s.push(a);
    }
    while(!s.isempty())
    {
        a = (int *)s.pop();
        cout<<*a<<endl;
        free(a);
        a = NULL;
    }
    char buf[] = {"hello world"};
    mystack::play_test(buf);
    return 0;

}
