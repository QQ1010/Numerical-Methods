#include <stdio.h>
#include <stdint.h>

int main()
{
    int32_t row,col;
    printf("please enter the row of matrix:");
    scanf("%d",&row);
    printf("please enter the col of matrix:");
    scanf("%d",&col);
    double matrix[row][col];
    printf("please enter the matrix:\n");
    for(int32_t i = 0 ; i < row ; i++)
    {
        for(int32_t j = 0 ; j < col ; j++)
        {
            scanf("%lf",&matrix[i][j]);
        }
    }
    printf("ans\n");
    // Gaussian Elimination
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
    printf("\n");
    for(int32_t i = 0 ; i < row ; i++)
    {
        printf("ans:x%d = %.4lf\n",i,matrix[i][col-1]);
    }
}