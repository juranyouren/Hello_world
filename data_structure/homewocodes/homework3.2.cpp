#include<iostream>
#include<exception>
#include<string>
using namespace std;

class NoMem : public exception {
private:
    string message;
public:
    NoMem(const string& msg = "WRONG") : message(msg) {}
    virtual const char* what() const throw() {
        return message.c_str();
    }
};
class BadInitializers : public exception {
private:
    string message;
public:
    BadInitializers(const string& msg = "WRONG") : message(msg) {}
    virtual const char* what() const throw() 
    {
        return message.c_str();
    }
};

template<class T>
class SparseMatrix;

template<class U>
class Term
{
        template<typename V>
        friend void mul(SparseMatrix<V>& a, SparseMatrix<V>& b, SparseMatrix<V>& c);
        template<typename V>
        friend ostream& operator<<(ostream&, const SparseMatrix<V>&);
        template<typename V>
        friend istream& operator>>(istream&, SparseMatrix<V>&);
        friend class SparseMatrix<U>;
    private:
        int col;
        int row;
        U value;
    public:
        Term(int r, int c, U d) { col = c; row = r; value = d; }
        Term() { col = 0, row = 0, value = 0; };
};

template<class T>
class SparseMatrix
{
            template<class U>
            friend void mul(SparseMatrix<U>& a, SparseMatrix<U>& b, SparseMatrix<U>& c);
            friend class Term<T>;
            template<class U>
            friend ostream& operator<<(ostream&, const SparseMatrix<U>&);
            template<class U>
            friend istream& operator>>(istream&, SparseMatrix<U>&);
        public:
            SparseMatrix(int maxTerms = 10);
            SparseMatrix(int c, int r, int terms = 0) {
                cols = c;
                rows = r;
                this->terms = terms;
                MaxTerms = 10;
            }
    void set(int c, int r, int terms = 0)
    {
        cols = c;
        rows = r;
        this->terms = terms;
    }
    ~SparseMatrix() { delete[] t; }
    void Transpose(SparseMatrix<T>& b) const;
    void Add(const SparseMatrix<T>& b, SparseMatrix<T>& c) const;
private:
    void Append(const Term<T>& t);
    int rows, cols;
    int terms;
    Term<T>* t;
    int MaxTerms;
};

template<class T>
void SparseMatrix<T>::Transpose(SparseMatrix<T>& b) const
{

    if (terms > b.MaxTerms) throw NoMem();
    b.cols = rows;
    b.rows = cols;
    b.terms = terms;

    int* ColSize, * RowNext;
    ColSize = new int[cols + 1];
    RowNext = new int[cols + 1];
    for (int i = 1; i <= cols; i++)
        ColSize[i] = 0;
    for (int i = 0; i < terms; i++)
        ColSize[t[i].col]++;
    RowNext[1] = 0;
    for (int i = 2; i <= cols; i++)
        RowNext[i] = RowNext[i - 1] + ColSize[i - 1];
    for (int i = 0; i < terms; i++)
    {
        int j = RowNext[t[i].col]++;
        b.t[j].row = t[i].col;
        b.t[j].col = t[i].row;
        b.t[j].value = t[i].value;
    }
}

template<class T>
void SparseMatrix<T>::Append(const Term<T>& m)
{
    if (terms >= MaxTerms) throw NoMem();
    t[terms] = m;
    terms++;
}

template<class T>
SparseMatrix<T>::SparseMatrix(int maxTerms)
{
    if (maxTerms < 1) throw BadInitializers();
    MaxTerms = maxTerms;
    t = new Term<T>[MaxTerms];
    terms = rows = cols = 0;
}

template <class T>
ostream& operator<<(ostream& out, const SparseMatrix<T>& x)
{
    out << "rows = " << x.rows << " columns = "
        << x.cols << endl;
    out << "nonzero terms = " << x.terms << endl;

    for (int i = 0; i < x.terms; i++)
        out << "a(" << x.t[i].row << ',' << x.t[i].col
        << ") = " << x.t[i].value << endl;
    return out;
}

template<class T>
istream& operator>>(istream& in, SparseMatrix<T>& x)
{
    cout << "Enter number of rows, columns, and terms"
        << endl;
    in >> x.rows >> x.cols >> x.terms;
    if (x.terms > x.MaxTerms) throw NoMem();

    for (int i = 0; i < x.terms; i++)
    {
cout << "Enter row, column, and value of term "
            << (i + 1) << endl;
        in >> x.t[i].row >> x.t[i].col >> x.t[i].value;
    }
    return in;
}

template<class T>
void mul(SparseMatrix<T>& a, SparseMatrix<T>& b, SparseMatrix<T>& c)
{
    if (a.cols != b.rows || a.rows != b.cols) throw("WRONG");
    SparseMatrix<int> b1;
    b.Transpose(b1);
    c.set(a.rows, b1.rows);
    int* arr = new int[a.rows + 1];
    for (int i = 0; i < a.cols + 1; i++)
        arr[i] = 0;
    for (int m = 0; m < a.terms; m++)
    {
        for (int n = 0; n < b1.terms; n++)
        {
            if (a.t[m].col == b1.t[n].col)
                arr[b1.t[n].row] += (a.t[m].value) * (b1.t[n].value);
        }
        if (m == a.terms - 1)
        {
            for (int i = 0; i < a.cols + 1; i++)
            {
                if (arr[i])
                {
                    Term<T> tm(a.t[m].row, i, arr[i]);
                    c.Append(tm);
                }
            }
        }
        else
        {

            if (a.t[m].row != a.t[m + 1].row)
            {
                for (int i = 0; i < a.cols + 1; i++)
                {
                    if (arr[i])
                    {
                        Term<T> tm(a.t[m].row, i, arr[i]);
                        c.Append(tm);
                    }
                }
            }
            for (int i = 0; i < a.cols + 1; i++)
                arr[i] = 0;
        }
    }
}

void test11()
{
    SparseMatrix<int> a;
    SparseMatrix<int> b;
    SparseMatrix<int> c;
    cin >> a >> b;
    mul<int>(a, b, c);
    cout << c;
}

int main()
{
   test11();
   return 0;
}