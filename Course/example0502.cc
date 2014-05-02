/*queue*/
#include <iostream>
#include <deque>
#include <list>

using namespace std ;

template<typename T>
class my_queue{
	private :
		list<T> data ;

	public :
		void push( const T& a) { data.push_back(a) ; }
		void pop() { data.pop_front() ;}
		int size() { return data.size() ;}
		bool empty() { return data.empty() ;} 
		const T& front() const { return data.front() ; }


} ;

int main(void){

	my_queue<int> foo ;
	foo.push(4) ;
	foo.push(3) ;
	foo.push(5) ;
	while( !foo.empty() ){
		cout << foo.front() << endl ;
		foo.pop() ;
	}

	return 0 ;
}
