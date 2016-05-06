#ifndef __MYSTACK__
#define __MYSTACK__

template <typename T> 
class mystack
{
    public:
        mystack(void);
        bool push(T in);
        T pop(void);
        bool empty(void);
    private:
        T data[1024];
        unsigned int top;

};
template <typename T>
mystack<T>::mystack(void)
{
    top = 0;
}
template <typename T>
bool mystack<T>::push(T in)
{
    data[top] = in;
    top++;
    return true;
}
template <typename T>
T mystack<T>::pop(void)
{
    top--;
    return data[top];
}

template <typename T>
bool mystack<T>::empty(void)
{
    return top == 0;
}

#endif
