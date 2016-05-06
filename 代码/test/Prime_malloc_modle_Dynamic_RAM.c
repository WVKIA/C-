#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
void show(int *pa, int m)
{
    int i;
    for(i = 0; i < m; i++)
    {
        printf("%d   ",pa[i]);
    }
}
int is_prime(int a);
//int * prime(int a);
int main()

{
    int n;
    int i;
    int m = 0;
    int *p = NULL;
    int *a = malloc(2 * sizeof(int));
    int space = 2;
    if(NULL == a)
    {
        return -1;
    }
    scanf("%d",&n);
    for(i = 2; i <= n; i++)
    {
        if(is_prime(i))
        {
            if(m == space)
            {
                p = malloc((space * 2) * sizeof(int) );
                if(NULL == p)
                {
                    free(a);
                    return -1;
                }
                memcpy(p,a,m * sizeof(int));  //memcpy( destination *, source *,byte)
                free(a);
                a = p;           
                space = space * 2;
            }
            a[m] = i;
            m ++;
        }
    }
    show(a,m);
    return 0;
}




/*
   int * prime(int a)

   {
   int i;
   int j = 0;
   int k = 0;
   int counter ;
   int *pa = malloc(sizeof(int));;
   int space = 2;
   if(NULL ==a)
   {
   return -1;
   }
   int * pb = NULL;
   for(i = 3; i <= a; i++)
   {
   k = is_prime(i);
   if( k )
   {
   pa[j] = i;
   j++;
   }
   }
   pb = malloc(j + 1);
   if(NULL == pb)
   {
   return NULL;
   }
   pb[0] = 2;
   for(i = 1; i < j + 1; i++)
   {
   pb[i] = pa[i - 1];

   }
   for(i = 0;i < j + 1; i++)
   {
   printf("%5d",pb[i]);
   }

   return pb;
   }

*/

int is_prime(int a)
{
    int i;

    int top = (int )sqrt(a);    //use sqrt to judge ,from 2 to sqrt
    for(i = 2; i <= top; i++)
    {

        if(a % i == 0)
        {
            return 0;
            break;
        }
        /*          break;
                    }
                    else if((a - i ) == temp)
                    {
                    return 1;
                    } 
                    */
    } 

    return 1;

}
