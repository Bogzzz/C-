/**************************************************/
/*                                                */
/*  Lab 1 Starter file                            */
/*                                                */
/*  Name:Aleksandr Stepanenko                     */
/*  Student number:  124888181                    */
/*                                                */
/**************************************************/

unsigned int factorial (unsigned int n){

	unsigned int z = 1;						//	1	
	// 1*1 = 1 so we dont start from 1
	for ( int i = 2; i <= n; i++) {			// 1 + (n-1) + (n-1)
		z *= i;								// 2(n-1)
}
	return z;								//	1
}
double power (double base, unsigned int n){

	unsigned int z = 1;
	for (int i = 1; i <= n; i++) {

		z *= base;
	}
	return z;
}
unsigned int fibonacci (unsigned int n){
	
	unsigned int z = 1;
	unsigned int tmp = 0;
	unsigned int tmp2 = 1;

	for (int i = 1; i < n; i++) {

		z = tmp + tmp2;
		tmp = tmp2;
		tmp2 = z;

	}
	if (n == 0) {
		return 0;
	}
	else
	{
		return z;
	}

}
