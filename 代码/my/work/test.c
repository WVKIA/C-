#include <stdio.h>
#include <string.h>
#define SIZE 50
int main()
{
    char flower[SIZE];
    char addon[] = "s smell like old shoes";

    puts("what is your favorite flower?");
    gets(flower);
    strcat(flower,addon);
    puts(flower);
    puts(addon);

    printf("%s %s",flower,addon);

    return 0 ;

}
