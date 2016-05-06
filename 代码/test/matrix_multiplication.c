#include <stdio.h>
int var(int m, int n, int l, int pa[m][n], int pb[n][l],int pc[m][l]);
int main(void)
{
    int pa[2][2] = {{1,2},
        {1,2},
        };
    int pb[2][3] = {{1,2,3},{1,2,3}};
    int pc[2][3];

    var(2,2,3,pa,pb,pc);
    return 0;
}
/*
int var(int *pa, int *pb, int *pc,int m,int n,int l)

{
    int i, j;
    int k;
    for(i = 0; i < m; i++)
    {
        for(k = 0;k < l; k++)
        {
            pc[l * i + k] = 0;
            for(j = 0; j <n; j ++)
            {
                pc[l * i + k] += pa[n * i + j] * pb[l * j + k];
            }
        }

    }


}
*/
int var(int m, int n, int l, int pa[m][n], int pb[n][l],int pc[m][l])
{
    int i,j,a;
    int temp = 0;

    for(i = 0; i < m; i++)
    {
        for(j = 0; j < l; j ++)
        {
            temp = 0;
            for(a = 0; a < n; a++)
            {
            temp += pa[i][a] * pb[a][j];
            }
            pc[i][j] = temp;
            printf("%4d",pc[i][j]);
        }
            printf("\n");
    }
}

