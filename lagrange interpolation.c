#include <stdio.h>
#include <stdint.h>

typedef struct _points{
    double x;
    double y;
}point;

double larange(int32_t n,point enter[n],double x)
{
    double fun = 0;
    for(int32_t i = 0 ; i < n ; i++)
    {
        double tmp = 1;
        for(int32_t j = 0 ; j < n ; j++)
        {
            if(j != i)
            {
                tmp *= (x-enter[j].x)/(enter[i].x-enter[j].x);
            }
        }
        fun += enter[i].y*tmp;
    }
    return fun;
}

int main()
{
    int32_t n = 0;
    printf("please enter your n:");
    scanf("%d",&n);
    point enter[n];
    for(int32_t i = 0 ; i < n ; i++)
    {
        printf("please enter x%d : (x y)",i);
        scanf("%lf %lf",&enter[i].x,&enter[i].y);
        
    }
    double que = 0;
    printf("please enter the guess x:");
    scanf("%lf",&que);
    double ans = 0;
    ans = larange(n,enter,que);
    printf("ans = %lf\n",ans);
}

/*
1960 3039585530
1970 3707475887
1990 5281653820
2000 6079603571
1980
*/
