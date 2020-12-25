#include <stdio.h>
#define DEGREE 50    //degree max = 50

//P(x) = 1 + x + x^2 + ... + x^50

int main()
{

    double sum = 0;
    float x = 0;
    printf("please enter number P(x) x=");
    scanf("%f",&x);
    for(int i = 0 ; i < DEGREE ; i++) 
    {
        sum += 1;
        sum *= x;
    }
    sum += 1;
    printf("%lf",sum);
    return 0;
}
