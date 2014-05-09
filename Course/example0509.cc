/*Fabonacci*/
#include <iostream>

using namespace std ;

unsigned int fib( unsigned int n ){
	static unsigned int f[100] = {0} ;
	if( n < 2 )
		return 1 ;
	else if ( f[n] != 0 )
		return f[n] ;
	else 
		return f[n] = fib(n-2) + fib(n-1) ;
}

int main(void){

	for(unsigned int i = 0 ; i < 50 ; ++i)
		cout << "[" << i << "]" << " " << fib(i) << " " << flush;
	cout << endl ;
	return 0 ;
}
