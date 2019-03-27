#include <iostream>
#include <string>
#include<Windows.h>
using namespace std;
int index(const string &T, const string & p)
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
int main()

{

                string T = "ababaababcb";
				string P = "ababc";
				int num = index(P, T);
				cout << num;
				
				system("pause");
               
				return 0;
			

}
