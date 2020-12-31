#include "matrix.h"

void matrix::matrix_delete()
{
    for(int32_t i = 0 ; i < row ; i++)
    {
        delete data[i];
    }
    delete data;
}

void matrix::matrix_print()
{
    cout << "============= matrix =============" << endl;
    for(int32_t i = 0 ; i < row ; i++)
    {
        for(int32_t j = 0 ; j < col ; j++)
        {
            cout << data[i][j] << " ";
        }
        cout << endl;
    }
}
void matrix::matrix_inputdata()
{
    for(int32_t i = 0 ; i < row ; i++)
    {
        for(int32_t j = 0 ; j < col ; j++)
        {
            cout << "please enter data[" << i << "][" << j << "]: ";
            cin >> data[i][j];
        }
    }
}

matrix& matrix::operator = (const matrix& rhs)
{
    this->matrix_delete();
    row = rhs.row;
    col = rhs.col;
    data = new double*[row];
    for(int32_t i = 0 ; i < row ; i++)
    {
        data[i] = new double[col];
    }
    for(int32_t i = 0 ; i < rhs.row ; i++)
    {
        for(int32_t j = 0 ; j < rhs.col ; j++)
        {
            data[i][j] = rhs.data[i][j];
        }
    }
    return *this;
}
matrix matrix::operator + (const matrix& rhs)
{
    if(rhs.row != row || rhs.col != col)
    {
        cout << "This two matrix cannot add." << endl;
    }
    else
    {
        matrix tmp(row, col);
        for(int32_t i = 0 ; i < row ; i++)
        {
            for(int32_t j = 0 ; j < col ; j++)
            {
                tmp.data[i][j] = rhs.data[i][j] + data[i][j];
            }
        }
        return tmp;
    }
}
matrix matrix::operator - (const matrix& rhs)
{
    if(rhs.row != row || rhs.col != col)
    {
        cout << "This two matrix cannot sub." << endl;
    }
    else
    {
        matrix tmp(row,col);
        for(int32_t i = 0 ; i < row ; i++)
        {
            for(int32_t j = 0 ; j < col ; j++)
            {
                tmp.data[i][j] = data[i][j] - rhs.data[i][j];
            }
        }
        return tmp;
    }
    
}
matrix matrix::operator * (const matrix& rhs)
{
    if(col != rhs.row)
    {
        cout << "This two matrix cannot mult." << endl;
    }
    else
    {
        matrix tmp(row,rhs.col);
        for(int32_t i = 0 ; i < row ; i++)
        {
            for(int32_t j = 0 ; j < rhs.col ; j++)
            {
                double sum = 0;
                for(int32_t k = 0 ; k < rhs.row ; k++)
                {
                    sum += data[i][k]*rhs.data[k][j];
                }
                tmp.data[i][j] = sum;
            } 
        }
        return tmp;
    }
}

matrix matrix::matrix_transpose()
{
    matrix result(col,row);
    for(int32_t i = 0 ; i < row ; i++)
    {
        for(int32_t j = 0 ; j < col ; j++)
        {
            if(i != j)
            {
                result.data[j][i] = data[i][j];
            }
            else
            {
                result.data[i][j] = data[i][j];
            }
            
        }
    }
    return result;
}

matrix matrix::matrix_joint(const matrix& b)
{
    matrix result(row,col+b.col);
    if(row != b.row)
    {
        cout << "This two matrix cannot joint." << endl;
    }
    else
    {
        for(int32_t i = 0 ; i < row ; i++)
        {
            for(int32_t j = 0 ;  j < col+b.col ; j++)
            {
                if(j < col)
                {
                    result.data[i][j] = data[i][j];
                }
                else if(j >= col && j < col+b.col)
                {
                    result.data[i][j] = b.data[i][j-col];
                }
            }
        }
        return result;
    }
}