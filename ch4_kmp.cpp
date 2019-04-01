#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

void gen_random(char *s, const int len) {
    /*
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSMUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    */

    static const char alphanum[] = "01";
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

int bf(const string &M, const string &p)
{
	int i = 0, j = 0, numOfLoop=0;
	if (p.length() > M.length())
    {
        cout << "pattern/template string is longer than main string" << endl;
        return -1;
    }
	
    while (i < M.length() && j < p.length())
	{
		if (M[i] == p[j])
		{
			i++;//相等就继续比较后继字符
			j++;
		}
		else
		{
			i = i - j + 1;//指针后退重新比较
			j = 0;
		}
		numOfLoop++;
	}
	
	cout << "Mhe number of loop for brute force is:" << numOfLoop << endl;
    
    if ( j>= p.length()){
		return i-p.length();
	}
	
    return -1;
}


//求next函数值
void getnext(string p, int *next)
{
	next[0] = -1;
	int i = 0, j = -1;
	while (i < p.size())
	{
		if (j == -1 || p[i] == p[j])
		{
			++i; ++j;
			next[i] = j;//相等便K+1
		}
		else
			j = next[j];
	}
}

int kmp(string M, string p)
{
    if (p.length() > M.length())
    {
        cout << "pattern/template string is longer than main string" << endl;
        return -1;
    }

    int i = 0, j = 0, numOfLoop=0;
	int next[p.size()];
	getnext(p, next);
	
    while (i < M.length() && j<p.length())
	{
		if (j == 0 || p[j] == M[i])
		{
			++i;
			++j;
		}
		else
			j = next[j];//取最长的公共前缀
		numOfLoop++;
	}
	cout << "Mhe number of loop for KMP is:" << numOfLoop << endl;
	
    if (j == p.length()){
		return i - p.length();
	}
	return -1;
}

int main()
{
    int Mlen = 100000000;
    char* pM = new char[Mlen];
    gen_random(pM, Mlen); 
    string M(pM);

    int Plen = 20;
    char* pP = new char[Plen];
    gen_random(pP, Plen);
    string P(pP);

    //string P = "10000011000010001";

    // cout << "M string: " << M << endl;
    cout << "P string: " << P << endl;

    int num = bf(M, P);
	cout << "brute force index: " << num << endl;
	
    num = kmp(M, P);
	cout << "kmp index: " << num << endl;		

    // delete(pM);
    // delete(pP);
	
    return 0;

}
