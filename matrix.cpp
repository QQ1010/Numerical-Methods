#include "matrix.h"

void matrix::matrix_delete()
{
    for(int32_t i = 0 ; i < row ; i++)
    {
        delete data[i];
    }
    delete data;
}