#include <iostream>

using namespace std ;

class Pascal{
	private :
		int **p ;
		int size ;
	public :

		Pascal( int n ) : size(n){
			p = new int*[n] ;
			int i , j ;
			for( i = 0 ; i < n ; ++i ){
				p[i] = new int[i+1] ;
				for ( j = 0 ; j <= i ; ++j ){
					if ( j == 0 || j == i ) {
						p[i][j] = 1 ;
					}else{
						p[i][j] = p[i-1][j-1] + p[i-1][j] ;
					}
				}
			}
		}

		Pascal( const Pascal& foo ){
			size = foo.size ;
			p = new int*[size] ;

			int i , j ;
			for ( i = 0 ; i < size ; ++i ){
				p[i] = new int[i+1] ;
				for( j = 0 ; j <= i ; ++j ){
					p[i][j]=foo.p[i][j] ;
				}
			}

		}

		Pascal& operator= ( const Pascal& foo ){
			if( this == &foo ) return *this ;
			int i, j ;
			if ( size > 0 ) {
				for( i = 0 ; i < size ; ++ i ) delete [] p[i] ;
				delete [] p ;
			}

			size = foo.size ;
			p = new int*[size] ;

			for ( i = 0 ; i < size ; ++i ){
				p[i] = new int[i+1] ;
				for( j = 0 ; j <= i ; ++j ){
					p[i][j]=foo.p[i][j] ;
				}
			}
		}

		~Pascal() {
			if ( size > 0 ){
				for( int i = 0 ; i < size ; ++i ) delete [] p[i] ;
				delete [] p ;
			}
		}
		
		friend ostream& operator<< ( ostream& ostr , const Pascal& foo ){
			int i , j ;
			for ( int i = 0 ; i < foo.size ; ++i ){
				for ( j = 0 ; j <= i ; ++j ){
					ostr << foo.p[i][j] << " " ;
				}
				ostr << endl ;
			}
			return ostr ;
		}

} ;


int main(void){

	int n ;

	cout << "> n : " ;
	cin >> n ;
	Pascal foo(n) ;
	cout << foo << endl ;

	Pascal bar = foo ;
	cout << bar << endl ;

	Pascal c(n+2) ;
	cout << c << endl ;

	bar = c ;
	cout << bar << endl ;

	return 0 ;
}
