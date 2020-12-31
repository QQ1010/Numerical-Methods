#pragma once
#include <cstdio>
#include <stdint.h>
#include <cstdlib>
#include <iostream>

using namespace std;
class matrix
{
public:
    matrix() {}
    matrix(int32_t in_row,int32_t in_col)
    {
        row = in_row;
        col = in_col;
        data = new double*[row];
        for(int32_t i = 0 ; i < row ; i++)
        {
            data[i] = new double[col];
        }
    }
    void matrix_inputdata();
    void matrix_delete();
    void matrix_print();
    matrix& operator = (const matrix& rhs);
    matrix operator + (const matrix& rhs);
    matrix& operator += (const matrix& rhs) { return *this = *this + rhs; }
    matrix operator - (const matrix& rhs);
    matrix& operator -= (const matrix& rhs) { return *this = *this - rhs; }
    matrix operator * (const matrix& rhs);
    matrix matrix_transpose();
    matrix matrix_joint(const matrix& b);               //use when Ax = b ，put A and b to same matrix
private:
    int32_t row;
    int32_t col;
    double **data;
};