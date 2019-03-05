// Example program
#include <math.h>
#include <time.h>
#include <stdio.h>

double f1(int n, double a[], double x)
{
    int i;
    double p = a[0];
    for (i=0; i<=n; ++i)
    {
        p += ( a[i] * pow(x,i) );
    }
    return p;
}

double f2(int n, double a[], double x)
{
    int i;
    double p = a[n];
    for (i=n; i>0; --i)
    {
        p = x*p + a[i-1];
    }
    return p;
}


int main()
{
    double a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    int n = 9;
    double x = 20.16;
    
    time_t begin, end;
    double spent1, spent2;
    
    begin = clock();
    double r1 = f1(n, a, x);
    end = clock();
    spent1 = (double)(end-begin) / CLOCKS_PER_SEC;
    
    begin = clock();
    double r2 = f2(n, a, x);
    end = clock();
    spent2 = (double)(end-begin) / CLOCKS_PER_SEC;
    
    
    printf("result1 = %f\n", r1);
    printf("result2 = %f\n", r2);
    
    printf("time spent1 = %f\n", spent1);
    printf("time spent2 = %f\n", spent2);
    
    return 0;
}

