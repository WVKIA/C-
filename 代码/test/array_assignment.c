#include <stdio.h>
void initarray(int pa[], int n,int m);
int main(void)
{
    int a[4][5];
    initarray(a[0],4,5);
    return 0;
    
}
void initarray(int pa[],int n,int m)
{
    int i,j;
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < m; j++ )
        {
           pa[m *i + j] = i * j;
           printf("%15d",pa[m * i + j]);
        }
        printf("\n");
    }
}
