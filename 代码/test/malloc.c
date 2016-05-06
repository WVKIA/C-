#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void getstr(char **s)
{
    *s = malloc(100);
    strcpy(*s,"hello,world!");
    return ;

}

int main(void)
{
    int n ;
    char * str = NULL;
    getstr(&str);
    printf("%s\n",str);
    free (str);
    while(1)
    {
        scanf("%d",&n);
        printf("%d\n",n);
        str = malloc(n + 1);
        if (NULL == str)
        {
            break;
        }
        scanf("%s",str);
        printf("str:%s\n",str);
        if(strcmp(str, "quit") == 0)
        {
            free(str);
            str = NULL;
            break;
        }
        free (str);
        str = NULL;
    }
    return 0;
}
/*char * getstr(void)
{
    char * s = NULL;
    s = malloc(100);
    strcpy(s,"hello,wod!");
    return s;

}
*/
