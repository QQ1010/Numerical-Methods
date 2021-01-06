#include <stdio.h>
#include <stdint.h>
#include <math.h>

//search for x with range

#define F1(x) exp(x-2)+pow(x,3)-x    //--> e^(x-2) + x^3 - x = 0
#define F2(y) exp(y) + y - 7         // --> e^x + x = 7

int main()
{
    double ans = 1;
    double ran1,ran2;
    double mid = 0;
    double check = 0;
    printf("please enter your range(x1 x2):");
    scanf("%lf %lf",&ran1,&ran2);
    mid = (ran1+ran2)/2;
    check = ran1-ran2;
    if(check < 0)
    {
            check *= -1;
    }
    while(check > 0.000001)
    {
        ans = F2(mid);               //fnction1
        if(ans < 0)
        {
            ran1 = mid;
            mid = (ran1+ran2)/2;
            check = ran1 - ran2;
            if(check < 0)
            {
                check *= -1;
            }
        }
        else if(ans > 0)
        {
            ran2 = mid;
            mid = (ran1+ran2)/2;
            check = ran1 - ran2;
            if(check < 0)
            {
                check *= -1;
            }
        }
    }
    printf("x = %.4lf\n",mid);
    return 0;
}
