#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include <string.h>
int priority(char op)
{
    switch (op)
    {
        case ')':return 2;
        case '+':
        case '-':return 3;
        case '*':
        case '/':return 4;
        case '(':return 5;
        default :return 0;
    }
}
int main()
{

    int i;
    int *n;
    int *a;
    int *b;
    char buf[100];
    char *ch;
    int c,d;
    struct stack  *ptmp=malloc(sizeof(struct stack));

    struct stack *ptmp2 = malloc(sizeof(struct stack));
    scanf("%s",buf);
    for(i =0;i < strlen(buf);i++)
    {
        if(buf[i]-'0' =< 9 && buf[i]-'0' >= 0)
        {
            n = malloc(sizeof(int));
            n = buf[i]-'0';
           printf("%d",*n);
            push(ptmp2,n);
        }
        else 

        {
            ch = malloc(sizeof(char));
            ch = peek(ptmp);
            c = priority(*ch);
            d = priority(buf[i]);

            while(1)
            {
                if(empty(ptmp) )
                {
                    ch = malloc(sizeof(char));
                    ch = buf[i];
                    push(ptmp,ch);
                    break;
                }
                else
                {
                    if(c < d)
                    {
                     //   ch = malloc(sizeof(char));
                        ch = buf[i];
                        push(ptmp,ch);
                        break;
                    }
                    else
                    {
                        ch = pop(ptmp);
                        printf("%c",ch);
                        push(ptmp2,ch);
                    }
                }
            }
        }

    }
    destroy(ptmp);
    destroy(ptmp2);
    return 0;
}
