#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

/*ex
 F(x):                  matrix:1*3
 x+y+z-3 = 0
 x^2+y^2+^2-5 = 0
 e^x+xy-xz-1 = 0
*/

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

void enter_Fmatrix(double matrix[],double var[])
{
    //you need to change here
    double x = var[0];
    double y = var[1];
    double z = var[2];
    matrix[0] = (x+y+z-3)*(-1);
    matrix[1] = (pow(x,2)+pow(y,2)+pow(z,2)-5)*(-1);
    matrix[2] = (exp(x)+(x*y)-(x*z)-1)*(-1);
}


void enter_Dmatrix(double **matrix,double var[])
{
    //you need to change here
    double x = var[0];
    double y = var[1];
    double z = var[2];
    matrix[0][0] = 1;
    matrix[0][1] = 1;
    matrix[0][2] = 1;
    matrix[1][0] = 2*x;
    matrix[1][1] = 2*y;
    matrix[1][2] = 2*z;
    matrix[2][0] = exp(x)+y-z;
    matrix[2][1] = x;
    matrix[2][2] = -1*x;
}

void Gaussian(double Fmatrix[],double **Dmatrix,double Smatrix[])
{
    double **matrix;
    //you need to change here!
    int32_t row = 3;
    int32_t col = 4;
    matrix = matrix_calloc(row,col);
    for(int32_t i = 0 ; i < row ; i ++)
    {
        for(int32_t j = 0 ; j < col ; j++)
        {
            if(j != col-1)
            {
                matrix[i][j] = Dmatrix[i][j];
            }
            if(j == col-1)
            {
                matrix[i][j] = Fmatrix[i];
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
    for(int32_t i = 0 ; i < row ; i++)
    {
        Smatrix[i] = matrix[i][col-1];
    }
}

int main()
{
    int32_t num = 0;
    printf("please enter the number of variables:");
    scanf("%d",&num);
    double x0[num];
    printf("please enter the initial vercotr X0:");
    for(int32_t i = 0 ; i < num ; i++)
    {
        scanf("%lf",&x0[i]);
    }
    double Fmatrix[num];
    enter_Fmatrix(Fmatrix,x0);
    int32_t row = num;
    int32_t col = num;
    double **Dmatrix;                        //must square
    Dmatrix = matrix_calloc(num,num);
    enter_Dmatrix(Dmatrix,x0);
    double Smatrix[num];
    double next[num];
    Gaussian(Fmatrix,Dmatrix,Smatrix);
    int32_t k = 0;
    while(k != 10)
    {
        k++;
        for(int32_t i = 0 ; i < num ; i++)
        {
            next[i] = x0[i] + Smatrix[i];
        }
        for(int32_t i = 0 ; i < num ; i++)
        {
            x0[i] = next[i];
        }
        enter_Fmatrix(Fmatrix,next);
        enter_Dmatrix(Dmatrix,next);
        Gaussian(Fmatrix,Dmatrix,Smatrix);
    }
    printf("Ans:\n");
    for(int32_t i = 0 ; i < num ; i++)
    {
        printf("%.4lf\n",next[i]);
    }
    return 0;
}