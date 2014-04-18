/*linked list*/
#include <iostream>

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

/*
template<typename T>
void operator++( Node<T>* ptr ){ ptr = ptr->fptr ;}


template<typename T>
void operator--( Node<T>* ptr ){ ptr = ptr->bptr ;}
*/
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

		const Node<T>* begin() const { return head ;}
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

		void clear() {
			while ( osize ) pop_back() ;
		}
		
		//destructor
		~List(){ clear() ;}

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

	return 0 ;

}
