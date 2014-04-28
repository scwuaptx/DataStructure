#include <iostream>
#include <cassert>
#include <iomanip>
using namespace std ;

//define Node struct
template<typename T>
struct Node{
	T data ;
	Node<T>* fptr ;
	Node<T>* bptr ;

	Node(){}

	Node(const T& a):data(a),fptr(NULL),bptr(NULL){} 
};

//Function object
struct large_first{
	bool operator()( const int& a, const int& b){
		return a < b ;
	}
} ;

//define the struct of wsetw 
struct wsetw{
	ostream *ptr ;
	int w ;
	wsetw(int n) : w(n) {} ;
} ;

//define the output operator of the struct of wsetw 
wsetw operator<<(ostream& out , wsetw a ){
	a.ptr = &out ;
	return a ;
}

//define the output operator if the struct of Node
template<typename T>
ostream& operator<<(ostream& out ,const Node<T>* foo){
	return out << foo->data ;
}

//define the class of List
template<typename T,typename UnaryPredicate = large_first >
class List{
	private :
		Node<T> *head ;
		Node<T> *tail ;
		int osize ;
	public :

		//constructor
		List():head(NULL), tail(NULL) , osize(0){}

		//copy constructor
		List( const List<T>& foo ):head(NULL),tail(NULL),osize(0){
			const Node<T>* ptr ;
			for(ptr = foo.begin(); ptr != foo.end() ; ptr=ptr->fptr)
				push_back(ptr->data) ;
		}
		
		//assignment constructor
		const List<T>& operator=(const List<T>& foo){
			if(this = &foo ) return *this ;
			clear() ;
			const Node<T> *ptr ;
			for(ptr = foo.begin() ; ptr = foo.end() ; ptr=ptr->fptr)
				push_back(ptr->data) ;
			return *this ;
		}

		//define the begin() and end()
		const Node<T>* begin() const { return head ;}
		Node<T>* begin() {return head ;}
		Node<T>* end() const {return NULL ;}  	

		//push an element to the end of list;
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

		//pop an element at the end of the list ;
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

		//push an element to the start of the list
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

		//pop an element at the start  of the list 
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

		//insert an element to the list,
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

		//remove an element of the list 
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

		//find an element in the list
		Node<T>* find(const T& no) const{
			Node<T>* ptr ;
			for(ptr= begin() ; ptr!= end() ; ptr = ptr->fptr){
				if(ptr->data == no ) return ptr ;
			}

			return NULL ;

		}

		//sort the list
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

		//sort by pred the list 
		void sort(UnaryPredicate pred){	
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
	
	//define output operator of List
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

	//destructor
	~List(){ clear() ; } 


};

//the function is what create a node
template<typename T>
Node<T>* make_node(const T& no = 0){
	Node<T> *ptr = new Node<T>(no) ;
	return ptr ;
}

//wsetw output operator
template<typename T>
ostream& operator<<( wsetw a , List<T>& foo ) {
	Node<T>* ptr ;
	for ( ptr = foo.begin() ; ptr != foo.end() ; ptr = ptr->fptr ){
		*(a.ptr) << setw(a.w) << ptr->data ;
	}
	return *(a.ptr) ;
}

int main(void){

	int i ;
	List<int> foo ;

	foo.push_back(7) ;
	foo.push_back(4) ;
	foo.push_back(2) ;
	foo.push_back(1) ;
	foo.push_back(4) ;
	foo.push_back(8) ;
	foo.push_back(5) ;

	foo.sort() ;
	cout << wsetw(4) << foo << endl ;
 
	foo.sort( large_first() ) ;
	cout << wsetw(4) << foo << endl ;

	return 0 ;
}
