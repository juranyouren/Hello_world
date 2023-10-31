#include<iostream>
using namespace std;
long long int FIB[91] = { 0 };
long long int Fib(int n)
{
	if (n <= 0 || n >= 90)
	{
		cout << "WRONG";
		return 0;
	}
	else if (n == 1) return 1;
	else if (n == 2) return 1;
	else
	{
		if (FIB[n] == 0)
		{
			FIB[n] = Fib(n - 1) + Fib(n - 2);
			return FIB[n];
		}
		else return FIB[n];
	}
}
//int main()
//{
//	int n;
//	cin >> n;
//	cout << Fib(n);
//	return 0;
//}