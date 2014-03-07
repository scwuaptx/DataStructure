#include <iostream>
#include <vector>
#include <iomanip>
#include <list>
using namespace std ;

class LList{
	private :
		list < list<int> > num ;
	public :
		LList( int n ){
			int i , j , k ;
			list<int> foo ;

			k = 1 ;
			for ( i = 1 ; i <=n ; ++i) {
				foo.clear() ;
				for ( j = 0 ; j < i ; ++ j , ++k ) foo.push_back(k) ;
				num.push_back(foo) ;
			}
		}

		friend ostream& operator<< ( ostream& out, const LList& foo ){
			list< list<int> >::const_iterator iter1 ;
			list<int>::const_iterator iter2 ;

			for( iter1 = foo.num.begin(); iter1 != foo.num.end() ; ++iter1 ){
				for( iter2 = (*iter1).begin() ; iter2 != (*iter1).end() ; ++iter2 ){
					out << *iter2 << " " ;
				}
				out << endl ;
			}
			return out ;
		}
};


int main(void){

/*--------capacity------*/
	
	vector<int> foo ;

	for( int i = 0 ; i < 100 ; ++i ) {
		foo.push_back(i) ;
		if( foo.size() == foo.capacity() ) cout << foo.size() << endl ;
	}

/*-------pascal------*/

	int i , j , n = 6 ;
	vector< vector<int> > pascal ;

	for( i = 0 ; i < n ; ++i ) {
		pascal.push_back( vector<int>(1,1) ) ;
	
		for( j = 1 ; j < i ; ++j )
			pascal[i].push_back( pascal[i-1][j-1] + pascal[i-1][j] ) ;
		if( i > 0 ) pascal[i].push_back(1) ;
		
	}

	for( i = 0 ; i < pascal.size() ; ++i ){
		for( j = 0 ; j < pascal[i].size() ; ++j )
			cout << setw(4) << pascal[i][j] ;
		cout << endl ;
	}
	
/*---------LLIST-------------*/
	LList foo2(5) ;
	cout << foo2 << endl ;
	
	return 0 ;

}
