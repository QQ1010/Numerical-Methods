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
    // LU
    double b[row];
    double c[row];
    double ans[row];
    double mult = 0;
    double Lmatrix[row][col];
    double Umatrix[row][col];
    for(int32_t i = 0 ; i < row ; i++)
    {
        b[i] = matrix[i][col-1];
    }
    for(int32_t j = 0 ; j < col ; j++)
    {
        for(int32_t i = j+1 ; i < row ; i++)
        {
            mult = matrix[i][j] / matrix[j][j];
            Lmatrix[i][j] = mult;
            mult *= -1;
            for(int32_t k = 0 ; k < col ; k++)
            {
                matrix[i][k] += matrix[j][k]*mult;
            }
        }
    }
    for(int32_t i = 0 ; i < row ; i++)
    {
        for(int32_t j = 0 ; j < col ; j++)
        {
            if(i == j)
            {
                Lmatrix[i][j] = 1;
            }
            if(i < j)
            {
                Lmatrix[i][j] = 0;
            }
        }
    }
    for(int32_t i = 0 ; i < row ; i++)
    {
        Lmatrix[i][col-1] = b[i];
    }
    printf("Lmatrix\n");
    for(int32_t i = 0 ; i < row ; i++)
    {
        for(int32_t j = 0 ; j < col-1 ; j++)
        {
            printf("%.4lf ",Lmatrix[i][j]);
        }
        printf("\n");
    }
    mult = 0;
    for(int32_t j = 0 ; j < col ; j++)
    {
        for(int32_t i = j+1 ; i < row ; i++)
        {
            mult = Lmatrix[i][j] / Lmatrix[j][j];
            mult *= -1;
            for(int32_t k = 0 ; k < col ; k++)
            {
                Lmatrix[i][k] += Lmatrix[j][k]*mult;
            }
        }
    }
    for(int32_t i = row-1 ; i >= 0 ; i--)
    {
        for(int32_t j = i-1 ; j >=0 ; j--)
        {
            mult = Lmatrix[j][i]/Lmatrix[i][i];
            mult *= -1;
            for(int32_t k = 0 ; k < col ; k++)
            {
                Lmatrix[j][k] += Lmatrix[i][k]*mult;
            }
        }
    }
    for(int32_t i = 0 ; i < row ; i++)
    {
        if(Lmatrix[i][i] != 1)
        {
            Lmatrix[i][col-1] /= Lmatrix[i][i];
            Lmatrix[i][i] = 1;
        }
        c[i] = Lmatrix[i][col-1];
    }
    for(int32_t i = 0 ; i < row ; i ++)
    {
        Umatrix[i][col-1] = c[i];
    }
    for(int32_t i = 0 ; i < row ; i++)
    {
        for(int32_t j = 0 ; j < col ; j++)
        {
            Umatrix[i][j] = matrix[i][j];
        }
    }
    printf("Umatrix\n");
    for(int32_t i = 0 ; i < row ; i++)
    {
        for(int32_t j = 0 ; j < col-1 ; j++)
        {
            printf("%.4lf ",Umatrix[i][j]);
        }
        printf("\n");
    }
    mult = 0;
    for(int32_t j = 0 ; j < col ; j++)
    {
        for(int32_t i = j+1 ; i < row ; i++)
        {
            mult = Umatrix[i][j] / Umatrix[j][j];
            mult *= -1;
            for(int32_t k = 0 ; k < col ; k++)
            {
                Umatrix[i][k] += Umatrix[j][k]*mult;
            }
        }
    }
    for(int32_t i = row-1 ; i >= 0 ; i--)
    {
        for(int32_t j = i-1 ; j >=0 ; j--)
        {
            mult = Umatrix[j][i]/Umatrix[i][i];
            mult *= -1;
            for(int32_t k = 0 ; k < col ; k++)
            {
                Umatrix[j][k] += Umatrix[i][k]*mult;
            }
        }
    }
    for(int32_t i = 0 ; i < row ; i++)
    {
        if(Umatrix[i][i] != 1)
        {
            Umatrix[i][col-1] /= Umatrix[i][i];
            Umatrix[i][i] = 1;
        }
        ans[i] = Umatrix[i][col-1];
    }
    printf("b matrix:\n");
    for(int32_t i = 0 ; i < row ; i++)
    {
        printf("%.lf\n",b[i]);
    }
    printf("c matrix:\n");
    for(int32_t i = 0 ; i < row ; i++)
    {
        printf("%.lf\n",c[i]);
    }
    for(int32_t i = 0 ; i < row ; i++)
    {
        printf("%.4lf \n",ans[i]);
    }
}