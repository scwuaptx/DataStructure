#include <iostream>
#include <iomanip>

using namespace std ;

class Pascal{
	private :
		int **p ;
		int size ;
	public :

		Pascal() : p(NULL) , size(0) {}

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
		
		void reset( int n ){
			int i,j ;
			if ( size > 0 ){
			for(i = 0 ; i < size ; ++ i ) delete [] p[i] ;
			delete [] p ;
			}
			
			size = n ;
			p = new int*[size] ;

			for ( i = 0 ; i < size ; ++i ){
				p[i] = new int[i+1] ;
				for( j = 0 ; j <= i ; ++j ){
					if( j == 0 || j == i ){
						p[i][j] = 1 ;
					}else{
						p[i][j] = p[i-1][j-1] + p[i-1][j] ;
					}
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
			int i , j , s ;
			s = 4 ;
			for ( int i = 0 ; i < foo.size ; ++i ){
				ostr << setw((foo.size-i-1)*s/2+s) << foo.p[i][0] ;
				for ( j = 1 ; j <= i ; ++j ){
					ostr << setw(s) <<foo.p[i][j]  ;
				}
				ostr << endl ;
			}
			return ostr ;
		}

} ;


int main(void){

	Pascal foo ;
	int n ;
	while(1) {
		cout << "> n : " ;
		cin >> n ;
		foo.reset(n) ;
		cout << foo << endl ;
	}
	return 0 ;
}
