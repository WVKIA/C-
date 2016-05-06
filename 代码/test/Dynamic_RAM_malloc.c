#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void  show(void);
int main()
{


    show();
    return 0;



}
void show(void)
{
    int *pb;
    int *pa = malloc(2 * sizeof(int));
    if(NULL == pa)
    {
        free(pa);
        return ;
    }
    int space = 2;
    int n = 0;
    int m;
    int i;

    while(1)
    {
        scanf("%d",&m);
        if(0 == m)
        {

            break;
        }
        if(findint(pa,n,m) == 1)
        {
            if(n == space)
            {
                pb = malloc(space * 2 *sizeof(int));
                if(NULL == pb)
                {
                    free(pa);
                    return ;
                }
                memcpy(pb,pa,n * sizeof(int));
                space = space * 2;
                free(pa);
                pa = pb;


            }


            pa[n] = m;

            n ++;

        }
    }
    printf("the number of scanf is %d\n",n);
    for(i = 0; i < n; i++)
    {
        printf("%d ",pa[i]);
    }
    free(pb);

}

int findint(int * pa, int n,int m)
{
    int j = 0;
    for(j = 0; j < n; j++)
    {
        if(pa[j] == m)
        {
            return -1;;
        }

    }
    return 1;
}
