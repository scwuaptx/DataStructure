#include <iostream>
#include <algorithm>

using namespace std ;

int GCD( int a ,int b){
	if(a == 0 )
		return 1;
	if( a >= b)
		return a%b == 0 ? b : GCD( b , a%b ) ;
	else
		return b%a == 0 ? a : GCD( a , b%a ) ; 
}


struct Fraction{
	unsigned int num , den ;
	Fraction( unsigned int n , unsigned int d ): num(n/GCD(n,d)) , den(d/GCD(n,d)) {} ;
};

ostream& operator<< ( ostream& out , const Fraction& foo ){
	return out << foo.num << '/' << foo.den ;
}

struct MyRule{
	bool operator() ( const Fraction& x , const Fraction & y) { 
		if( x.den != y.den )
			return x.den < y.den ;
		else
			return x.num > y.num ;
	}
};

Fraction operator+ ( const Fraction& a , const Fraction& b){
	int newden = a.den*b.den ;
	int newnum = a.num*b.den + a.den*b.num ;
	return Fraction(newnum,newden) ;
}

Fraction operator* ( const Fraction& a , const Fraction& b){
	return Fraction(a.num*b.num,a.den*b.den) ;
}

template <class Function1 ,class Function2 , class Iterator1 ,class Iterator2, class T>
T compute( Iterator1 start1 , Iterator1 end1 , Iterator2 start2, Iterator2 end2,T value, Function1 fn1 , Function2 fn2){
	Fraction temp(1,1) ;
	for( ; start1 != end1 ; ++start1 , ++start2){
		temp = fn1(*start1,*start2) ;
		value = fn2(value,temp) ;
	}
	return value ;
}

int main(void){
	Fraction foo[4] = { Fraction(2,3) , Fraction(3,5) , Fraction(7,5) , Fraction(7,3) } ;
	Fraction bar[4] = { Fraction(3,2) , Fraction(5,3) , Fraction(5,7) , Fraction(3,7) } ;

	sort( foo , foo+4 , MyRule() ) ;
	sort( bar , bar+4 , MyRule() ) ;
	
	for (int i = 0 ; i < 4 ; ++i )
		cout << foo[i] << "||" << bar[i] << endl ;
	
	cout << compute(foo , foo+4 , bar , bar+4 , Fraction(0,1) , multiplies<Fraction>(), plus<Fraction>()) << endl ;

	return 0 ;

}
