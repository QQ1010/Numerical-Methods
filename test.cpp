#include "matrix.h"
#include <iostream>
using namespace std;

// class num{
//     int v;
// public:
//     num() {}
//     num(int val): v(val) {}
//     num& operator = (const num& rhs) { v = rhs.v; return *this; }
//     num& operator + (const num& rhs) { v = v + rhs.v; return *this; }
//     void print() { cout << v; }
// };

int main()
{
    int32_t row = 2;
    int32_t col = 2;
    matrix test(row,col);
    matrix A(row,col);
    test.matrix_inputdata();
    A.matrix_inputdata();
    test.matrix_print();
    A.matrix_print();
    test = test * A;
    test.matrix_print();
    A -= test;
    A.matrix_print();
    A.matrix_transpose();
    matrix AT(col,row);
    AT = A.matrix_transpose();
    AT.matrix_print();
    matrix result(row,2*col);
    result = A.matrix_joint(test);
    result.matrix_print();
    A.matrix_delete();
    test.matrix_delete();

    // num a(1), b(2), c, d(4);
    // // int a = 1,b = 2,c,d = 4;
    // c = a + b;
    // c = c + d;
    // // cout << c << endl;
    // // cout << a << endl;
    // c.print();
    // a.print();
}