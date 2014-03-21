#include <iostream>
#include <iterator>
#include <list>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
using namespace std ;

int main(void) {

/*insert iterator*/
/*
	list<int> a , b ;
	insert_iterator< list<int> > itr1(a,a.begin()) ;
	for( int i = 1 ; i < 6 ; ++i , ++itr1 ) *itr1 = i ;		
	front_insert_iterator< list<int> > itr2(b) ;
	for( int i = 1 ; i < 6 ; ++i ) *itr2 = i ;

	list<int>::iterator iter ;
	for ( iter = a.begin() ; iter != a.end() ; ++iter ) cout << *iter << " " ;
	cout << endl ;
	for ( iter = b.begin() ; iter != b.end() ; ++iter ) cout << *iter << " " ;
	cout << endl ;
*/
/*copy , inserter*/
/*
	int no[10] = {2,3,4,5,1,7,8,1,3,5} ;
	list<int> foo ;

	copy( no+2 , no+6 , back_inserter(foo) ) ;
	copy( no+5 , no+7 , front_inserter(foo) ) ;
	
	list<int>::iterator itr ;
	for( itr = foo.begin() ; itr != foo.end() ; ++itr ) {
		cout << *itr << " " ;
	}
	cout << endl ;
*/
/*istream iterator*/
/*
	istream_iterator<int> iitr(cin) ;
	int sum = 0 ;
	for(; iitr != istream_iterator<int>(); ++iitr )
		sum += *iitr ;
	cout << sum << endl ;
*/
/*ostream_iterator*/
/*
	list<int> fooo ;
	ifstream infile("data.txt") ;
	istream_iterator<int> in(infile) ;

	copy( in , istream_iterator<int>() , front_inserter(fooo) ) ;
	copy( fooo.begin() , fooo.end() , ostream_iterator<int>(cout,"->")) ;

	cout << endl ;
*/
/*filln*/
/*
	int i,j,n ;
	vector<int> foo2 ;
	
	while(1) {
		cout << "> " ;
		cin >> n ;
		foo2.resize(2*n-1) ;
		for( i = 0 ; i < 2*n-1 ; ++i ) {
			j = ( i < n ? i : 2*n-2-i ) ;
			fill_n( foo2.begin() + j , 2*n-1-2*j , j+1 ) ;
			copy( foo2.begin() , foo2.end() , ostream_iterator<int>(cout," ") ) ;
			cout << endl ;
		}

	}
*/

/*adjacent_find()*/
	const int N = 10 ;
	int i, j, n , k ;
	locale utf8("zh_TW.UTF-8") ;
	setlocale(LC_ALL,"zh_TW.UTF-8") ;
	//int bar[N] = { 7, 3 , 3 , 4  , 5 ,6 ,6 ,8 ,9 ,3} ;
	wstring bar = L"各各位位位鄉民,大家好好好" ;


	j = 0 ;
	while( j < bar.size() ){
		k = adjacent_find(bar.begin()+j,bar.end()) - bar.begin() ;
		if ( k != j) {
			if( k!= j) wcout << bar.substr(j,k-j) ;
			//copy(bar+j,bar+k,ostream_iterator<int>(cout," ")) ;
		}
		j = k+1 ;

	}

	return 0 ;
}
