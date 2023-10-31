#include<iostream>
#include<iomanip>
using namespace std;
template<class T>
class UpperTriangleMatrix;
template<class T>
class LowerTriangleMatrix
{
	friend UpperTriangleMatrix<T>;
private:
	int n;
	T* t;
public:
	LowerTriangleMatrix(int size)
	{
		n = size; t = new T[n * (n + 1) / 2];
	}
	~LowerTriangleMatrix() { delete[]t; }
	LowerTriangleMatrix<T>& Store(const T& x, int i, int j);
	T Retrieve(int i, int j)const;
	UpperTriangleMatrix<T>* Reverse();
	void Print()const;
};
template<class T>
LowerTriangleMatrix<T>& LowerTriangleMatrix<T>::Store(const T& x, int i, int j)
{
	if (i<1 || j<1 || i>n || j>n)
		throw "Wrong";
	if (i >= j)
	{
		t[i * (i - 1) / 2 + j - 1] = x;
		//cout << i * (i - 1) / 2 + j - 1<<endl;
	}
	else if (x != 0)throw "Wrong";
	return *this;
}
template<class T>
T LowerTriangleMatrix<T>::Retrieve(int i, int j)const
{
	if (i<1 || j<1 || i>n || j>n)
		throw "Wrong";
	if (i >= j)return t[i * (i - 1) / 2 + j - 1];
	return 0;
}
template<class T>
class UpperTriangleMatrix
{
	friend LowerTriangleMatrix<T>;
private:
	int n;
	T* t;
public:
	UpperTriangleMatrix(int size)
	{
		n = size; t = new T[n * (n + 1) / 2];
	}
	UpperTriangleMatrix(UpperTriangleMatrix<T>& M)
	{
		n = M.n;
		t = new T[n * (n + 1) / 2];
		for (int i = 0; i < n * (n + 1) / 2; i++)
		{
			t[i] = M.t[i];
		}
	}

	~UpperTriangleMatrix() { delete[]t; }
	UpperTriangleMatrix<T>& Store(const T& x, int i, int j);
	T Retrieve(int i, int j)const;
	void Print()const;
};
template<class T>
UpperTriangleMatrix<T>& UpperTriangleMatrix<T>::Store(const T& x, int i, int j)
{
	if (i<1 || j<1 || i>n || j>n)
		throw "wrong";
	if (j >= i)t[j * (j - 1) / 2 + i - 1] = x;
	else if (x != 0)throw "wrong";
	return *this;
}
template<class T>
T UpperTriangleMatrix<T>::Retrieve(int i, int j)const
{
	if (i<1 || j<1 || i>n || j>n)
		throw "wrong";
	if (j >= i)return t[j * (j - 1) / 2 + i - 1];
	return 0;
}
template<class T>
UpperTriangleMatrix<T>* LowerTriangleMatrix<T>::Reverse()
{
	UpperTriangleMatrix<T>* M=new UpperTriangleMatrix<T>(n);
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
		{
			M->Store(this->Retrieve(i, j), j, i);
			//cout << this->Retrieve(i, j);
		}
	return M;
}
template<class T>
void LowerTriangleMatrix<T>::Print() const
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (i >= j)
			{
				cout.setf(ios::left);
				cout << setw(5) << t[i * (i - 1) / 2 + j - 1];
			}
				
			else
				cout << setw(5)<<"0 ";
		}
		cout << endl;
	}
}

template<class T>
void UpperTriangleMatrix<T>::Print() const
{
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= n; j++)
		{
			if (j >= i)
			{
				cout.setf(ios::left);
				//cout << "the" << j * (j - 1) / 2 + i - 1 << "th:";
				cout <<setw(5)<< t[j * (j - 1) / 2 + i - 1];
			}
				
			else
				cout <<setw(5)<<"0 ";
		}
		cout << endl;
	}
}
void test01()
{
	LowerTriangleMatrix<int> M1(2);
	M1.Store(2, 1, 1);
	M1.Store(0, 1, 2);
	M1.Store(2, 2, 1);
	M1.Store(3, 2, 2);
	M1.Print();
	M1.Reverse()->Print();
}
void test02()
{
	const int n = 10;
	LowerTriangleMatrix<int> M1(n);
	for(int i=1;i<=n;i++)
		for (int j = 1; j <= n; j++)
		{
			if (i >= j)M1.Store(i * j, i, j);
			else M1.Store(0, i, j);
		}
	M1.Print();
	cout << endl;
	M1.Reverse()->Print();
}
int main()
{
	test02();
	return 0;
}