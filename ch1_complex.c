/*
* @Author: Song Dejia
* @Date:   2019-03-03 17:25:10
* @Last Modified by:   Song Dejia
* @Last Modified time: 2019-03-03 18:06:03
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef float ItermType;
typedef struct Complex
{
	ItermType r;
	ItermType v;
}Cpx, *pCpx;

void Assign(pCpx A, ItermType r, ItermType c);
void Add(pCpx A, Cpx B);
void Minus(pCpx A, Cpx B);
void Multiply(pCpx A, Cpx B);
void Divide(pCpx A, Cpx B);

int main()
{
 	pCpx pCpxA = (pCpx)malloc(sizeof(Cpx));
 	Cpx  CpxB;

 	// ++++++ Init +++++++++++++++++++
 	Assign(pCpxA, 10, 1);
 	Assign(&CpxB, 1,  1);
    
 	// ++++++ OP.  +++++++++++++++++++
 	//Add(pCpxA, CpxB);
 	//Minus(pCpxA, CpxB);
 	//Multiply(pCpxA, CpxB);
 	Divide(pCpxA, CpxB);
 	
    printf("R:%f\n", pCpxA->r);
 	printf("V:%f\n", pCpxA->v);

    //system("pause");
    return 0;
}

void Assign(pCpx A, ItermType r, ItermType v){
	A->r = r;
	A->v = v;
}

void Add(pCpx A, Cpx B){
	A->r += B.r;
	A->v += B.v;
}

void Minus(pCpx A, Cpx B){
	A->r -= B.r;
	A->v -= B.v;
}

void Multiply(pCpx A, Cpx B){
	ItermType NewR, NewV;
	NewR = A->r * B.r - A->v * B.v;
	NewV = A->r * B.v + A->v * B.r;
	A->r = NewR;
	A->v = NewV;
}

void Divide(pCpx A, Cpx B){
	ItermType NewR, NewV, MODE;
	MODE = pow(B.r, 2) + pow(B.v, 2);
	if(MODE == 0){
		printf("B shouldnt be 0\n");
		return;
	}
	NewR = (A->r*B.r+A->v*B.v)/MODE;
	NewV = (A->v*B.r-A->r*B.v)/MODE;
	A->r = NewR;
	A->v = NewV;
}



