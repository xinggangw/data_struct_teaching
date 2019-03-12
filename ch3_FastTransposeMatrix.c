/*
* @Author: Song Dejia
* @Date:   2019-03-12 00:27:27
* @Last Modified by:   Song Dejia
* @Last Modified time: 2019-03-12 02:53:59
*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#define MAX_SIZE 15 //默认初始化三元组长度10(可修改)

using namespace std;
/* 定义三元组 */
typedef struct{
	int i, j;
	int val; 
}triple;

/* 定义用三元组压缩存储的矩阵*/
typedef struct{
	triple data[MAX_SIZE]; //三元组顺序表,data[0]表示矩阵行数，列数，非零元素个数
}TSMatrix;

/*
 * 功能说明: 快速转置
 * 参数说明：
 *     M -- 待转置矩阵
 *     T -- 转置完成后需在T上赋值
 * 返回值：
 #     转置成功 则返回True,否则false
 */
bool fastTransposeMatrix(TSMatrix M, TSMatrix *T){
	if(NULL == T || M.data[0].i < 1 || M.data[0].j < 1 || M.data[0].val < 1) return false;
	
	//矩阵行数列数互换, 非0值不变
	T->data[0].i = M.data[0].j;
	T->data[0].j = M.data[0].i;
	T->data[0].val = M.data[0].val;

	//1.初始化
	//按列初始化为0, 其余值未赋值.这里注意
	//编译器有可能会把它置为0，所以未被赋值的地方要置为-1
	//这里是从1开始索引，目的是方便用列序号直接查找
	int array[M.data[0].j+1];

	//2.计算辅助向量num,从三元组中去遍历时间复杂度更低
	//注意 data[0] 表示的是rows, cols, num. 
	//data[x].j 从1开始
	for(int t = 1; t <= M.data[0].val; t++){
		int j = M.data[t].j;
		array[j]++;
	}

	//3.计算辅助向量pos
	int cpos[M.data[0].j+1];
	cpos[0] = -1;
	cpos[1] = 1;
	for(int col = 2; col <= M.data[0].j; col++) cpos[col] = cpos[col - 1] + array[col - 1];

	//4.赋值
	for(int p = 1; p <= M.data[0].val; p++){
		int col = M.data[p].j;
		int q = cpos[col];
		T->data[q].i = M.data[p].j;
		T->data[q].j = M.data[p].i;
		T->data[q].val = M.data[p].val;
		cpos[col]++;
	}
	
	return true;
}

int main(){
	TSMatrix M;
	TSMatrix *T = (TSMatrix*)malloc(sizeof(TSMatrix));
	if(T == NULL) exit(0);//判断是否分配成功

	M.data[0].i = 6;
	M.data[0].j = 6;
	M.data[0].val = 8;
    if (M.data[0].val > MAX_SIZE)
    {
        printf("error: non zero iterms exceeds matrix capacity\n");
        return 0;
    }
    if (M.data[0].val > 0.3*M.data[0].i*M.data[0].j)
    {
        printf("warning: the matrix is not so sparse, you may try naive matrix transpose algorithm\n");
    }

	M.data[1].i = 1;
	M.data[1].j = 2;
	M.data[1].val = 12;

	M.data[2].i = 1;
	M.data[2].j = 3;
	M.data[2].val = 9;

	M.data[3].i = 3;
	M.data[3].j = 1;
	M.data[3].val = -3;

	M.data[4].i = 3;
	M.data[4].j = 5;
	M.data[4].val = 14;

	M.data[5].i = 4;
	M.data[5].j = 3;
	M.data[5].val = 24;

	M.data[6].i = 5;
	M.data[6].j = 2;
	M.data[6].val = 18;	

	M.data[7].i = 6;
	M.data[7].j = 1;
	M.data[7].val = 15;

	M.data[8].i = 6;
	M.data[8].j = 4;
	M.data[8].val = -7;

	bool status = fastTransposeMatrix(M, T);
	if(!status){
		cout << "Transpose Fail !!!" << endl;
		exit(0);
	}

	//show
	int M1[36], T1[36];
	for(int i = 0; i < 36; ++i){
		M1[i] = 0;
		T1[i] = 0;
	}

	cout << "++++++++++++++ Original Matrix ++++++++++++" <<endl;
	for(int index = 1; index <= 8; ++index){
		int r = M.data[index].i - 1;
		int c = M.data[index].j;
		int v = M.data[index].val;
		int id = r * 6 + c - 1;
		M1[id] = v;
	}

	for(int index = 0; index <= 35; ++index){
		int r = int(index / 6);
		int c = int(index % 6);
		if(c == 5) cout << M1[index] << endl;
		else cout << M1[index] << '\t';
	}


	cout << "++++++++++++++ Transposed Matrix ++++++++++++" <<endl;
	for(int index = 1; index <= 8; ++index){
		int r = T->data[index].i - 1;
		int c = T->data[index].j;
		int v = T->data[index].val;
		int id = r * 6 + c - 1;
		T1[id] = v;
	}

	for(int index = 0; index <= 35; ++index){
		int r = int(index / 6);
		int c = int(index % 6);
		if(c == 5) cout << T1[index] << endl;
		else cout << T1[index] << '\t';
	}
	return 0;
}































