#include "stdafx.h"
#include <stack>
#include <iostream>

using namespace std;

void printMaze(char maze[][16]);

void printMaze(char maze[][16]) {
        printf(" ");
    for (int i = 0; i <10; i++)
        for (int j = 0; j < 16; j++) {
            if (j == 15)
                printf("\n");
            printf("%c", maze[i][j]);
        }
    printf("\n");
};

int main()
{
    char    maze[10][16] = {
        "OOOOOOOOOOOOOOO",        //start is [1][1] , end is [8][13]
        "O O O OOO O  OO",
        "O             O",
        "O O OOOOOOO O O",    
        "O O   O   O   O",    
        "O OOO  OO  OOOO",
        "O    O O      O",
        "OO O O O OOO OO",
        "OO   O   O    O",
        "OOOOOOOOOOOOOOO"    
        
    };



    printMaze(maze); //prints unsolved maze

    stack<int>stackR;
    stack<int>stackC;

    int r = 1;
    int c = 1;

    bool done = false;

    while (!done){

        if (r == 10 - 2 && c == 16 - 2)
            done = true;

        if (maze[r][c + 1] == ' ')    //checks east
        {
            stackR.push(r);                
            stackC.push(c);
            maze[r][c] = 'x';
            c++;
        }
        else if (maze[r + 1][c] == ' ')    //checks south
        {
            stackR.push(r);                
            stackC.push(c);
            maze[r][c] = 'x';
            r++;
        }
        else if (maze[r][c - 1] == ' ') // checks west
        {
            stackR.push(r);                
            stackC.push(c);
            maze[r][c] = 'x';
            c--;
        }
        else if (maze[r - 1][c] == ' ') //checks north
        {
            stackR.push(r);
            stackC.push(c);
            maze[r][c] = 'x';
            r--;
        }
        else {
            if (!stackR.empty()) //if stack is not empty, mark current pos. as d
                                //and back track
            {
                maze[r][c] = 'D';
                
                stackC.pop();
                stackR.pop();
                
                }            
            
            else
            {
                done = true; 
                printMaze(maze); //prints maze solution 
            }

        }
    }

    double test;
    scanf("%lf", &test);
    return 0;
}
