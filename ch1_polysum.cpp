// Example program
#include <math.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

float f1(int n, float a[], float x)
{
    int i;
    float p = a[0];
    for (i=0; i<=n; ++i)
    {
        p += ( a[i] * pow(x,i) );
    }
    return p;
}

float f2(int n, float a[], float x)
{
    int i;
    float p = a[n];
    for (i=n; i>0; --i)
    {
        p = x*p + a[i-1];
    }
    return p;
}


int main()
{
    int n = 100000;
    float* a = (float *) malloc(sizeof(float)*(n+1));
    // init a
    for (int j=0; j<=n; ++j)
        a[j] = (float)j*0.01;
    float x = 1.0001;
    
    time_t begin, end;
    float spent1, spent2;
    
    begin = clock();
    float r1 = f1(n, a, x);
    end = clock();
    spent1 = (float)(end-begin) / CLOCKS_PER_SEC;
    
    begin = clock();
    float r2 = f2(n, a, x);
    end = clock();
    spent2 = (float)(end-begin) / CLOCKS_PER_SEC;
    
    
    printf("result1 = %f\n", r1);
    printf("result2 = %f\n", r2);
    
    printf("time spent1 = %f\n", spent1);
    printf("time spent2 = %f\n", spent2);
    
    free(a);
    return 0;
}

