#include <iostream>
#include <cassert>
using namespace std ;

template<typename T>
struct Node{
	T data ;
	Node<T>* fptr ;
	Node<T>* bptr ;

	Node(){}

	Node(const T& a):data(a),fptr(NULL),bptr(NULL){} 
};

struct large_first{
	bool operator()( const int& a, const int& b){
		return a < b ;
	}
} ;

template<typename T>
ostream& operator<<(ostream& out ,const Node<T>* foo){
	return out << foo->data ;
}

template<typename T>
class List{
	private :
		Node<T> *head ;
		Node<T> *tail ;
		int osize ;
	public :

		List():head(NULL), tail(NULL) , osize(0){}

		List( const List<T>& foo ):head(NULL),tail(NULL),osize(0){
			const Node<T>* ptr ;
			for(ptr = foo.begin(); ptr != foo.end() ; ptr=ptr->fptr)
				push_back(ptr->data) ;
		}
		
		const List<T>& operator=(const List<T>& foo){
			if(this = &foo ) return *this ;
			clear() ;
			const Node<T> *ptr ;
			for(ptr = foo.begin() ; ptr = foo.end() ; ptr=ptr->fptr)
				push_back(ptr->data) ;
			return *this ;
		}

		const Node<T>* begin() const { return head ;}
		Node<T>* begin() {return head ;}
		Node<T>* end() const {return NULL ;}  	

		void push_back(const T & no){
			if( osize == 0 ){
				head = tail = make_node(no);
			}else{
				tail->fptr = make_node(no) ;
				tail->fptr->bptr = tail ;
				tail = tail->fptr ;
			}
			++osize ;
		}

		void pop_back(){
			if( osize == 0 ){
				return ;
			}else if( osize == 1){
				head = tail = NULL ;
			}else{
				tail = tail->bptr ;
				delete tail->fptr ;
				tail->fptr = NULL ;
			}
			--osize ;
		}

		void push_front(const T& no){
			if(osize == 0 ){
				head = tail = make_node(no) ;
			}else{
				head->bptr = make_node(no) ;
				head->bptr->fptr = head ;
				head = head->bptr ;
			}
			++osize ;
		}

		void pop_front(){
			if(osize == 0)
				return ;
			else if( osize == 1 ){
				head = tail = NULL ;
			}else{
				head = head->fptr ;
				delete head->bptr ;
				head->bptr = NULL ;
			}
			--osize ;
		}

		void insert(Node<T>* cptr ,const T& no){
			if( osize == 1 ){
				assert(cptr == head ); 
				push_front(no) ;
			}else if( osize >=2 ){
				Node<T>* nptr = make_node(no) ;
				nptr->bptr = cptr->bptr ;
				nptr->fptr = cptr ;
				cptr->bptr->fptr = nptr ;
				cptr->bptr = nptr ;
				++osize ;
			}else{
				NULL ;
			}

		}

		void erase( Node<T>* cptr){
			if( osize == 1 ){
				assert(cptr == head );
				pop_back() ;
			}else if (osize == 2){
				if(cptr == head)
					pop_front() ;
				else if(cptr == tail) 
					pop_back() ;
				else{
					NULL;
				}
			}else{
				cptr->bptr = cptr->fptr ;
				cptr->fptr->bptr = cptr->bptr ;
				delete cptr ;
				--osize ;
			}

		}

		Node<T>* find(const T& no) const{
			Node<T>* ptr ;
			for(ptr= begin() ; ptr!= end() ; ptr = ptr->fptr){
				if(ptr->data == no ) return ptr ;
			}

			return NULL ;

		}

		void sort() {
			int n , i , j ;
			Node<T>* walker, *ptr ;
			for ( walker = begin() ; walker != end() ; walker = walker->fptr ){
				n = walker->data ;
				for( ptr = walker->bptr ; ptr != NULL && (ptr->data) > n ; ptr = ptr->bptr ){
					ptr->fptr->data = ptr->data ;
				}	
				if(ptr == NULL){
					head->data = n ;
				}else{
					ptr->fptr->data = n ;
				}
			}
		}

		void sort(bool pred){	
			int n , i , j ;
			Node<T>* walker, *ptr ;
			for ( walker = begin() ; walker != end() ; walker = walker->fptr ){
				n = walker->data ;
				for( ptr = walker->bptr ; ptr != NULL && pred(ptr->data,n) ; ptr = ptr->bptr ){
					ptr->fptr->data = ptr->data ;
				}	
				if(ptr == NULL){
					head->data = n ;
				}else{
					ptr->fptr->data = n ;
				}
			}
		}

	friend ostream& operator<<(ostream& out , List<T>& foo ){
			const Node<T>* ptr ;
			for(ptr = foo.begin(); ptr!= foo.end() ; ptr=ptr->fptr){
				out << ptr->data << " " ;
			}
		return out ;
	}

	void clear(){ 
		while(osize) pop_back() ;
	}

	~List(){ clear() ; } 


};

template<typename T>
Node<T>* make_node(const T& no = 0){
	Node<T> *ptr = new Node<T>(no) ;
	return ptr ;
}

int main(void){

	int i ;
	List<int> foo ;
	for( i = 10 ; i >= 1 ; --i ) foo.push_back(i) ;	
	cout << foo << endl ;
	
	foo.sort() ;
	cout << foo << endl ;

	foo.sort( large_first() ) ;
	cout << foo << endl ;

	return 0 ;
}
