/**************************************************/
/*                                                */
/*  Lab 2 Starter file                            */
/*                                                */
/*  Name:Aleksandr Stepanenko                     */
/*  Student number:124888181                      */
/*                                                */
/**************************************************/

#include <math.h>
unsigned int factorial (unsigned int n){
    if (n > 1) {
        return n * factorial(n - 1);
    }
    else {
        return 1;
    }
}
double power (double base, unsigned int n){
    if (n  > 0) {
        return (power(base,n-1) * base);
    }
    else {
        return 1;
    }
}
unsigned int fibonacci (unsigned int n){
    if (n <= 1) {
        return n;
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
	
}

