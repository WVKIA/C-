#include <stdio.h>
short l2byte1(short a);
short l2byte(short a);
int main(void)
{
    short s = 0x1234;
    short a = l2byte(s);
    short b = l2byte1(s);
    printf("0x%x 0x%x\n",b,a);
    return 0;
}
// later byte list,inter
                                                           //translate bit from behind to front
                                                           //zhuan  huan  char baochun yige zijie
                                                           //zhi zhen yong lai huan zijie wei 
short l2byte(short a)
{
    
    
    char *pa = (char *)&a;
    int temp;
    temp = *pa ;
    *pa = *(pa + 1);
    *(pa + 1) = temp;

    
    return a;
    

}
         // 
short l2byte1( unsigned short a)                        //wei yun suan >>  <<  yong yu zijie zhuan huan
{
    short pa = (a>>8);
    short pb = (a<<8);
    a = (pa | pb);
    return a;
}
