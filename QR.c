#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>


double **matrix_calloc(int32_t row,int32_t col)
{
    double ** matrix = (double **)calloc(row,sizeof(double *));
    for(int32_t i = 0 ; i < row ; i++)
    {
        matrix[i] = (double *)calloc(col,sizeof(double));
    }
    return matrix;
}
void matrix_free(int32_t row,int32_t col,double ** matrix)
{
    for(int32_t i = 0 ; i < row ; i++)
    {
        free(*matrix);
    }
    free(matrix);
}
double **matrix_mult(int32_t row_a,int32_t col_a,double **matrixa,int32_t row_b,int32_t col_b,double **matrixb)
{
    double **result;
    result = matrix_calloc(row_a,col_b);
    if(col_a != row_b)
    {
        printf("These two matrix cannot mult.\n");
    }
    else
    {
        for(int32_t i = 0 ; i < row_a ; i++)
        {
            for(int32_t j = 0 ; j < col_b ; j++)
            {
                double sum = 0;
                for(int32_t k = 0 ; k < row_b ; k++)
                {
                    sum += matrixa[i][k]*matrixb[k][j];

                }
                result[i][j] = sum;
            }
        }
    }
        return result;
}
double **matrix_tranpose(int row,int col,double **matrix)
{
    double **result;
    result = matrix_calloc(col,row);
    double tmp = 0;
    for(int32_t i = 0 ; i < row ; i++)
    {
        for(int32_t j = 0 ; j < col ; j++)
        {
            if(i != j)
            {
                result[j][i] = matrix[i][j];
            }
            else
            {
                result[i][j] = matrix[i][j];
            }
            
        }
    }
    return result;
}

double **input(double **matrix)    //you need to change here
{
    matrix[0][0] = 1;
    matrix[0][1] = -4;
    matrix[1][0] = 2;
    matrix[1][1] = 3;
    matrix[2][0] = 2;
    matrix[2][1] = 2;
    return matrix;
}


int main()
{
    int32_t row,col;
    printf("please enter row and col:(row col)");
    scanf("%d %d",&row,&col);
    double **matrix;
    matrix = matrix_calloc(row,col);
    input(matrix);
    double **Qmatrix;
    Qmatrix = matrix_calloc(row,col);
    double **Rmatrix;
    Rmatrix = matrix_calloc(col,col);
    for(int32_t i = 0 ; i < col ; i++)
    {
        if(i == 0)
        {
            double len = 0;
            for(int32_t j = 0 ; j < row ; j++)
            {
                len += matrix[j][i]*matrix[j][i];
            }
            len = pow(len,1.0/2.0);
            Rmatrix[i][i] = len;
            for(int32_t j = 0 ; j < row ; j++)
            {
                Qmatrix[j][i] = matrix[j][i]/len;
            }
        }
        else
        {
            double len = 0;
            for(int32_t j = 0 ; j < i ; j++)
            {
                double r = 0;
                for(int32_t k = 0 ; k < row ; k++)
                {
                    r += Qmatrix[k][j]*matrix[k][i];
                }
                Rmatrix[j][i] = r;
                for(int32_t k = 0 ; k < row ; k++)
                {
                    matrix[k][i] -= Qmatrix[k][j]*r;
                }
            }
            for(int32_t k = 0 ; k < row ; k++)
            {
                len += matrix[k][i]*matrix[k][i];
            }
            len = pow(len,1.0/2.0);
            Rmatrix[i][i] = len;
            for(int32_t j = 0 ; j < row ; j++)
            {
                Qmatrix[j][i] = matrix[j][i]/len;
            }
        }
    }
    printf("Q matrix:\n");
    for(int32_t i = 0 ; i < row ; i++)
    {
        for(int32_t j = 0 ; j < col ; j++)
        {
            printf("%.4lf ",Qmatrix[i][j]);
        }
        printf("\n");
    }
    printf("R matrix:\n");
    for(int32_t i = 0 ; i < row ; i++)
    {
        for(int32_t j = 0 ; j < col ; j++)
        {
            printf("%.4lf ",Rmatrix[i][j]);
        }
        printf("\n");
    }
    free(matrix);
    free(Qmatrix);
    free(Rmatrix);
}