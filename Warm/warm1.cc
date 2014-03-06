#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

/*GCD Function*/
int GCD( int a , int b) {
	if( a >= b ) 
		return a%b == 0 ? b : GCD( b , a%b ) ;
	else
		return b%a == 0 ? a : GCD( a , b%a ) ;
}

/*Fraction operator*/
struct Fraction{
	unsigned int num , den ;
	Fraction( unsigned int n , unsigned int d ) : num(n/GCD(n,d)) , den(d/GCD(n,d)) {} ;	
} ;

/*print the fraction operator*/
ostream& operator<< ( ostream& out , const Fraction& foo ){
	return out << foo.num  << '/' << foo.den ;
}

/*return the bigger fraction*/
struct Bigger {
	bool operator() ( const Fraction& x , const Fraction&  y ) {
		return x.num*y.den > x.den*y.num ;
	}

} ;
/*Fraction plus operator*/
Fraction operator+ ( const Fraction& a , const Fraction& b ) {
	int newden = a.den * b.den ;
	int newnum = a.num * b.den + a.den * b.num ;
	return Fraction(newnum,newden) ;
}

/*Plus function struct*/
template < class T >
struct add{
	T operator() ( const T& a , const T & b ) const {
		return a+b ;
	}
};

/*Fraction minus operator*/
Fraction operator- ( const Fraction& a , const Fraction& b ) {
	int newden = a.den * b.den ;
	int newnum = a.num * b.den - a.den * b.den ;
	return Fraction(newnum,newden) ;
}

/*Minus function struct*/
template < class T >
struct minusf{
	T operator() ( const T& a , const T& b) const {
		return a-b ;
	}
};

/*Fraction multiplies operator*/
Fraction operator* ( const Fraction& a , const Fraction& b ) {
	return Fraction(a.num*b.num,a.den*b.den) ;
}

/*Multiplies function struct*/
template < class T >
struct mul{
	T operator() ( const T& a , const T& b) const {
		return a*b ;
	}
};

/*Fraction divides operator*/
Fraction operator/ ( const Fraction& a , const Fraction& b ) {
	return Fraction(a.num*b.den,a.den*b.num) ;
}

/*Divides function struct*/
template < class T >
struct divs{
	T operator() ( const T& a , const T& b) const {
		return a/b ;
	}
};

/*Compute function of list*/
template<class Function , class Iterator , class T>
T compute( Iterator start , Iterator end , T value , Function fn ) {
	for ( ; start != end ; ++start ) value = fn(value,*start) ;
	return value ;
}

int main(void){

	Fraction foo[4] = { Fraction(100,3) , Fraction(3,5) ,	Fraction(7,5) , Fraction(7,3) } ;
	
	/*Calculation of Fraction list*/
	cout << compute( foo+1 , foo+4 , foo[0] , add<Fraction>()) << endl ;
	cout << compute( foo+1 , foo+4 , foo[0] , minusf<Fraction>() ) << endl;
	cout << compute( foo , foo+4 , Fraction(1,1) , mul<Fraction>()) << endl ;
	cout << compute( foo+1 , foo+4 , foo[0] , divs<Fraction>() ) << endl ;
	
	
	/*Sort of fraction list*/
	sort( foo , foo+4 , Bigger() ) ;
	for ( int i = 0 ; i < 4 ; ++i ) cout << foo[i] << ' ' ;
	cout << endl ;

	return 0 ;
}
