#include <stdio.h>
#include <math.h>

//search for x

#define F1(x) (exp(x)+x-7)    //f(x_i)can change to f(x_i)(x_i-x_i-1)
#define F11(x) (exp(x)+1)   //f'(x_i)can change to f(x_i)-f(x_i-1)
#define F2(y) (log(y)+y*y-3)
#define F21(y) (1/y+2*y)
#define Fcheck(z) (pow(z,3)+z-1)
#define Fcheck1(z) (3*z*z+1)


int func1(double x1)
{
    double x2 = x1-(F1(x1)/F11(x1));
    double sub = x1-x2;
    while(abs(sub) > 0.000001)
    {
        x2 = x1-(F1(x1)/F11(x1));
        // printf("a = %lf\n",x2);
        sub = x1 - x2;
        x1 = x2;
    }
    printf("ans = %.4lf\n",x2);
}

int func2(double x1)
{
    double x2 = x1-(F2(x1)/F21(x1));
    double sub = x1-x2;

    while(abs(sub) > 0.000001)
    {
        x2 = x1-(F2(x1)/F21(x1));
        // printf("a = %lf\n",x2);
        sub = x1 - x2;
        x1 = x2;
    }
    printf("ans = %.4lf\n",x2);
}

int main()
{
    double x0 = 1;
    printf("please enter x0:");
    scanf("%.4lf",&x0);
    func1(x0);
    // func2(x0);
    return 0;
}
