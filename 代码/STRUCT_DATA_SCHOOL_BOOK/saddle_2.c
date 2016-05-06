#include <stdio.h>
#define m 10
#define n 10
#define true 1
#define false 0

int saddle(int a[m][n])
{
    int count = 0,i,j,k;
    int b[n],c[m];
    for(i = 0; i < m; i++)
    {
        c[i] = a[i][0];
        for(j = 1; j < n; j++)
        {
            if(c[i] > a[i][j])
            {
                c[i] = a[i][j];
            }
        }
    }
    for(j = 0; j < n; j++)
    {
        b[j] = a[0][j];
        for(i = 1; i < m; i++)
        {
            if(b[j] < a[i][j])
            {
                b[j] = a[i][j];
            }
        }
    }
    for(i = 0; i<m; i++)
    {
        for(j=0; j<n; j++)
        
        {
            if(b[j] == c[i])
            {
                count++;
                
            }
        }
    }
}
