#ifndef __TEST_H__
#define __TEST_H__

template <typename T>
class test
{
    private:
        T data[100];
        unsigned int num;
    public:
        test(void);
        void put(T in);
        T get(void);
        bool empty(void);
        
};
template <typename T>
test<T>::test(void)
{
    num = 0;
}
template <typename T>
void test<T>::put(T in)
{
    data[num] = in;
    num++;
}
template <typename T>
T test<T>::get(void)
{
    num--;
    return data[num];
}
template <typename T>
bool test<T>::empty(void)
{
    return num== 0;
}
#endif
