#include <iostream>
using namespace std;
template <class T>
class HashTable
{
public:
    HashTable(int size = 101);
    ~HashTable() { delete[] ht; }
    bool Search(const T &x) const;
    bool Insert(const T &x);
    bool Remove(const T &x);
private:
    int size;
    T *ht;
    int Hash(const T &x) const;
    bool* empty;
    float LoadFactor() const
    {
        int count = 0;
        for (int i = 0; i < size; i++)
            if (!empty[i])
                count++;
        return (float)count / size;
    }
};
template <class T>
HashTable<T>::HashTable(int size)
{
    this->size = size;
    ht = new T[size];
    for (int i = 0; i < size; i++)
        ht[i] = -1;
    empty = new bool[size];
    for (int i = 0; i < size; i++)
        empty[i] = true;
}
template <class T>
int HashTable<T>::Hash(const T &x) const
{
    return x % size;
}
template <class T>
bool HashTable<T>::Search(const T &x) const
{
    int initPos = Hash(x);
    int pos = initPos;
    do
    {
        if (ht[pos] == x && !empty[pos])
            return true;
        pos = (pos + 1) % size;
    } while (pos != initPos);
    return false;
}
template <class T>
bool HashTable<T>::Insert(const T &x)
{
    int initPos = Hash(x);
    int pos = initPos;
    do
    {
        if (empty[pos])
        {
            ht[pos] = x;
            empty[pos] = false;
            if(LoadFactor() > 0.6)
            {
                cout << "Rehashing..." << endl;
                int oldSize = size;
                size *= 2;
                T *oldHt = ht;
                ht = new T[size];
                for (int i = 0; i < size; i++)
                    ht[i] = -1;
                bool *oldEmpty = empty;
                empty = new bool[size];
                for (int i = 0; i < size; i++)
                    empty[i] = true;
                for (int i = 0; i < oldSize; i++)
                    if (!oldEmpty[i])
                        Insert(oldHt[i]);
                delete[] oldHt;
                delete[] oldEmpty;
            }
            return true;
        }
        pos = (pos + 1) % size;
    } while (pos != initPos);
    return false;
}
template <class T>
bool HashTable<T>::Remove(const T &x)
{
    int initPos = Hash(x);
    int pos = initPos;
    do
    {
        if (ht[pos] == x && !empty[pos])
        {
            empty[pos] = true;
            return true;
        }
        pos = (pos + 1) % size;
    } while (pos != initPos);
    return false;
}
int main()
{
    HashTable<int> ht(5);

    ht.Insert(1);
    ht.Insert(2);
    ht.Insert(3);
    ht.Insert(4);
    ht.Insert(5);
    ht.Insert(6);
    ht.Insert(7);
    ht.Insert(8);
    ht.Insert(9);
    ht.Insert(10);

    cout << ht.Search(1) << endl; 
    cout << ht.Search(5) << endl; 
    cout << ht.Search(10) << endl; 
    cout << ht.Search(11) << endl; 

    
    ht.Remove(1);
    ht.Remove(5);
    ht.Remove(10);

    cout << ht.Search(1) << endl; 
    cout << ht.Search(5) << endl; 
    cout << ht.Search(10) << endl; 

    return 0;
}