#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

/*Fraction operator*/
struct Fraction{
	unsigned int num , den ;
	Fraction( unsigned n , unsigned d ) : num(n) , den(d) {} ;
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



/*Fraction multiplies operator*/
Fraction operator* ( const Fraction& a , const Fraction& b ) {
	return Fraction(a.num*b.num,a.den*b.den) ;
}

/*Fraction multiplies function*/
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

/*Fraction divides function*/
template < class T >
struct divs{
	T operator() ( const T& a , const T& b) const {
		return a/b ;
	}
};


template<class Function , class Iterator , class T>
T compute( Iterator start , Iterator end , T value , Function fn ) {
	for ( ; start != end ; ++start ) value = fn(value,*start) ;
	return value ;
}

int main(void){

	Fraction foo[4] = { Fraction(2,3) , Fraction(3,5) ,	Fraction(7,5) , Fraction(7,3) } ;
	//int a[4] = {2,4,6,8} ;

	cout << compute( foo , foo+4 , foo[0]*foo[0] , divs<Fraction>() ) << endl ;
	//sort( foo , foo+4 , Bigger() ) ;
	//for ( int i = 0 ; i < 4 ; ++i ) cout << foo[i] << ' ' ;


	return 0 ;
}
