#include <stdio.h>

#define MAXTITL 40
#define MAXAUTL 40
#define MAXBKS 100

struct book 
{
    char title[MAXTITL];
    char author[MAXAUTL];
    float value;
};
int main()
{
    struct book library[MAXBKS];
    int count = 0;
    int index;

    printf("please enter the book title\n");
    printf("press [enter] at the start of a line to stop\n");
    while (count < MAXBKS && gets(library[count].title) != NULL && library[count].title[0] !='\0')
    {
        printf("now enter you author\n");
        gets(library[count].author);
        printf("now enter the value\n");
        scanf("%f",&library[count++].value);
        while(getchar() != '\n')
        
        {
            continue;
        }
        if(count < MAXBKS)
        {
            printf("enter the next title\n");
        }
    }
    if (count > 0)
    {
        printf("here is the list of your book]\n");
        for(index = 0; index < count; index ++)
        
        {
            printf("%s by %s :$%.3f\n",library[index].title,library[index].author,library[index].value);
        }
    }
    else
    {
        printf("no book ?too bad\n");
    }
    return 0;

}
