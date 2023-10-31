#include <iostream>
#include<ostream>

using namespace std;
template <class T>
class CNode;
template <class T>
class Chain;
template <class T>
class HeadNode;
template <class T>
class LinkedMatrix;
template <class T>
class CNode
{
    friend class Chain<T>;
    friend class LinkedMatrix<T>;
    friend class HeadNode<T>;
    template <class T>
    friend ostream& operator<<(ostream&, const LinkedMatrix<T>&);
    template <class T>
    friend istream& operator>>(istream&, LinkedMatrix<T>&);

public:
    CNode() { this->next = nullptr; }
    CNode(int col, T value)
    {
        this->col = col;
        this->value = value;
        this->next = nullptr;
    }
    CNode(CNode<T>& a) { col = a.col; value = a.value; next = a.next; }

    CNode* next;
private:
    int col;
    T value;
    
};

template <class T>
class Chain
{
    friend class CNode<T>;
    friend class LinkedMatrix<T>;
    friend class HeadNode<T>;
    template <class T>
    friend ostream& operator<<(ostream&, const LinkedMatrix<T>&);
    template <class T>
    friend istream& operator>>(istream&, LinkedMatrix<T>&);

public:
    T* head;
    T* tail;

    Chain() : head(nullptr), tail(nullptr) {}

    // Copy constructor for Chain
    Chain(const Chain& other) : head(nullptr), tail(nullptr)
    {
        T* current = other.head;
        while (current)
        {
            T* newNode = new T(*current);
            if (!head)
            {
                head = newNode;
                tail = head;
                tail->next = nullptr;
            }
            else
            {
                tail->next = newNode;
                tail = newNode;
                tail->next = nullptr;
            }
            current = current->next;
        }
    }

    void insert(T& a)
    {
        if (!head)
        {
            head = &a;
            tail = head;
            tail->next = nullptr;
        }
        else
        {
            tail->next = &a;
            tail = &a;
            tail->next = nullptr;
        }
    }
};

template <class T>
class HeadNode
{
   
    friend class Chain<T>;
    friend class LinkedMatrix<T>;
    friend class CNode<T>;
    template <class T>
    friend ostream& operator<<(ostream&, const LinkedMatrix<T>&);
    template <class T>
    friend istream& operator>>(istream&, LinkedMatrix<T>&);

public:
    HeadNode() : row(0), next(nullptr)
    {
        nodechain.head = nullptr;
        nodechain.tail = nullptr;
    }

    HeadNode(int r) : row(r), next(nullptr)
    {
        nodechain.head = nullptr;
        nodechain.tail = nullptr;
    }
    HeadNode* next;
private:
    int row;
    Chain<CNode<T>> nodechain;
   
};

template <class T>
class LinkedMatrix
{
    friend class CNode<T>;
    friend class Chain<T>;
    friend class HeadNode<T>;
    template <class T>
    friend ostream& operator<<(ostream&, const LinkedMatrix<T>&);
    template <class T>
    friend istream& operator>>(istream&, LinkedMatrix<T>&);

public:
    LinkedMatrix() : rows(0), cols(0)
    {
        headchain.head = nullptr;
        headchain.tail = nullptr;
    }

    // Copy constructor for LinkedMatrix
    LinkedMatrix(const LinkedMatrix& a) : rows(a.rows), cols(a.cols)
    {
        HeadNode<T>* current = a.headchain.head;
        while (current)
        {
            HeadNode<T>* newNode = new HeadNode<T>(*current);
            if (!headchain.head)
            {
                headchain.head = newNode;
                headchain.tail = headchain.head;
                headchain.tail->next = nullptr;
            }
            else
            {
                headchain.tail->next = newNode;
                headchain.tail = newNode;
                headchain.tail->next = nullptr;
            }
            current = current->next;
        }
    }

private:
    int rows, cols;
    Chain<HeadNode<T>> headchain;
};

template <class T>
ostream& operator<<(ostream& out, const LinkedMatrix<T>& a)
{
    out << "rows=" << a.rows << endl;
    out << "cols=" << a.cols << endl;
    HeadNode<T>* cur = a.headchain.head;
    while (cur)
    {
        CNode<T>* cur1 = cur->nodechain.head;
        while (cur1)
        {
            out << "(" << cur->row << "," << cur1->col << ")=" << cur1->value << endl;
            cur1 = cur1->next;
        }
        cur = cur->next;
    }
    return out;
}

template <class T>
istream& operator>>(istream& in, LinkedMatrix<T>& a)
{
    cout << "rows,cols,terms" << endl;
    int n = 0;
    in >> a.rows >> a.cols >> n;
    for (int i = 0; i < n; i++)
    {
        int r = 0, c = 0, v = 0;
        cout << "row,col,value" << endl;
        in >> r >> c >> v;
        CNode<T> cnd(c, v);
        HeadNode<T>* fd = a.headchain.head;
        while (fd)
        {
            if (fd->row == r)
                break;
            fd = fd->next;
        }
        if (!fd)
        {
            HeadNode<T> hnd(r);
            hnd.nodechain.insert(cnd);
            a.headchain.insert(hnd);
        }
        else
        {
            fd->nodechain.insert(cnd);
        }
    }
    return in;
}

//void test31()
//{
//    LinkedMatrix<int> a;
//    cin >> a;
//    cout << a;
//}
//
//int main()
//{
//    test31();
//    return 0;
//}
