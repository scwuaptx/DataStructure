#include <iostream>

using namespace std ;

/*vector*/
class Vector {
	private :
		int *data ;
		int rsize ; 
		int osize ;
	public :
		Vector() : data(NULL), rsize(0) , osize(0) {}

		Vector( int n , int val = 0 ) : osize(n) , rsize(n) {
			data = new int[rsize] ;
			for( int i = 0 ; i < osize ; ++i ) data[i] = val ;
		}
	
		~Vector(){
			if ( rsize >0 ){
				delete [] data ;
			}

		}

		Vector( const Vector& foo ){
			osize = foo.osize ;
			rsize - foo.rsize ;
			data = new int[rsize] ;
			for( int i = 0 ; i < osize ; ++i )
				data[i] = foo.data[i] ;
		}

		Vector& operator= ( const Vector& foo){
			if ( this == &foo ) return *this ;
			if ( rsize < foo.osize ){
				delete [] data ;
				rsize = foo.rsize ;
				osize = foo.osize ;
				data = new int[rsize] ;
				for ( int i = 0 ; i < osize ; ++i )
					data[i] = foo.data[i] ;
			}else{
				osize = foo.osize ;
				for ( int i = 0 ;i < osize ; ++i )
					data[i] = foo.data[i] ;
			}
		}
		
		int size() const { return osize ; }

		void push_back( int v ){
			if( rsize == 0 ){
				osize = 1 ;
				rsize = 0 ;
			}else if( osize == rsize ){
				rsize = 2 * rsize ;
				int *q = new int[rsize] ;
				for ( int i = 0 ; i < osize ; ++i ){
					q[i] = data[i] ;
				}
				delete [] data ;
				data = q ;
				data[osize] = v ;
			}else{
				data[osize] = v ;
			}

			++osize ;
		}

		void pop_back(){
			if( osize > 0 ) --osize ; 
		}

		int front() const { return data[0] ;}
		int back() const { return data[osize-1] ;}

		int& front() { return data[0] ; }
		int& back() { return data[osize-1] ;}

		int operator[] (int i) const {return data[i] ;}
		int& operator[] (int i) {return data[i] ;} 

		friend ostream& operator<< ( ostream& ostr , const Vector& foo ){
			ostr << "[" << foo.osize << "," <<  foo.rsize << "] : " ;
			for( int i = 0 ; i < foo.osize ; ++ i ){
				ostr << foo.data[i] << " " ;
			}
			return ostr ;

		}
};

Vector operator+( const Vector& a, const Vector& b ){
	Vector c ;
	int i ;
	for( i = 0 ; i < a.size() ; ++i ) c.push_back(a[i]) ;
	for( i = 0 ; i < b.size() ; ++i ) c.push_back(b[i]) ;
	return c ;
}


int main(void){

	Vector a(3,2) , b , c(2,1) ;
	cout << a << '\n' << b << '\n' << c << endl ;

	b = a ;

	cout << a+c ;

	cout << "\n\n\n" ;


	for( int i = 0 ; i < 5 ; ++i ){
		c.push_back(i) ;
		cout << c << endl ;
	}

	for( int i = 0 ; i < 10 ; ++i ){
		c.pop_back() ;
		cout << c << endl ;
	}

	return 0 ;

}
