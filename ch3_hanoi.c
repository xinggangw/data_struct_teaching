// Example program
#include <stdio.h>
#include <time.h>

void move(char from, int n, char to)
{
    printf("move plate %d from %c to %c\n", n, from, to);
}

void hanoi(int n, char x, char y, char z)
{
    if (1 == n)    
    {
        move(x, 1, z);
    }
    else
    {
        hanoi(n-1, x, z, y);
        move(x, n, z);
        hanoi(n-1, y, x, z);
    }
}

int main()
{
    time_t begin, end;
    
    int n = 24;
    
    begin = clock();
    hanoi(n, 'x', 'y', 'z');
    end = clock();
    
    double spent = (double)(end-begin) / CLOCKS_PER_SEC;
    printf("\ndepth = %d, time = %.3f seconds\n", n, spent);
}

