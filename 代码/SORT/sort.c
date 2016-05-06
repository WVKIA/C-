#include <stdio.h>
#define M 10
void show(int a[],int n)
{
    int i;
    for( i = 0;i < n;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n");
}
void bubble(int a[],int n)
{
    int i,j,tmp;
    for(i = n;i > 0; i--)
    {
        for(j = 0; j < i-1; j++)
        {
            if(a[j] > a[j+1])
            {
                tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;

            }
        }
    }
}
void insert_sort(int a[],int n)
{
    int i,j,tmp,t;
    for(i = 0; i < n; i++)
    {
        tmp = a[i];
        for(j = 0; j< i; j++)
        {
            if(tmp < a[j])
            {
                for(t = i-1;t>=j;t--)
                {
                    a[t+1] = a[t];
                }
                a[j] = tmp;
                break;
            }
        }
    }
}


void swap(int *a,int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}
void insert_sort_swap(int a[],int n)
{
    int i,j;
    for(i = 1;i < n; i++)
    {
        for(j = i - 1;j >= 0 && a[j] > a[j+1];j--)
        {
            swap(&a[j],&a[j+1]);
        }
    }
}

*****************************************************************************************************

int part(int *a, int l, int r)
{
    int tmp = 0;
    int x = a[r];
    int i = l - 1;
    int j = 0;
    for(j = l; j < r; j++)
    {
        if(a[j] <= x)
        {
            i++;
            tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
        }                                        //  quick sort write-test
    }
    a[r] = a[i + 1];
    a[i+1] = x;
    return i+1;
}
void quick_sort(int *a,int l, int r)
{
    if(l >= r)
    {
        return ;
    }
    mid = pation(*a,l,r);
    quick_sort(*a,l,mid-1);
    quick_sort(*a,mid+1,r);
}

********************************************************************************************************

int main()

{
    int a[M] = {1,4,2,22,4,3,7,8,3,34};
    show(a,M);
    insert_sort_swap(a,M);
    show(a,M);
    return 0;
}
