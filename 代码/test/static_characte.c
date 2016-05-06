#include <stdio.h>
void status_number_character(char * buf);
int main()
{
    char buf[1024];

    scanf("%s",buf);
    status_number_character(buf);
    return 0;

}
void status_number_character(char * buf)
{
    int i;
    int number[27] = {0};
    
    for(i = 0; '\0' != buf[i]; i++)
    {
        if(((buf[i] >= 'a') && (buf[i] <= 'z')) || ((buf[i] >= 'A') && (buf[i] <= 'Z') )  )
        {
            if(((buf[i] >= 'a') && (buf[i] <= 'z')) )
            {
                number[buf[i] - 'a'] += 1;
            }
            if(((buf[i] >= 'A') && (buf[i] <= 'Z') )  )
            {
                number[buf[i] - 'A'] += 1;
            }
        }
        else
        {
            number[26] += 1;
        }
    }
    for(i = 0; i < 27; i++)
    {
        if(i == 26)
        {
            printf("char other %d:\n",number[26]);
            break;
        }
        else
        {
            printf("char %c :%d\n",'a' + i,number[i]);
        }
    }
    
}
