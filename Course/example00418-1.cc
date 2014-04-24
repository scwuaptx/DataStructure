/*linked list*/
#include <iostream>
#include <cassert>

using namespace std ;


/*Node structure*/
template<typename T>
struct Node {
	T data ;
	Node<T> *fptr ; //forward pointer
	Node<T> *bptr ; //backward pointer

	Node(){}
	Node( const T& a ) : data(a) , fptr(NULL) , bptr(NULL) {}
};

template<typename T>
ostream& operator<< ( ostream& out , const Node<T>* foo ){
	return out << foo->data ;
}

template<typename T>
class List {
	private :
		Node<T> *head ;
		Node<T> *tail ;
		int osize ;
	public :

		//constructor 
		List() : head(NULL), tail(NULL) , osize(0) {}

		//copy constructor
		List( const List<T>& foo ): head(NULL),tail(NULL) , osize(0) {
			const Node<T> *ptr ;
			for( ptr = foo.begin() ; ptr != foo.end() ; ptr= ptr->fptr )
				push_back( ptr->data ) ;
		}

		//assignment 
		const List<T>& operator=( const List<T>& foo ){
			if ( this == &foo ) return *this ;
			clear() ;
			const Node<T> * ptr ;
			for ( ptr = foo.begin() ; ptr != foo.end() ;
					ptr = ptr->fptr){
					push_back( ptr->data ) ;
			}
			return *this ;
		}		

		const Node<T>* begin() const { return head ;}
		Node<T>* begin() {return head ;}
		Node<T>* end() const { return NULL ;}

		void push_back( const T& no){
			if ( osize == 0 ){
				head = tail = make_node(no) ;
			}else{
				tail->fptr = make_node(no) ;
				tail->fptr->bptr = tail ;
				tail = tail->fptr ;
			}
			++osize ;
		}

		void pop_back(){
			if ( osize == 0 ) 
				return ;
			else if ( osize == 1 ){
				delete tail ;
				head = tail = NULL ;
			}else{
				tail = tail->bptr ;
				delete tail->fptr ;
				tail->fptr = NULL ;
			}
			--osize ;	
		}

		void push_front( const T& no ){
			if ( osize == 0 )
				head = tail = make_node(no) ;
			else{
				head->bptr = make_node(no) ;
				head->bptr->fptr = head ;
				head = head->bptr ;
			}
			++osize ;
		}

		void pop_front(){
			if ( osize == 0 )
				return ;
			else if ( osize == 1 ){
				delete head ;
				head = tail = NULL ;
			}else{
				head = head->fptr ;
				delete head->bptr ;
				head->bptr = NULL ;
			}
			-- osize ;
		}
		
		Node<T>* insert( Node<T>* cptr , const T& no ){
			if ( osize == 1 ) {
				assert( cptr == head ) ;
				push_front(no) ;
				return head ;
			}else if ( osize >= 2 ){
				Node<T> *nptr = make_node(no) ;
				nptr->bptr = cptr->bptr ;
				nptr->fptr = cptr ;
				nptr->bptr->fptr = nptr ;
				cptr->bptr = nptr ;
				++osize ;
				return nptr ;
			}else {
				NULL ;
			}
		}

		void erase( Node<T>* cptr ){
			if ( osize == 1 ){
				asser(cptr == head) ;
				pop_back() ;
			}else if( osize == 2 ){
				if(cptr == head ){
					pop_front();
				}else if( cptr == tail ){
					pop_back() ;
				}else{
					NULL ;
				}
			}else{
				cptr->bptr->fptr = cptr->fptr ;
				cptr->fptr->bptr = cptr->bptr ;
				delete cptr ;
				--osize ;
			}
		}

		Node<T>* find( const T& no ) const {
			Node<T>* ptr ;
			for( ptr = begin() ; ptr != end() ; ptr = ptr->fptr ){
				if( ptr->data == no ) return ptr ;
			}
			return NULL ;
		}

		int count( const T& no ) const{
			Node<T>* ptr ;
			int c ;
			for( ptr = begin() ; ptr != end() ; ptr = ptr->fptr ){
				if( ptr->data == no ) c++ ;	
			}
			return c ;
		}


		void clear() {
			while ( osize ) pop_back() ;
		}
		
		//destructor
		~List(){ clear() ;}

		//output operator
		friend ostream& operator<< ( ostream& out , const List<T>& foo ){
			const Node<T>* ptr ;
			for( ptr = foo.begin() ; ptr != foo.end() ; ptr = ptr->fptr ){
				out << ptr->data << " " ;
			}
			
			return out ;
		}

} ;

template<typename T>
Node<T>* make_node( const T& no = 0){
	Node<T> *ptr = new Node<T>(no) ;
	return ptr ;
}

template<typename T>
List<T>& operator+=( List<T>& foo, const List<T>& bar){
	const Node<T>* ptr ;
	for( ptr = bar.begin() ; ptr != bar.end() ; ptr = ptr->fptr ){
		foo.push_back( ptr->data ) ;
	}
	return foo ;
}

int main(void){
	
	int i ;
	List<int> foo ;
	for( i = 1 ; i < 10 ; ++i ) foo.push_back(i) ;
	cout << foo << endl ;

	for( i =1 ; i <= 5 ; ++i ) foo.pop_back() ;
	cout << foo << endl ;

	for( i = 1 ; i <=5 ; ++i ) foo.push_front(i) ;
	cout << foo << endl ;

	for( i = 1 ; i <=3 ; ++i ) foo.pop_front() ;
	cout << foo << endl ;

	Node<int> *ptr = foo.begin() ;
	ptr = ptr->fptr ;
	foo.insert(ptr,10);
	cout << foo << endl ;

	List<int> bar = foo ;
	cout << bar << endl ;

	foo.pop_back() ;
	bar = foo ;
	cout << bar << endl ;

	bar += foo ;
	cout << bar << endl ;

	return 0 ;

}
