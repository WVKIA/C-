#include <stdio.h>
#define m 10
#define n 10
#define true 1
#define false 0
int saddle(int a[m][n])
{
    int count = 0,k,i,j,rowmin,colmax;
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < n; j++)
        
        {
            k = 0;
            while  ((k < n) && (a[i][k] >= a[i][j]))
            {
                k++;
            }
            if(k < n)
            {
                rowmin = true;
            }
            else
            {
                rowmin = false;
            }
            if(rowmin == true)
            {
                k = 0;
                while((k < m) &&  (a[k][j]) <= a[i][j])
                {
                    k++;
                }
                if(k < m)
                {
                    colmax = false;
                }
                else
                {
                    colmax = true;
                }
            }
            if(rowmin == true && colmax == true)
            {
                printf("%d\n",a[i][j]);
                count++;
            }
        }
    }
    return count;
}
int main()

{
    int i,j;
    int a[m][n] ;
    for(i = 0; i< m;i++)
    {
        for(j = 0;j < n; j++)
        {
            a[i][j] = i*j;
        }
    }
    int c = saddle(a);
}
