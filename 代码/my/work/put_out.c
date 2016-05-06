#include <stdio.h>
#define DEF "i am a define string"
int main()
{
    char ch[30] = {"an arraywa tome"};
    const char * p3 = "a pointer was innitinalized me";
    puts("t ");
    puts(ch);
    puts(p3);
    puts(&ch[4]);
}
