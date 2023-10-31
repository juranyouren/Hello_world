#include <iostream>

using namespace std;

template <typename T>
class LinkedMatrix;

template <typename T>
ostream& operator<<(ostream& os, const LinkedMatrix<T>& matrix);

template <typename T>
istream& operator>>(istream& is, LinkedMatrix<T>& matrix);

template <typename T>
class MatrixNode {
public:
    int row;
    int col;
    T value;
    MatrixNode* down;
    MatrixNode* left;
    MatrixNode(int r, int c, T val) : row(r), col(c), value(val), down(nullptr),left(nullptr) {}
};

template <typename T>
class LinkedMatrix {
    friend ostream& operator<< <T>(ostream& os, const LinkedMatrix<T>& matrix);
    friend istream& operator>> <T>(istream& is, LinkedMatrix<T>& matrix);

public:
    LinkedMatrix(int numRows, int numCols) : rows(numRows), cols(numCols), head(nullptr) {
        head = new MatrixNode<T>(0, 0, T());
    }
    LinkedMatrix() : rows(0), cols(0), head(nullptr) {
        head = new MatrixNode<T>(0, 0, T());
    }
    LinkedMatrix<T> operator=(LinkedMatrix<T>& a)
    {
        rows = a.rows;
        cols = a.cols;
        head = a.head;
        return *this;
    }
    ~LinkedMatrix() ;
    void store(int row, int col, int value)
    {
        if (value)
        {
            if (row > rows || row <= 0 || col > cols || col <= 0)
            {
                cout << "out of range" << endl;
                return;
            }
            MatrixNode<T>* cur = head;
            MatrixNode<T>* newnode = new MatrixNode<T>(row, col, value);
            bool f = 0;
            while (cur->down)
            {
                if (cur->row<row && cur->down->row>row)
                {
                    newnode->down = cur->down;
                    cur->down = newnode;
                }
                else if (cur->down->row == row)
                {
                    cur = cur->down;
                    if (cur->col == col)f = 1;
                    while (cur->left)
                    {
                        if (cur->col<col && cur->left->col>col)
                        {
                            newnode->left = cur->left;
                            cur->left = newnode;
                            f=1;
                            break;
                        }
                        else if (cur->left->col == col)f = 1;
                         cur = cur->left;
                    }
                    
                    if(!f) 
                    {
                        cur->left = newnode;
                        f=1;
                    }
                }
                else
                {
                    cur = cur->down;
                }

            }
            if(!f)cur->down = newnode;
        }
    }
    T get(int r,int c)
    {
        if (r > rows || r <= 0 || c > cols || c <= 0)
        {
            cout << "out of range" << endl;
            return -10000;
        }
        MatrixNode<T>* cur = head->down;
        while (cur)
        {
            if (cur->row == r)
            {
                while (cur)
                {
                    if (cur->col == c)
                    {
                        return cur->value;
                    }
                }
            }
            else
            {
                cur = cur->down;
            }
        }
        
        return 0;
    }
    LinkedMatrix<T>* operator+(LinkedMatrix<T>& b)
    {
        LinkedMatrix<T>* c=new LinkedMatrix<T>(this->rows, this->cols);
        MatrixNode<T>* cur = head->down;
        MatrixNode<T>* cur1 = b.head->down;
        while (cur && cur1)
        {
            if (cur->row == cur1->row)
            {
                MatrixNode<T>* temp = cur;
                MatrixNode<T>* temp1 = cur1;
                while (cur && cur1)
                {
                    if (cur->col == cur1->col)
                    {
                        c->store(cur->row, cur->col, cur->value + cur1->value);
                        cur = cur->left;
                        cur1 = cur1->left;
                    }
                    else if (cur->col < cur1->col)
                    {
                        c->store(cur->row, cur->col, cur->value);
                        cur = cur->left;
                    }
                    else
                    {
                        c->store(cur1->row, cur1->col, cur1->value);
                        cur1 = cur1->left;
                    
                    }
                }
                while(cur&&!cur1)
                {
                    c->store(cur->row, cur->col, cur->value);
                    cur=cur->left;
                }
                while(!cur&&cur1)
                {
                    c->store(cur1->row, cur1->col, cur1->value);
                    cur1=cur1->left;
                }
                cur = temp->down;
                cur1 = temp1->down;
            }
            else if (cur->row > cur1->row)
            {
                MatrixNode<T>* temp = cur1;
                while (temp)
                {
                    c->store(temp->row, temp->col, temp->value);
                    temp = temp->left;
                }
                cur1 = cur1->down;
            }
            else
            {
                MatrixNode<T>* temp = cur;
                while (temp)
                {
                    c->store(temp->row, temp->col, temp->value);
                    temp = temp->left;
                }
                cur = cur->down;
            }
        }
        while (!cur && cur1)
        {
            MatrixNode<T>* temp = cur1;
            while (temp)
            {
                c->store(temp->row, temp->col, temp->value);
                temp = temp->left;
            }
            cur1 = cur1->down;
        }
        while (!cur1 && cur)
        {
            MatrixNode<T>* temp = cur;
            while (temp)
            {
                c->store(temp->row, temp->col, temp->value);
                temp = temp->left;
            }
            cur = cur->down;
        }
        return c ;
    }
    LinkedMatrix<T>* operator-(LinkedMatrix<T>& b)
    {
        LinkedMatrix<T>* c = new LinkedMatrix<T>(this->rows, this->cols);
        MatrixNode<T>* cur = head->down;
        MatrixNode<T>* cur1 = b.head->down;
        while (cur && cur1)
        {
            if (cur->row == cur1->row)
            {
                MatrixNode<T>* temp = cur;
                MatrixNode<T>* temp1 = cur1;
                while (cur && cur1)
                {
                    if (cur->col == cur1->col)
                    {
                        c->store(cur->row, cur->col, cur->value - cur1->value);
                        cur = cur->left;
                        cur1 = cur1->left;
                    }
                    else if (cur->col < cur1->col)
                    {
                        c->store(cur->row, cur->col, cur->value);
                        cur = cur->left;
                    }
                    else
                    {
                        c->store(cur1->row, cur1->col, -cur1->value);
                        cur1 = cur1->left;

                    }
                }
                while(cur&&!cur1)
                {
                    c->store(cur->row, cur->col, cur->value);
                    cur=cur->left;
                }
                while(!cur&&cur1)
                {
                    c->store(cur1->row, cur1->col, -cur1->value);
                    cur1=cur1->left;
                }
                cur = temp->down;
                cur1 = temp1->down;
            }
            else if (cur->row > cur1->row)
            {
                MatrixNode<T>* temp = cur1;
                while (temp)
                {
                    c->store(temp->row, temp->col, -temp->value);
                    temp = temp->left;
                }
                cur1 = cur1->down;
            }
            else
            {
                MatrixNode<T>* temp = cur;
                while (temp)
                {
                    c->store(temp->row, temp->col, temp->value);
                    temp = temp->left;
                }
                cur = cur->down;
            }
        }
        while (!cur && cur1)
        {
            MatrixNode<T>* temp = cur1;
            while (temp)
            {
                c->store(temp->row, temp->col, -temp->value);
                temp = temp->left;
            }
            cur1 = cur1->down;
        }
        while (!cur1 && cur)
        {
            MatrixNode<T>* temp = cur;
            while (temp)
            {
                c->store(temp->row, temp->col, temp->value);
                temp = temp->left;
            }
            cur = cur->down;
        }
        return c;
    }
    LinkedMatrix<T> operator*(LinkedMatrix<T>& a)
    {
        //multiply
        LinkedMatrix<T>* c = new LinkedMatrix<T>(this->rows, a.cols);
        LinkedMatrix<T>* ta= a.transpose();
        MatrixNode<T>* cur = head->down;
        MatrixNode<T>* cur1=ta->head->down;
        while(cur)
        {
            cur1=ta->head->down;
            while(cur1)
            {
                int sum=0;
                
                MatrixNode<T>* temp=cur;
                MatrixNode<T>* temp1=cur1;
                while(temp&&temp1)
                {
                    if(temp->col==temp1->col)
                    {
                        sum+=temp->value*temp1->value;
                        temp=temp->left;
                        temp1=temp1->left;
                    }
                    else if(temp->col<temp1->col)
                    {
                        temp=temp->left;
                    }
                    else
                    {
                        temp1=temp1->left;
                    }
                }
                if(sum)
                {
              c->store(cur->row,cur1->row,sum);  
                 }
                cur1=cur1->down;
            }
            
            cur=cur->down;
        }
       
        return *c; 

    }
    
    LinkedMatrix<T>* transpose() 
    {
        LinkedMatrix<T>* c = new LinkedMatrix<T>(this->cols, this->rows);
        MatrixNode<T>* cur = head->down;
        while (cur)
        {
            MatrixNode<T>* temp = cur;
            while (temp)
            {
                c->store(temp->col, temp->row, temp->value);
                temp = temp->left;
            }
            cur = cur->down;
        }
        return c;
    }
private:
    int rows;
    int cols;
    MatrixNode<T>* head;
};

template <typename T>
ostream& operator<<(ostream& os, const LinkedMatrix<T>& matrix) 
{
    MatrixNode<T>* cur = matrix.head->down;
    while (cur)
    {
        cout << "(" << cur->row << "," << cur->col << ")" << "=" << cur->value<<endl;
        MatrixNode<T>* temp = cur->left;
        while (temp)
        {
            cout << "(" << temp->row << "," << temp->col << ")" << "=" << temp->value << endl;
            temp = temp->left;
        }
        cur = cur->down;
        delete temp;
    }
    delete cur;
    return os;
}

template <typename T>
istream& operator>>(istream& is, LinkedMatrix<T>& matrix) 
{
    int numRows, numCols, numTerms;

    cout << "Enter the number of rows: ";
    is >> numRows; matrix.rows = numRows;
    cout << "Enter the number of columns: ";
    is >> numCols; matrix.cols = numCols;
    cout << "Enter the total number of terms: ";
    is >> numTerms;
    cout << "Enter the non-zero matrix elements in the format 'row column value':" << endl;

    for (int i = 0; i < numTerms; i++)
    {
        int row, col;
        T value;
        cout << "Term " << (i + 1) << ": ";
        is >> row >> col >> value;
        matrix.store(row, col, value);
       
    }
    return is;
}
template <typename T>
LinkedMatrix<T>::~LinkedMatrix() 
{
    MatrixNode<T>* current = head;
    while (current != nullptr) 
    {
        MatrixNode<T>* temp = current;
        current = current->down;
        MatrixNode<T>* rowCurrent = temp->left;
        while (rowCurrent != nullptr) 
        {
            MatrixNode<T>* rowTemp = rowCurrent;
            rowCurrent = rowCurrent->left;
            delete rowTemp;
        }
        delete temp;
    }
    head = nullptr;
}
int test31() {
    LinkedMatrix<int> matrix;
    cin >> matrix;
    matrix.store(1, 1, 1);
    cout << matrix << endl;
    cout << matrix.get(1, 1);
    return 0;
}
void test32()
{
    LinkedMatrix<int> a;
    LinkedMatrix<int> b;
    LinkedMatrix<int>* c;
    cin >> a>>b;
    c = a + b;
    cout << *c;
    c=  a-b;
    cout << *c;
}
void test33()
{
    LinkedMatrix<int> m1(2, 3);
    m1.store(1, 1, 1);
    m1.store(1, 2, 2);
    m1.store(1, 3, 3);
    m1.store(2, 1, 4);
    m1.store(2, 2, 5);
    m1.store(2, 3, 6);
    cout<<m1;
    LinkedMatrix<int> m2(3, 2);
    m2.store(1, 1, 7);
    m2.store(1, 2, 8);
    m2.store(2, 1, 9);
    m2.store(2, 2, 10);
    m2.store(3, 1, 11);
    m2.store(3, 2, 12);
    LinkedMatrix<int> m3 = m1 * m2;

    LinkedMatrix<int> expected(2, 2);
    expected.store(1, 1, 58);
    expected.store(1, 2, 64);
    expected.store(2, 1, 139);
    expected.store(2, 2, 154);
    cout<<"result:"<<endl;
    cout<<m3;
    cout<<"expected:"<<endl;
    cout<<expected;
    
}

int main()
{
    test32();
    return 0;
}
