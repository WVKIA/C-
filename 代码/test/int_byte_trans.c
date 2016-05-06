#include <stdio.h>

int l2byte1(int a);
//int l2byte(int a);
int main(void)
{
    int a = 0x12345678;
    //int pa = l2byte(a);
    int pb = l2byte1(a);
    printf("%x \n",pb);
    return 0;
}
/*
int l2byte(int a)
{
    int *pa = (char *)&a;
    int temp;
    for(i = 0; i < 2;i++)
    
    temp = *pa;
    *pa = *(pa + 3);
    *(pa + 3) = temp;
    temp = *(pa + 1);
    *(pa + 1) = *(pa + 2);
    *(pa + 1) = temp;
    
    return a;

    char *p = (char *)&a;
    char *q = p + 3;
}
*/

int l2byte1(int a)
{
    int b = (a << 24) | (a >> 24) & 0xff;
    int c = ((a << 8 ) & 0x00ff0000) | (((a >> 8) & 0x000ff00  ) );
    a = b | c;
    return a;

}
