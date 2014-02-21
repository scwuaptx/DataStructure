#include <iostream>
#include <vector>
#include <deque>
#include <list>

using namespace std;

template <typename T>
void print_items( T start , T end){
	for (T i = start ; i != end ; ++i)
		cout << *i << ' ';
	return ;
}

template <	class InputIter , class T > //search template
InputIter find( InputIter start , InputIter end , const T& val ) {
	while ( start != end && *start != val )
		++start ;
	return start ;
}

template < class T >
struct Square {	
	T operator() ( const T& a ) const {
		return a * a ;
	}
};

template < class S , class T >
void print_items2 (S start, S end , T fn) {
	for(S i = start ; i != end ; ++i )
		cout << fn(*i) << ' ' ;	         //class T is a struct , for example fn can be replace by Squeare
	cout << endl ;
} ;

int main(){

	int i,j;
	deque<int> a ;          //initial a which is a deque

	for ( i = 0 ; i < 10 ; ++i) a.push_back(i) ; //add a element at the end of a

	for ( i = 0 ; i < a.size() ; ++i){   //print  a
		cout << a[i] << endl;
	}

	list<int> b ;			//initial b which is a list

	b.push_back(3) ;		//add a element at the end of b
	b.push_back(8) ;		// b = 3 8
	b.push_front(5) ;		//add a element at the front of b
	b.push_front(7) ;		// b = 7 5 3 8
	b.pop_front() ;			//remove the element at front of b
	b.pop_back() ;			//remove the element at end of b
	b.front() = 9 ;			//change the value which at the front of b
	cout << b.front() << ' ' << b.back() << endl ;

/*---------------------------------------------------------------*/
	vector<int> c(10) ;     //intital c which i a vector and the values are 10.
	
	vector<int>::iterator itr;		//let itr be a iterator

	itr = c.begin() ;
	while( itr != c.end() ){		// if itr not walk to the end of c, then ....
		*itr = 100 ;
		++itr ;
	}
	for ( itr = c.begin() ; itr != c.end() ; ++itr){ //print the elemet of c
		cout << *itr << ' ' ;
	}
	cout << endl;
/*-------------iterator of template--------------------------------*/
	vector<int> d(3,5) ;		//initial d which is a vector contain 5 5 5
	deque<int>	e(5,7) ;
	list<char>	f(10,'a') ;

	print_items( d.begin() , d.end() ) ;	//print d, input type is a iterator 
	print_items( e.begin() , e.end() ) ;
	print_items( f.begin() , f.end() ) ;	//can't use the operator '+'
	cout << endl;

/*--------------find arg template-----------------------------------*/
	vector<int> foo ;	//initial foo which is vector
	vector<int>::iterator iter;

	foo.push_back(7) ;
	foo.push_back(8) ;	
	foo.push_back(2) ;
	foo.push_back(9) ;
	foo.push_back(3) ;
	foo.push_back(1) ;	
		
	if ( find( foo.begin() , foo.end() , 3 ) == foo.end() )
		cout << "3 is not found" << endl;
	else 
		cout << "3 is found" << endl ;


/*---------------temple of operator()----------------------------*/
	Square<int> s;		//create the function of object of s square

	cout << s(2) << endl;	//print the value of s
	cout << s.operator()(2) << endl ;
	cout << Square<int>()(2) << endl ;	//Squaer<int>() can replace s, and need not create the object

/*--------------------------------------------------------------*/
	vector <int> g(3,2) ;
	print_items2( g.begin() , g.end() , Square<int>() ) ;	//print 4 4 4 4

	return 0 ;
}
