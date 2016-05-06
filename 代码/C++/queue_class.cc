#include <iostream>
#include <stdlib.h>
using namespace std;
struct node 
{
    void *data;
    struct node *next;
};
class que
{
    private:
        struct node *front;
        struct node *rear;
    public:
        que();
        ~que();
        void put(struct node *);
        struct node *get(void);
        bool empty(void);
};
que::que(void)
{
    front = rear = NULL;
}
que::~que()
{
    struct node *p = NULL;
    while(!empty())
    {
        p = front;
        front = front->next;
        free((p->data));
        p->next = NULL;
        free(p);
    }
}
void que::put(struct node *p)
{
    if(front == NULL  && rear == NULL)
    {
        front = p;
        rear = p;
        return ;
    }
 
    rear->next = p;
    rear = p;
}
struct node  * que::get(void)
{
    if(empty())
    {
        cout<<"empty queue\n"<<endl;
        return NULL;
    }
    struct node *x = front;
    if(front == rear)
    {
        rear = NULL;
    }
    front = front->next;
    
    return x;
}
bool que::empty(void)
{
    return front== NULL;
}
int main()
{
    que q;
    struct node *p  =NULL;
    int i = 0;
    int *a = NULL;
    for(i = 0;i < 9;i++)
    {
        p =(struct node *) malloc(sizeof(struct node));
        a =(int *) malloc(sizeof(int));
        *a = i;
        p->data = a;
        p->next = NULL;
        q.put(p);
    }
    while(!q.empty())
    {
        p = q.get();

        cout<<*(int *)(p->data)<<endl;

        free((p->data));
        p->next = NULL;
        free(p);
    }
    return 0;
}
