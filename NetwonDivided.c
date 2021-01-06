#include <stdio.h>
#include <stdint.h>

typedef struct _data
{
    double x;
    double y;
}data;

int main()
{
    int32_t num = 0;
    printf("please enter the num of data:");
    scanf("%d",&num);
    data input[num];
    for(int32_t i = 0 ; i < num ; i++)
    {
        printf("please enter data (x y):");
        scanf("%lf %lf",&input[i].x,&input[i].y);
    }
    double guess = 0;
    printf("please enter your guess:");
    scanf("%lf",&guess);
    double expon[num][num];
    for(int32_t i = 0 ; i < num ; i++)
    {
        for(int32_t j = 0 ; j < num-i ; j++)
        {
            if(i == 0)
            {
                expon[i][j] = input[j].y;
            }
            else
            {
                expon[i][j] = (expon[i-1][j+1]-expon[i-1][j])/(input[i+j].x-input[j].x);
            }
        }
    }
    double ans = 0;
    for(int32_t i = num-1 ; i >= 0 ;i--)
    {
        ans *= (guess - input[i].x);
        printf("c_%d = %lf\n",i,expon[i][0]);
        ans += expon[i][0];
    }
    printf("ans = %lf\n",ans);
}

/*
4
1800 280
1850 283
1900 291
2000 370
1950  
ans = 316
*/