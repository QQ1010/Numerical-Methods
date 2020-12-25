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

double **Rmatrix(double x,double y)      //you need to change here
{
    double r1x,r1y,r2x,r2y,r3x,r3y,rad1,rad2,rad3;
    r1x = -1;
    r1y = 0;
    r2x = 1;
    r2y = 1;
    r3x = 1;
    r3y = -1;
    rad1 = 1;
    rad2 = 1;
    rad3 = 1;
    double **matrix = matrix_calloc(3,1);
    matrix[0][0] = pow(((x-(r1x))*(x-(r1x)) + (y-(r1y))*(y-(r1y))),1.0/2.0)-rad1;
    matrix[1][0] = pow(((x-(r2x))*(x-(r2x)) + (y-(r2y))*(y-(r2y))),1.0/2.0)-rad2;
    matrix[2][0] = pow(((x-(r3x))*(x-(r3x)) + (y-(r3y))*(y-(r3y))),1.0/2.0)-rad3;
    // printf("%lf %lf %lf\n",matrix[0][0],matrix[1][0],matrix[2][0]);
    return matrix;
}

double **D_rmatrix(double x,double y)   //you need to change here
{
    double r1x,r1y,r2x,r2y,r3x,r3y,rad1,rad2,rad3;
    r1x = -1;
    r1y = 0;
    r2x = 1;
    r2y = 1;
    r3x = 1;
    r3y = -1;
    rad1 = 1;
    rad2 = 1;
    rad3 = 1;
    double **matrix = matrix_calloc(3,2);
    matrix[0][0] = (x-(r1x))/pow(((x-(r1x))*(x-(r1x)) + (y-(r1y))*(y-(r1y))),1.0/2.0);
    matrix[0][1] = (y-(r1y))/pow(((x-(r1x))*(x-(r1x)) + (y-(r1y))*(y-(r1y))),1.0/2.0);
    matrix[1][0] = (x-(r2x))/pow(((x-(r2x))*(x-(r2x)) + (y-(r2y))*(y-(r2y))),1.0/2.0);
    matrix[1][1] = (y-(r2y))/pow(((x-(r2x))*(x-(r2x)) + (y-(r2y))*(y-(r2y))),1.0/2.0);
    matrix[2][0] = (x-(r3x))/pow(((x-(r3x))*(x-(r3x)) + (y-(r3y))*(y-(r3y))),1.0/2.0);
    matrix[2][1] = (y-(r3y))/pow(((x-(r3x))*(x-(r3x)) + (y-(r3y))*(y-(r3y))),1.0/2.0);
    // printf("%lf %lf \n%lf %lf\n%lf %lf\n",matrix[0][0],matrix[0][1],matrix[1][0],matrix[1][1],matrix[2][0],matrix[2][1]);
    return matrix;
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

double **Gauss(int32_t a_row,int32_t a_col,double **a_matrix,int32_t b_row,int32_t b_col,double **b_matrix)
{
    int32_t row = a_row;
    int32_t col = a_col + b_col;
    double**matrix = matrix_calloc(row,col);
    for(int32_t i = 0 ; i < row ; i++)
    {
        for(int32_t j = 0 ; j < col ; j++)
        {
            if(j != col-1)
            {
                matrix[i][j] = a_matrix[i][j];
            }
            if(j == col-1)
            {
                matrix[i][j] = b_matrix[i][0];
            }
        }
    }
    double mult = 0;
    for(int32_t j = 0 ; j < col ; j++)
    {
        for(int32_t i = j+1 ; i < row ; i++)
        {
            mult = matrix[i][j] / matrix[j][j];
            mult *= -1;
            for(int32_t k = 0 ; k < col ; k++)
            {
                matrix[i][k] += matrix[j][k]*mult;
            }
        }
    }
    for(int32_t i = row-1 ; i >= 0 ; i--)
    {
        for(int32_t j = i-1 ; j >=0 ; j--)
        {
            mult = matrix[j][i]/matrix[i][i];
            mult *= -1;
            for(int32_t k = 0 ; k < col ; k++)
            {
                matrix[j][k] += matrix[i][k]*mult;
            }
        }
    }
    for(int32_t i = 0 ; i < row ; i++)
    {
        if(matrix[i][i] != 1)
        {
            matrix[i][col-1] /= matrix[i][i];
            matrix[i][i] = 1;
        }
    }
    double **ans = matrix_calloc(row,1);
    for(int32_t i = 0 ; i < row ; i++)
    {
        ans[i][0] = matrix[i][col-1];
    }
    return ans;
}

int main()
{
    double x,y;
    printf("please enter (x_0 y_0):");
    scanf("%lf %lf",&x,&y);
    int32_t r_row = 3;                        //need to change
    int32_t r_col = 1;
    int32_t d_row = 3;
    int32_t d_col = 2;
    int32_t dt_row = 2;
    int32_t dt_col = 3;
    double **r_matrix;
    double **d_rmatrix;
    double **d_rTmatrix;
    double **a_matrix = matrix_calloc(dt_row,d_col);
    double **x_matrix = matrix_calloc(dt_row,r_col);
    double **b_matrix = matrix_calloc(dt_row,r_col);
    //Ax=b solve x
    int32_t k = 0;
    while(k != 20)
    {
        k++;
        r_matrix = Rmatrix(x,y);
        d_rmatrix = D_rmatrix(x,y);
        d_rTmatrix = matrix_tranpose(d_row,d_col,d_rmatrix);
        a_matrix = matrix_mult(dt_row,dt_col,d_rTmatrix,d_row,d_col,d_rmatrix);
        b_matrix = matrix_mult(dt_row,dt_col,d_rTmatrix,r_row,r_col,r_matrix);
        for(int32_t i = 0 ; i < dt_row ; i++)
        {
            for(int32_t j = 0 ; j < r_col ; j++)
            {
                b_matrix[i][j] *= -1;
            }
        }
        x_matrix = Gauss(dt_row,d_col,a_matrix,dt_row,r_col,b_matrix);
        // printf("%lf %lf\n",x,y);
        x += x_matrix[0][0];
        y += x_matrix[1][0];
    }
    printf("--- ans ---\n");
    printf("x = %lf , y = %lf\n",x,y);
    matrix_free(r_row,r_col,r_matrix);
    matrix_free(d_row,d_col,d_rmatrix);
    matrix_free(dt_row,dt_col,d_rTmatrix);
    matrix_free(dt_row,d_col,a_matrix);
    matrix_free(dt_row,r_col,b_matrix);
    matrix_free(dt_row,r_col,x_matrix);
}