#include <stdio.h>
#include <math.h>

//search for x
// sinx=6x+5  --> x = (sinx-5)/6
//x^3 = 2x+2  --> x =(2*x+2)^1/3
//lnx + x^2 = 3 --> x = (3-log(x))^1/2 
//e^x + x = 4 --> x = 4 - e^x

double func(double x)
{
    return (sin(x)-5)/6;
}

double func2(double x)
{
    return pow(3-log(x),1.0/2);
}

double num_abs(double num)
{
    if(num < 0)
    {
        num *= -1;
    }
    return num;
}

int main()
{
    double x = 0, pre_x = 0;
    printf("please enter x0 you guess:");
    scanf("%lf",&x);
    do
    {
        pre_x = x;
        x = func2(pre_x);                           //function change
    }while(num_abs(pre_x - x) > 0.00001);
    printf("ans = %.4lf\n",x);
    return 0;
}   