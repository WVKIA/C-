#include <stdio.h>
#define FUNDLEN 50
#define N 2

struct fund

{
    char bank[FUNDLEN];
    double bankfund;
    char save[FUNDLEN];
    double savefund;
};

double sum(const struct fund money[],int n);
int main()
{
    struct fund jones[N] = {{"garlic_melon bank",3024.72,"lucky's saving and loan",9237.11},{"honest jack'bank",3534.28,"party time savings",3203.89}};
    printf("the jonese have a total of $%.2f \n",sum(jones,N));
    return 0;
}
double sum(const struct fund money[],int n)
{
    double total;
    int i;
    for(i = 0,total = 0;i < n; i++)
    {
        total += money[i].bankfund + money[i].savefund;
    }
    return total;
}


