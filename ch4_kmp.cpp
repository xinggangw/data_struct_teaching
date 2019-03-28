#include <iostream>
#include <string>

using namespace std;

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
	if (i>= m){
		cout << "The number of loop:" << numOfLoop << endl;
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
	int next[100];
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
	if (j == T.size()){
		cout << "The number of loop:" << numOfLoop << endl;
		return i - T.size();
		}
	return -1;
}
int main()
{
    string T = "ababaababcb";
	string P = "ababc";
	
    int num = bf(P, T);
	cout << "brute force: " << num;
	
    num = kmp(P, T);
	cout << "kmp: " << num;			
	
    return 0;

}
