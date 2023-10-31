#include<iostream>
#include<fstream>
using namespace std;
template<class T>
class Stack
{
    public:
    T* data;
    int top;
    int maxsize;
    Stack(int size)
    {
        data = new T[size];
        top = -1;
        maxsize = size;
    }
    void push(T d)
    {
        if (top == maxsize - 1)
        {
            cout << "Stack is full!" << endl;
            return;
        }
        data[++top] = d;
    }
    T pop()
    {
        if (top == -1)
        {
            cout << "Stack is empty!" << endl;
            return NULL;
        }
        return data[top--];
    }
    T getTop()
    {
        if (top == -1)
        {
            cout << "Stack is empty!" << endl;
            return NULL;
        }
        return data[top];
    }
    bool isEmpty()
    {
        return top == -1;
    }
};
template<class T>
void delete_all(Stack<T>& s,  T& x)
{
    Stack<T> temp(s.maxsize);
    while (!s.isEmpty())
    {
        if (s.getTop() == x)
        {
            s.pop();
        }
        else
        {
            temp.push(s.pop());
        }
    }
    while (!temp.isEmpty())
    {
        s.push(temp.pop());
    }
}
#include <fstream>

int main()
{
    char x;
    char s;
    Stack<char> stack(100);
    ifstream input("input.txt");
        input >> x;
        input >> s;
        do{
            stack.push(s);
            input >> s;
        }while(s!='#');
        input.close();
    delete_all(stack, x);
    while (!stack.isEmpty())
    {
        cout << stack.pop();
    }
    cout << endl;
}