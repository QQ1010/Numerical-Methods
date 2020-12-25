#pragma once
#include <cstdio>
#include <stdint.h>
#include <cstdlib>

using namespace std;
class matrix
{
public:
    matrix() {}
    matrix(int32_t inrow,int32_t incol)
    {
        row = inrow;
        col = incol;
        data = new double*[row];
        for(int32_t i = 0 ; i < row ; i++)
        {
            data[i] = new double[col];
        }
    }
    void matrix_delete();
private:
    int32_t row;
    int32_t col;
    double **data;
};