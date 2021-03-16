#include <stdio.h>

void printarray(int a[], int n, char name)
{
    for (int index=0; index<n; ++index)
    {
        printf("%c[%d] = %d\t", name, index, a[index]);
    }
    printf("\n");
}

int main()
{
    int a[3];
    a[0] = 10;
    a[1] = 20;
    a[2] = 100;
   
    int b[3];
    b[0] = 100;
    b[1] = 0;
    b[2] = 0;

    int c[3];

    int index;
    for (index=0; index<3; ++index)
    {
        c[index] = a[index] + b[index];
    }
    
    printarray(a, 3, 'a');
    printarray(b, 3, 'b');
    printarray(c, 3, 'c');

    return 1;
}

