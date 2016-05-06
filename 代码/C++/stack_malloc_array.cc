#include <string.h>
#include <iostream>
#include <stdlib.h>
using namespace std;
class mystack
{
    private:
        void **data;
        unsigned int top;
        unsigned int space;
        bool enlarge(void);
    public:
        mystack(unsigned int );
        ~mystack();
        void push(void *p);
        void *pop(void);
        void *peek(void);
        bool isempty(void);
        void clean(void);
};
mystack::mystack(unsigned int b = 1)
{
    space= b;
    top = 0;
    data =(void **) malloc(space *sizeof(void*));

}
bool mystack::enlarge(void)
{
    void **pnew = (void **)malloc(space * 2 *sizeof(void *));
    memcpy(pnew,data,space*sizeof(void*));
    space = space *2;
    free(data);
    data = pnew;
    return true;
}
mystack::~mystack()
{
    free(data);
    top = 0;
}
void  mystack::push(void *p)
{
    if(top == space)
    {
       int rt = enlarge();
       if(!rt)
       {
           return ;
       }
      
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
    return 0;

}
