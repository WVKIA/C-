#include <stdio.h>
#include <math.h>
//char * a2A(char *s);
char a2d(char *s);
int main(void)
{
    //char *s = "dASSSf";  chang liang zi fu chuan bu neng xiu gai
    char s[39] = {"123"};
    int temp = a2d(s);
    printf("%d",temp);   //chuan zhi wei zhi zhen dayin shi wei zhizhen
    return 0;
}
/*
char * a2A(char *s)
{
    int i;
    int temp = ('A' - 'a');
    for( i = 0; '\0' != s[i]; i++)     //for(i = 0; '\0' != s[i]; i++)
    {
        if((s[i] >='a') && (s[i] <='z'))
        {
            s[i] += temp;
        }
    }
    return s;
}
*/
char a2d(char *s)
{
    int i,j,m;
    int temp = 0;
    for(i = 0; '\0' != s[i]; i ++)
    {
        m = s[i] - '0';
        temp = temp * 10  + m  ;     //zi fu '9' - '0' = int 9;


    }
    return temp;
} 
