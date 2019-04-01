#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

void gen_random(char *s, const int len) {
    /*
    static const char alphanum[] =
        "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    */

    static const char alphanum[] = "01";
    for (int i = 0; i < len; ++i) {
        s[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    s[len] = 0;
}

int bf(const string &T, const string & p)
{
	int i = 0, j = 0, numOfLoop=0;
	int m = T.length();//模式串长度
	int n = p.length();//主串长度
	if (m > n)return -1;
	
    while (i < m && j < n)
	{
		if (T[i] == p[j])
		{
			i++;//相等就继续比较后继字符
			j++;
		}
		else
		{
			j= j- i + 1;//指针后退重新比较
			i = 0;
		}
		numOfLoop++;
	}
	
	cout << "The number of loop for brute force is:" << numOfLoop << endl;
    
    if (i>= m){
		return j- m;
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

int kmp(string T, string p)
{
	int i = 0, j = 0, numOfLoop=0;
	int next[p.size()];
	getnext(p, next);
	
    while (i < p.size()&&j<T.size())
	{
		if (j == 0 || p[i] == T[j])
		{
			++i;
			++j;
		}
		else
			j = next[j];//取最长的公共前缀
		numOfLoop++;
	}
	cout << "The number of loop for KMP is:" << numOfLoop << endl;
	
    if (j == T.size()){
		return i - T.size();
	}
	return -1;
}
int main()
{
    int Tlen = 1000000;
    // int Plen = 10;

    char* pT = new char[Tlen];
    //char* pP = "abababa";

    gen_random(pT, Tlen);
    //gen_random(pP, Plen);

    string T(pT);
	string P = "0000000001";

    //cout << "T string: " << T << endl;
    cout << "P string: " << P << endl;

    int num = bf(T, P);
	cout << "brute force index: " << num << endl;
	
    num = kmp(T, P);
	cout << "kmp index: " << num << endl;		

    // delete(pT);
    // delete(pP);
	
    return 0;

}
