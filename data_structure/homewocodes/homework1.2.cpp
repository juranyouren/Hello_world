#include<iostream>
using namespace std;
int set[26] = { 0 };
void Print(int* set)
{
	for (int i = 0; i < 26; i++)
	{
		if(set[i])
		cout << (char)(97+i);
	}
	cout << endl;
}
void subset(int n)
{
	
	if (n <= 0 || n > 26)
	{
		cout << "WRONG";
		return;
	}
	if (n == 1)
	{
		set[0] = 0;
		Print(set);
		set[0] = 1;
		Print(set);
	}
	else
	{
		set[n - 1] = 0;
		subset(n - 1);
		set[n - 1] = 1;
		subset(n - 1);
	}
	
}
//int main()
//{
//	int n;
//	cin >> n;
//	subset(n);
//	return 0;
//}