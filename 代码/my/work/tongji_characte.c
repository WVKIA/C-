#include <stdio.h>

float multiply(float a,float b);
float divide(float a,float b);
float subtract(float a,float b);
float add(float a, float b);
char get_right(void);
char get_operation(void);
float get_second_number(void);
float get_first_number(void);
int main()
{
    float a = get_first_number();
    float b = get_second_number();
    char ch ;
    float add_n = add(a,b);
    
    float multiply_n = multiply(a,b);
    float divide_n = divide(a,b);
    float subtract_n = subtract(a,b);
    while(1 )
    {
        ch = get_operation();
        switch (ch)
        {
            case 'a':printf("%f + %f = %f",a,b,add_n);
                     break;
            case 'm':printf("%f * %f = %f",a,b,multiply_n);
                     break;
            case 's':printf("%f - %f = %f",a,b,subtract_n);
                     break;
            case 'd':printf("%f / %f = %f",a,b,divide_n);
                     break;
            case 'q':printf("bye");
                     break;
        }
    }
    return 0;
    
}



float get_first_number(void)

{
    float a;
    char ch;
    printf("enter first number\n");
    while(scanf("%f",&a) != 1)
    {
        while(( ch = getchar()) != '\n')
        {
            putchar(ch);
        }
        printf(" is not a number\nplease enter a number such as 3 or 5:");
    }
    return a;
}
float get_second_number(void)
{
    float b;
    char ch;
    printf("enter second number\n");
    while(scanf("%f",&b) != 1)
    {
        while((ch = getchar()) != '\n')
        {
            putchar(ch);
        }
        printf(" is not a number \nplease enter a number such as 3 or 5:");
    }
    
    return b;
}
char get_operation(void)

{
    char ch;
    printf("enter the opration of you choice\n");
    printf("a.add   s.subtract m.multiply \n  d.divide  q.quit\n");
     ch = get_right();
     if((ch != 'a') && (ch != 's') && (ch != 'm')  && (ch != 'd') && (ch != 'q'))
     {
         printf("please enter a  s  m  d  q \n");
         ch = get_right();
     }
     return ch;

     
}



char get_right(void)
{
    char ch = getchar();
    
    while(ch != '\n')
    {
        continue;
    }
    return ch;


}

float add(float a, float b)
{
    return a + b;
}
float subtract(float a,float b)
{
    return a - b;
}
float multiply(float a, float b)
{
    return a * b;
}
float divide(float a,float b)
{
   return a / b; 
}

