#ifndef __TEST_H__
#define __TEST_H__
#include <iostream>
#include <vector>
using namespace std;
template <typename T>
class mystack
{
    public:
        bool push(const T &in);
        T pop(void);
        bool empty(void);
    protected:
        vector<T> v;
};
template <typename T>
bool mystack<T>::push(const T &in)
{
    v.push_back(in);
}
template <typename T>
T mystack<T>::pop(void)
{
    T tmp = v.back();
    v.pop_back();
    return tmp;
}
template <typename T>
bool mystack<T>::empty()
{
    return v.size() == 0;
}
#endif
