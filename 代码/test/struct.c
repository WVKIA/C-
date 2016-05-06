#include <stdio.h>
struct test 
{
    char ch;
    short b;
    int a;
    
};
struct test1 

{ 
    int a;
    long b;
};
struct ab
{
    int a;
    long b;
    char c;
};

int main()
{
    struct test test;
    struct test * p = &test;
    test.a = 5;
    test.ch = 'A';

    printf("a :%d ch :%c\n",test.a,test.ch);
    p -> a = 43;
    p -> ch = 'a';
    printf("a is %d, ch is %c\n",p -> a,p -> ch);
    struct test1 test1;
    printf("%d",sizeof(test));


    
    
    return 0;

}
