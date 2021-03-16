#include <stdio.h>
void print_arr(int a[], int n)
{
    for (int i=0; i<n; ++i)
        printf("%d, ", a[i]);
    printf("\n");
}
void swap(int &x, int &y)
{
    int tmp;
    tmp=x;x=y;y=tmp;
}
void max2(int a[], int n)
{
    int p, k, q, t, i, j; 
    k = 3; //log(n)
    p = 1;
    for (i=0; i<k; i++)
    {
        q = 2*p;
        for (t=0; t<n; t=t+q)
        {
            if (a[t] < a[t+1])
                for (j=0; j<i; j++)
                    swap(a[t+j], a[t+j+p]);
            swap(a[t+p], a[t+i]);
        }
        p = q;
    }
    int max1 = a[0];
    int max2 = a[k];
    for (i=1; i<k; i++)
        if (max2 < a[i])
            max2 = a[i];
    printf("max1 = %d, max2 = %d\n", max1, max2);
}

int main()
{
    int n = 8;
    int a[8] = {5, 9, 1, 0, 3, 6, 7, 4};
    print_arr(a, n);
    max2(a, n);
}

