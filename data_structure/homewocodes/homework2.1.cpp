#include<iostream>
using namespace std;
template<class T>
class extendedChain;
template<class T>
class chainNode
{
	template<class T>
	friend extendedChain<T> meld(extendedChain<T>& a, extendedChain<T>& b);
	friend extendedChain<T>;
private:
	chainNode<T>* next;
	T data;
public:
	chainNode(T Data) { data = Data; next = nullptr; }
	chainNode() { data = NULL; next = nullptr; }
};

template<class T>
class extendedChain
{
	friend chainNode<T>;
	template<class T>
	friend extendedChain<T> meld(extendedChain<T>& a, extendedChain<T>& b);
private:
	chainNode<T>* head;
	chainNode<T>* tail;
public:
	extendedChain() { head = nullptr; tail = nullptr; }
	extendedChain(extendedChain<T>& a) { head = a.head; tail = a.tail; }
	void insert(T data)
	{
		chainNode<T>* cur=new chainNode<T>(data);
		if (!head)
		{
			head=cur;
			tail = head;
		}
		tail->next = cur;
		tail = cur;
	}
	void print()
	{
		chainNode<T>* cur=head;
		while (cur)
		{
			cout << cur->data << " ";
			cur = cur->next;
		}
	}
};
template<class T>
 extendedChain<T> meld(extendedChain<T>& a, extendedChain<T>& b)
{
	chainNode<T>* cura;
	chainNode<T>* curb;
	chainNode<T>* cur;
	if (!a.head)return b;
	if (!b.head)return a;
	cura = a.head->next;
	cur = a.head;
	curb = b.head;
	while (cura&&curb)
	{
		cura = cur->next;
		cur->next = curb;
		if (cura)
		{
			cur = cur->next;
			curb = cur->next;
			cur->next = cura;
			cur = cur->next;
		}
	}
	if (curb)cur->next = curb;
	return a;
}
//int main()
//{
//	extendedChain<int> c;
//
//	extendedChain<int> test01a;
//	for (int i = 0; i < 10; i++)
//	{
//		test01a.insert(i);
//	}
//	extendedChain<int> test01b;
//	for (int i = 0; i < 20; i++)
//	{
//		test01b.insert(i);
//	}
//	cout << "a: ";
//	test01a.print();
//	cout << endl<< "b: ";
//	test01b.print();
//	cout << endl << "c: ";
//	c = meld<int>(test01a, test01b);
//	c.print(); cout << endl;
//
//	extendedChain<int> test02a;
//	for (int i = 0; i < 20; i++)
//	{
//		test02a.insert(i);
//	}
//	extendedChain<int> test02b;
//	for (int i = 0; i < 10; i++)
//	{
//		test02b.insert(i);
//	}
//	cout << "a: ";
//	test02a.print();
//	cout << endl << "b: ";
//	test02b.print();
//	cout << endl << "c: ";
//	c = meld<int>(test02a, test02b);
//	c.print(); cout << endl;
//
//	extendedChain<int> test03a;
//	
//	extendedChain<int> test03b;
//	for (int i = 0; i < 10; i++)
//	{
//		test03b.insert(i);
//	}
//	cout << "a: ";
//	test03a.print();
//	cout << endl << "b: ";
//	test03b.print();
//	cout << endl << "c: ";
//	c = meld<int>(test03a, test03b);
//	c.print(); cout << endl;
//
//	extendedChain<int> test04a;
//	for (int i = 0; i < 10; i++)
//	{
//		test04a.insert(i);
//	}
//	extendedChain<int> test04b;
//	
//	cout << "a: ";
//	test04a.print();
//	cout << endl << "b: ";
//	test04b.print();
//	cout << endl << "c: ";
//	c = meld<int>(test04a, test04b);
//	c.print(); cout << endl;
//
//	extendedChain<int> test05a;
//	
//	extendedChain<int> test05b;
//	
//	cout << "a: ";
//	test05a.print();
//	cout << endl << "b: ";
//	test05b.print();
//	cout << endl << "c: ";
//	c = meld<int>(test05a, test05b);
//	c.print(); cout << endl;
//	return 0;
//}