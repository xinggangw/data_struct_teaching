#include <stdio.h>

void max3(int &x, int &y, int &z)
{
    int temp;
    if (x>y){
        if (x>z){ // x > y  & x > z
            if (y>z){
                return;    
            }
            else{
                temp = y;
                y = z;
                z = temp;
                return;
            }
        }
        else{ // z > x > y
            temp = x;
            x = z;
            z = temp;   
            temp = y; 
            y = z;
            z = temp;
        }
    }
    else{
        if (x<z) { // x<y, x<z
            if (y>z){
                // y>z>x
                temp = x;
                x = y;
                y = temp;
                temp = z;
                z = y;
                y = temp;
            }
            else{
                // x < y < z
                temp = z;
                z = x;
                x = temp;
            }
        }
        else {
            // z<x<y
            temp = x;
            x = z;
            z = temp;
            temp = y;
            y = z;
            z = temp;
        }
    }
}

int main()
{
    int x, y, z;
    x = 400000; y = -4; z = 1000;
    max3(x, y, z);
    printf("x = %d, y = %d, z = %d\n", x, y, z);
}

