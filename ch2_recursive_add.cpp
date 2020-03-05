#include <stdio.h>
int add(int a, int b)
{
    if (0 == a)
        return b;
    else
        return add(--a, ++b);
}
int main()
{
    int a, b;
    a = 5000;
    b = 100000;
    printf( "a+b = %d\n", add(a, b));
    return 0;
}

