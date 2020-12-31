#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#define PI 3.14159265

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

double **Amatrix_input(int32_t row,int32_t col)   //you need to change here
{
    double **matrix;
    for(int32_t i = 0 ; i < row ; i++)
    {
        matrix[i][0] = 1;
        matrix[i][1] = cos(2*PI*i/12);
        matrix[i][2] = sin(2*PI*i/12);
        matrix[i][3] = cos(4*PI*i/12);
    }
    return matrix;
}
double **bmatrix_input(int row,int col)  //you need to change here
{
    double **matrix;
    matrix = matrix_calloc(row,col);
    matrix[0][0] = 6.224;
    matrix[1][0] = 6.665;
    matrix[2][0] = 6.241;
    matrix[3][0] = 5.302;
    matrix[4][0] = 5.073;
    matrix[5][0] = 5.127;
    matrix[6][0] = 4.994;
    matrix[7][0] = 5.012;
    matrix[8][0] = 5.108;
    matrix[9][0] = 5.377;
    matrix[10][0] = 5.510;
    matrix[11][0] = 6.372;
    return matrix;
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

double **D_inverse(int32_t row,int32_t col,double **matrix)
{
    for(int32_t i = 0 ; i < row ; i++)
    {
        for(int32_t j = 0 ; j < col ; j++)
        {
            if(j == i)
            {
                matrix[i][j] = 1/matrix[i][j];
            }
        }
    }
    return matrix;
}

int main()
{
    int32_t row,col;
    printf("please enter the row and col of matrix A:");    //A_T*A(x) = A_T*b
    scanf("%d %d",&row,&col);
    double **A_matrix;
    A_matrix = matrix_calloc(row,col);
    A_matrix = Amatrix_input(row,col);
    int32_t row_b,col_b;
    printf("please enter the row and col of matrix b:");
    scanf("%d %d",&row_b,&col_b);
    double **b_matrix;
    b_matrix = matrix_calloc(row_b,col_b);
    b_matrix = bmatrix_input(row_b,col_b);
    double **Tmatrix;
    int32_t T_row = col;
    int32_t T_col = row;
    Tmatrix = matrix_calloc(T_row,T_col);
    Tmatrix = matrix_tranpose(row,col,A_matrix);
    double **TA_matrix;
    TA_matrix = matrix_calloc(T_row,col);
    TA_matrix = matrix_mult(T_row,T_col,Tmatrix,row,col,A_matrix);
    double **Tb_matrix;
    Tb_matrix = matrix_calloc(T_row,col_b);
    Tb_matrix = matrix_mult(T_row,T_col,Tmatrix,row_b,col_b,b_matrix);
    double **Dmatrix;
    Dmatrix = matrix_calloc(T_row,col);
    for(int32_t i = 0 ; i < T_row ; i ++)
    {
        for(int32_t j = 0 ; j < col ; j ++)
        {
            if(i == j)
            {
                Dmatrix[i][j] = 1/TA_matrix[i][j];
                TA_matrix[i][j] = 0;
            }
        }
    }
    double **ans;   //initial vector
    int32_t ans_row = col;
    int32_t ans_col = col_b;
    ans = matrix_calloc(ans_row,ans_col);
    int32_t k = 0;
    double **buffer;
    while(k != 10)
    {
        buffer = matrix_mult(T_row,col,TA_matrix,ans_row,ans_col,ans);    //(L+U)*x_k
        for(int32_t j = 0 ; j < ans_row ; j++)
        {
            for(int32_t i = 0 ; i < ans_col ; i++)   //buffer = b-(L+U)*x_k
            {
                buffer[j][i] = Tb_matrix[j][i] - buffer[j][i];
            }
        }
        k += 1;
        ans = matrix_mult(T_row,col,Dmatrix,ans_row,ans_col,buffer);  //x_k+1 = D^-1 * (b-(L+U)*x_k)   
    }
    for(int32_t i = 0 ; i < ans_row ; i++)
    {
        printf("c%d = %.4lf\n",i,ans[i][0]);
    }
    //count rmse
    double **bcount;
    bcount = matrix_calloc(row,ans_col);
    bcount = matrix_mult(row,col,A_matrix,ans_row,ans_col,ans);
    double **r;
    int32_t r_row = row;
    int32_t r_col = ans_col;
    r = matrix_calloc(r_row,r_col);
    for(int32_t i = 0 ; i < r_row ; i++)
    {
        for(int32_t j = 0 ; j < r_col ; j++)
        {
            r[i][j] = (b_matrix[i][j] - bcount[i][j]);
        }
    }
    double rmse = 0;
    double tmp = 0;
    for(int32_t i = 0 ; i < r_row ; i++)
    {
        tmp += (r[i][0])*(r[i][0]);
    }
    rmse = pow((tmp/r_row),1.0/2.0);
    printf("rmse = %lf\n",rmse);
}