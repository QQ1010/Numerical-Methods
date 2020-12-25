#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

//Jacobi
//matrix solution

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
        // printf("row_a=%d col_b=%d row_b=%d\n",row_a,col_b,row_b);
        for(int32_t i = 0 ; i < row_a ; i++)
        {
            // printf("hi1\n");
            for(int32_t j = 0 ; j < col_b ; j++)
            {
                // printf("hi2\n");
                double sum = 0;
                // printf("hi3\n");
                for(int32_t k = 0 ; k < row_b ; k++)
                {
                    // printf("hi4\n");
                    sum += matrixa[i][k]*matrixb[k][j];
                    // printf("sum = %.2lf\n",sum);

                }
                // printf("hi5\n");
                result[i][j] = sum;
                // printf("hi6\n");
                // printf("row_a = %d col_b = %d dest[%d][%d] = %.lf \n",row_a,col_b,i,j,result[i][j]);
            }
        }
    }
    // printf("multresult\n");
    // for(int32_t i = 0 ; i < row_a ; i++)
    // {
    //     for(int32_t j = 0 ; j < col_b ; j++)
    //     {
    //         printf("%.2lf ",result[i][j]);
    //     }
    //     printf("\n");
    // }
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
    printf("please enter the row of square matrix:");      //Ax = b ,A is a square matrix
    scanf("%d",&row);
    printf("please enter the col of square matrix:");
    scanf("%d",&col);
    double **matrix;
    matrix = matrix_calloc(row,col);
    printf("please enter the matrix:\n");
    for(int32_t i = 0 ; i < row ; i++)
    {
        for(int32_t j = 0 ; j < col ; j++)
        {
            scanf("%lf",&matrix[i][j]);
        }
    }
    printf("please enter the b matrix:");
    double **b;
    int32_t tmp = 1;
    b = matrix_calloc(row,tmp);
    for(int32_t i = 0 ; i < row ; i++)
    {
        for(int32_t j = 0 ; j < tmp ; j++)
        {
            scanf("%lf",&b[i][j]);
        }
    }
    // printf("b matrix:\n");
    // for(int32_t i = 0 ; i < row ; i++)
    // {
    //     for(int32_t j = 0 ; j < tmp ; j++)
    //     {
    //         printf("%.lf",b[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("matrix\n");
    // for(int32_t i = 0 ; i < row ; i++)
    // {
    //     for(int32_t j = 0 ; j < col ; j++)
    //     {
    //         printf("%.lf ",matrix[i][j]);
    //     }
    //     printf("\n");
    // }
    double **Dmatrix;
    Dmatrix = matrix_calloc(row,col);
    for(int32_t i = 0 ; i < row ; i ++)
    {
        for(int32_t j = 0 ; j < col ; j ++)
        {
            if(i == j)
            {
                Dmatrix[i][j] = 1/matrix[i][j];
                matrix[i][j] = 0;
            }
            // printf("%.2lf ",Dmatrix[i][j]);
        }
        // printf("\n");
    }
    // printf("L+U\n");
    // for(int32_t i = 0 ; i < row ; i++)
    // {
    //     for(int32_t j = 0 ; j < col ; j++)
    //     {
    //         printf("%.lf ",matrix[i][j]);
    //     }
    //     printf("\n");
    // }
    // printf("Dmatrix inverse:\n");
    // for(int32_t i = 0 ; i < row ; i++)
    // {
    //     for(int32_t j = 0 ; j < col ; j++)
    //     {
    //         printf("%.2lf ",Dmatrix[i][j]);
    //     }
    //     printf("\n");
    // }
    double **ans;   //initial vector
    ans = matrix_calloc(row,tmp);
    // for(int32_t i = 0 ; i < row ; i++)
    // {
    //     for(int32_t j = 0 ; j < tmp ; j++)
    //     {
    //         printf("i=%d j=%d\n",i,j);
    //         printf("%d ",ans[i][j]);
    //     }
    //     printf("\n");
    // }
    int32_t k = 0;
    double **buffer;
    while(k != 4)
    {
        // printf("k =%d \n",k);
        buffer = matrix_mult(row,col,matrix,row,tmp,ans);    //(L+U)*x_k
        for(int32_t j = 0 ; j < row ; j++)
        {
            for(int32_t i = 0 ; i < tmp ; i++)   //buffer = b-(L+U)*x_k
            {
                buffer[j][i] = b[j][i] - buffer[j][i];
            }
        }
        // printf("b-(L+U)*x_k\n");
        // for(int32_t i = 0 ; i < row ; i++)
        // {
        //     for(int32_t j = 0 ; j < tmp ; j++)
        //     {
        //         printf("%.2lf ",buffer[i][j]);
        //     }
        //     printf("\n");
        // }
        k += 1;
        ans = matrix_mult(row,col,Dmatrix,row,tmp,buffer);  //x_k+1 = D^-1 * (b-(L+U)*x_k)   
    }
    for(int32_t i = 0 ; i < row ; i++)
    {
        printf("x%d = %.4lf\n",i,ans[i][0]);
    }
    matrix_free(row,col,matrix);
    matrix_free(row,col,b);
    matrix_free(row,col,Dmatrix);
    matrix_free(row,col,buffer);
    matrix_free(row,col,ans);
}


/*
3 -1 0 0 0 0 0 0 0 0
-1 3 -1 0 0 0 0 0 0 0
0 -1 3 -1 0 0 0 0 0 0
0 0 -1 3 -1 0 0 0 0 0
0 0 0 -1 3 -1 0 0 0 0
0 0 0 0 -1 3 -1 0 0 0
0 0 0 0 0 -1 3 -1 0 0
0 0 0 0 0 0 -1 3 -1 0
0 0 0 0 0 0 0 -1 3 -1 
0 0 0 0 0 0 0 0 -1 3
*/

/*
2 1 1 1 1 1 1 1 1 2
*/


/*
3 -1 0 0 0 0.5
-1 3 -1 0 0.5 0
0 -1 3 -1 0 0
0 0 -1 3 -1 0
0 0.5 0 -1 3 -1
0.5 0 0 0 -1 3
*/

/*
2.5 1.5 1 1 1.5 2.5
*/