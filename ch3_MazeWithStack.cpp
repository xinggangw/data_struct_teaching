/*
* @Author: Song Dejia
* @Date:   2019-03-16 21:54:29
* @Last Modified by:   Song Dejia
* @Last Modified time: 2019-03-16 22:53:38
*/
#include<stdio.h>
#include<stdlib.h>

#define MAX_ROW  12
#define MAX_COL  14
#define MAXSIZE  200

int maze[12][14] = {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
    1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 1, 1,
    1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 1,
    1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1,
    1, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1,
    1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 0, 1,
    1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1,
    1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1,
    1, 0, 0, 0, 0, 1 ,0 ,0, 0 ,0 ,1 ,0 ,1 ,1,
    1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0, 1,
    1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1,
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};



typedef struct point{
    int  row, col;
}mark;

typedef mark DataType;

typedef struct {
    DataType data[MAXSIZE]; //每个元素为mark结构
    int top;
}SeqStack, *PSeqStack; //栈的顺序表实现

PSeqStack Init_SeqStack(void){
    PSeqStack S = (PSeqStack)malloc(sizeof(SeqStack));
    if(S)
        S->top = -1;
    else
        exit(-1);
    return S;
}

int Empty_SeqStack(PSeqStack S){
    if (S->top == -1)
        return 1;
    else
        return 0;
}

int Push_SeqStack(PSeqStack S, DataType x){
    if (S->top == MAXSIZE - 1){
        printf("栈满不能入栈\n");
        return 0;
    }
    else{
        S->data[++S->top] = x;
        return 1;
    }
}

int Pop_SeqStack(PSeqStack S,DataType *x)
{
    if(Empty_SeqStack(S))
        return 0;
    else
    {
        *x = S->data[S->top];
        S->top--;
        return 1;
    }
}

int GetTop_SeqStack(PSeqStack S ,DataType *x)
{
    if(Empty_SeqStack(S))
        return 0;
    else
    {
        *x = S->data[S->top];
        return 1;
    }
}
int GetLength_SeqStack(PSeqStack S)
{
    return S->top + 1;
}

void Distory_SeqStack(PSeqStack *S)
{
    if(*S)
        free(*S);
    *S = NULL;
}//end seqstack.h


void print_line()
{
    printf("迷宫如下‘++’代表墙,数字表示探索先后顺序\n");
    int i, j;
    for (i = 0; i < MAX_ROW; i++){
        for (j = 0; j < MAX_COL; j++)
            if (maze[i][j] == 1){    
            	printf("++\t");
            }
            else if (maze[i][j] >= 3){
                printf("%2d\t", maze[i][j] - 2);
            }    
            else{
            	printf("  \t");
            }
            printf("\n");
        }
    printf("已到达出口...\n");
    printf("可见使用栈求出的路径并非最优路径，根据我依次探索的方向不同，结果也将不同\n");
}

void visit(mark p, int sign, PSeqStack S)
{
    Push_SeqStack(S,p);//把当前点压入栈
    switch (sign)
    {
    //0表示路，1表示墙，2表示已经走过。相当于边走边封路
    case 1: p.col++; Push_SeqStack(S, p); maze[p.row][p.col] = 2; break;//向右,把下一点位置压入
    case 2: p.row++; Push_SeqStack(S, p); maze[p.row][p.col] = 2; break;//向下
    case 3: p.col--; Push_SeqStack(S, p); maze[p.row][p.col] = 2; break;//向左
    case 4: p.row--; Push_SeqStack(S, p); maze[p.row][p.col] = 2; break;//向上
    }
}

int main()
{
    mark p = { 1, 1 };
    maze[p.row][p.col] = 2;          //遍历过的点设置为2
    PSeqStack S = Init_SeqStack();   //初始化顺序栈

    Push_SeqStack(S, p);
    while (!Empty_SeqStack(S))
    {
        Pop_SeqStack(S, &p);         //pop + top => get current postion
        if (p.row == MAX_ROW - 2 && p.col == MAX_COL - 2) //到末尾
            break;
        
        //sign 1, 2, 3, 4 为右，下，左，上 //若右边为路，向右
        if (p.col + 1 < MAX_COL - 1 && maze[p.row][p.col + 1] == 0){    
            visit(p, 1, S);//把当前点压入，下一点也压入
            continue;
        }

        if (p.row + 1 < MAX_ROW - 1 && maze[p.row + 1][p.col] == 0){
            visit(p, 2, S);
            continue;
        }

        if (p.col - 1 >= 1 && maze[p.row][p.col - 1] == 0){
            visit(p, 3, S);
            continue;
        }

        if (p.row - 1 >= 1 && maze[p.row - 1][p.col] == 0){
            visit(p, 4, S);
            continue;
        }//以上是对迷宫的四个方向进行操作
    }
    
    //打印结果
    if (p.row == MAX_ROW - 2 && p.col == MAX_COL - 2)//是否为出口
    {
        int count = GetLength_SeqStack(S)+3;//为了与迷宫0,1,2的区别所以基数要以3开始
        printf("成功找到出口，路径倒序输出：\n");
        printf("(%d,%d)\n", p.row, p.col);
        maze[p.row][p.col] = count;
        while (!Empty_SeqStack(S))//按照前驱进行查找
        {
            count--;
            Pop_SeqStack(S, &p);
            maze[p.row][p.col] = count;
            printf("(%d,%d)\n", p.row, p.col);            
        }
        print_line();
    }
    else {
        printf("没有出路\n");
    }
    Distory_SeqStack(&S); //释放内存
    return 0;
}
