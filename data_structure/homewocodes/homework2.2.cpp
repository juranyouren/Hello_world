#include<iostream>
using namespace std;
#include<iostream>
using namespace std;
template<class T>
class circularChain;
template<class T>
class twoWayNode
{
	template<class T>
	friend void split(circularChain<T>& a, circularChain<T>& b, circularChain<T>& c);
	friend circularChain<T>;
private:
	twoWayNode<T>* forward;
	twoWayNode<T>* backward;
	T data;
public:
	twoWayNode(T Data) { data = Data; forward = nullptr; backward = nullptr; }
	twoWayNode() { data = NULL; forward = nullptr; backward = nullptr; }
};

template<class T>
class circularChain
{
	template<class T>
	friend void split(circularChain<T>& a, circularChain<T>& b, circularChain<T>& c);
	friend twoWayNode<T>;
private:
	twoWayNode<T>* head;
	twoWayNode<T>* tail;
public:
	circularChain() { head = nullptr; tail = nullptr; }
	circularChain(circularChain<T>& a) { head = a.head; tail = a.tail; }
	void insert(T data)
	{
		twoWayNode<T>* cur = new twoWayNode<T>(data);
		if (!head)
		{
			head = cur;
			tail = head;
			head->forward = head;
			head->backward = nullptr;
		}
		cur->backward = tail;
		tail->forward = cur;
		cur->forward = head;
		head->backward = cur;
		tail = cur;
		
	}
	void print()
	{
		if (!head)
		{
			cout << "empty";
			return;
		}
		twoWayNode<T>* cur = head;
		cout << cur->data << " ";
		cur = cur->forward;
		while (cur!=head)
		{
			cout << cur->data << " ";
			cur = cur->forward;
		}
	}
	void revprint()
	{
		twoWayNode<T>* cur = tail;
		cout << cur->data << " ";
		cur = cur->backward;
		while (cur!=tail)
		{
			cout << cur->data << " ";
			cur = cur->backward;
		}
	}
	void split(circularChain<T>&a, circularChain<T>& b)
	{
		if (!head)return;
		int i = 1;
		twoWayNode<T>* cur = head;
		a.head = cur;
		a.tail = a.head;
		cur = cur->forward;
		while (cur != head)
		{
			
			if (i % 2)
			{
				
				if (i == 1)
				{
					b.head = cur;
					b.tail = b.head;
				}
				else
				{
					cur->backward = b.tail;
					b.tail->forward = cur;
					b.tail = cur;
				}
			}
			else
			{
				cur->backward = a.tail;
				a.tail->forward = cur;
				a.tail = cur;
				
				
			}
			cur = cur->forward;
			i++;
		}
		if (!b.head)return;
		a.tail->forward = a.head;
		a.head->backward = a.tail;
		b.tail->forward = b.head;
		b.head->backward = b.tail;
	}
};
template<class T>
void split(circularChain<T>& a, circularChain<T>& b, circularChain<T>& c)
{
	if (!c.head)return;
	int n, m;
	twoWayNode<T>* cur = new twoWayNode<T>;
	cur =c.head;
	int i = 0;
	while(cur!=c.tail)
	{
		if (i % 2)
		{
			n = cur->data;
			a.insert(n);
		}
		else
		{
			m = cur->data;			
			b.insert(m);
		}
		 cur = cur->forward;
		 i++;
	}
	if (i % 2)
	{
		n = cur->data;
		a.insert(n);
	}
	else
	{
		m = cur->data;
		b.insert(m);
	}
}
void test01()
{
	circularChain<int> a, b, c;
	for (int i = 0; i < 10; i++)
	{
		a.insert(i);
	}
	split<int>(b, c, a);
	a.print(); cout << endl;
	b.print(); cout << endl;
	c.print(); cout << endl;
}
void test02()
{
	circularChain<int> a, b, c;
	split<int>(b, c, a);
	a.print(); cout << endl;
	b.print(); cout << endl;
	c.print(); cout << endl;
}
void test03()
{
	circularChain<int> a, b, c;
	a.insert(1);
	split<int>(b, c, a);
	a.print(); cout << endl;
	b.print(); cout << endl;
	c.print(); cout << endl;
}
void test11()
{
	circularChain<int> a, b, c;
	for (int i = 0; i < 10; i++)
		a.insert(i);
	a.print(); cout << endl;
	a.split(b, c);
	b.print(); cout << endl;
	c.print(); cout << endl;
}
void test12()
{
	circularChain<int> a, b, c;
	
	a.print(); cout << endl;
	a.split(b, c);
	b.print(); cout << endl;
	c.print(); cout << endl;
}
void test13()
{
	circularChain<int> a, b, c;
	a.insert(1);
	a.insert(1);
	a.print(); cout << endl;
	a.split(b, c);
	b.print(); cout << endl;
	c.print(); cout << endl;
}
int main()
{
	test01();
	test02();
	test03();
	test11();
	test12();
	test13();
}