#include <stdio.h>
#include <ctype.h>
int main()
{
    int space_num = 0;
    int enter_num = 0;
    int other_num = 0;
    char ch;
    while((ch = getchar()) != '#')
    {
        if(ch == ' ')
        {
            space_num ++;
        }
        else if(ch == '\n')
        {
            enter_num ++;
        }
        else
        {
            other_num ++;
        }
    }
    printf("space-num :%d enter_num :%d other_num :%d",space_num,enter_num,other_num);
    return 0;
}
