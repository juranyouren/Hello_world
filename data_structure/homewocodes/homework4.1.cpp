#include<iostream>
#include<fstream>
using namespace std;
template<class T>
class Node
{
public:
    T data;
    Node<T>* next;
    Node(T d)
    {
        data = d;
        next = NULL;
    }
};
template<class T>
class ChainList
{
public:
    Node<T>* head;
    ChainList()
    {
        head = nullptr;
    }
    void insert(T d)
    {
        Node<T>* p = new Node<T>(d);
        if (head == NULL)
        {
            head = p;
            head->next=head;
            return;
        }
        Node<T>* q = head;
        while (q->next != head)
        {
            q = q->next;
        }
        q->next = p;
        p->next = head;
    }
    void print()
    {
        Node<T>* p = head;
        while (p != NULL)
        {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
    void Delete(int n)
    {
        if(n==1)
        {
            Node<T>* p=head;
            while(p->next!=head)
            {
                p=p->next;
            }
            p->next=head->next;
            delete head;
            head=p->next;
            return;
        }
        Node<T>* p = head;
        Node<T>* q = head;
        for (int i = 1; i < n; i++)
        {
            q = p;
            p = p->next;
        }
        q->next = p->next;
        delete p;
    }
};

void test01()
{
    int n, m;
    ifstream input("input.txt");
    input >> n >> m;
    if(n<=0||m<=0)
    {
        cout<<"WRONG"<<endl;
        return;
    }
    ChainList<int> list;
    list.insert(n);
    for(int i=0;i<n-1;i++)
    {
        list.insert(i+1);
    }
    for(int i=0;i<n;i++)
    {
        for(int j=1;j<m;j++)
        {
            list.head=list.head->next;
        }
        cout<<list.head->next->data<<" ";
        list.Delete(2);
    }
}
void test02()
{
    int n, m;
    ifstream input("input.txt");
    input >> n >> m;
    if(n<=0||m<=0)
    {
        cout<<"WRONG"<<endl;
        return;
    }
    int* a=new int[n];
    for(int i=0;i<n;i++)
    {
        a[i]=i+1;
    }
    int index=-1;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            index++;
            if(index==n)
            {
                index=0;
            }
            while(a[index]==0)
            {
                index++;
                if(index==n)
                {
                    index=0;
                }
            }
        }
        cout<<a[index]<<" ";
        a[index]=0;
    }
    delete[] a;

}

int main()
{
    test01();
    return 0;
}