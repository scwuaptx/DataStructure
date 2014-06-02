#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <functional>
#include <fstream>
#include <string>
#include <sstream>

using namespace std ;

const double SMALL = 1.0e-10 ;

/*--define Studnet struct--*/
struct Student{
	string name ;
	int old ;

	//constructor
	Student() : name("\0"), old(0) {}

	//assignment operator
	Student& operator=( const Student& foo ){
		name = foo.name ;
		old = foo.old ;
	}

	//overriding < operator
	bool operator<( const Student& foo ) const {
		if ( old < foo.old ) 
			return true ;
		else if ( old == foo.old ) 
			return name.size() < (foo.name).size() ;
		else 
			return false ;
	}

	//output operator
	friend ostream& operator<<( ostream& out , const Student& foo ){
		return out << foo.name << "[" << foo.old << "]" ;
	}
} ;


template <typename T , typename LESS = less<T> >
class Priority_Queue{
	
	vector<T> data ;

	//Node of son
	int leftson( int i ) const { return 2 * i + 1 ; }
	int rightson( int i ) const { return 2 * i + 2 ; }

	//Node of Parent
	int parent( int i ) const { return (i-1)/2 ; }

	//whether is a node
	bool tree_node( int i ) const {
		return ( i < data.size() ? true:false ) ;
	}

	int depth( int i ) const {
		return static_cast<int>(log(i+1)/log(2)+SMALL) ;
	}

	//reheapification upward
	void reheap_upward( int i = 0 ){
		int p = parent(i) ;

		while( LESS()(data[p] ,data[i]) ){
				swap( data[p] , data[i] ) ;
				i = p ;
				if( i == 0 ) return ;
				p = parent(i) ;
		}
	}
	public :

		//constructor
		Priority_Queue() {}
		
		Priority_Queue( const T* a , const T* b){
			for( ; a != b ; ++a ) push(*a) ;
		}

		Priority_Queue( const vector<T>& f ) {
    		for ( int i = 0 ; i < f.size() ; i++ ) push(f[i]) ;
		 }

		//Number of data
		int size() const { return data.size() ; }

		//push a element
		void push( const T& a ){
			data.push_back(a) ;
			reheap_upward( size() - 1 ) ;
		}

		//element of top
		T top() const { return data[0] ; }

		//print the tree
		void print_queue_as_tree( int i , ostream& out ) const {
			if(tree_node(i)){
				print_queue_as_tree(rightson(i),out) ;
				for( int j = 0 ; j < depth(i)-1 ; j++ ) out << "|        " ;
				out << ( i > 0 ? "+------> " : "" ) << data[i] <<  endl ;
				print_queue_as_tree(leftson(i), out) ;
			}
		}

		//output operator
		friend ostream& operator<< (ostream& out , const Priority_Queue& foo ){
			foo.print_queue_as_tree(0,out) ;
			return out << endl ;
		}
} ;


int main() {
	const int N = 9 , M = 6 ;

	//read the file
	ifstream infile("score.txt") ;
	string line ,name ;
	int old ;
	vector<Student> Studentlist ;
	Student stu ;
	istringstream istring ;

	while( getline(infile,line) ){
		istring.str(line) ;
		istring >> name ;
		stu.name = name ;
		istring >> old ;
		stu.old = old ;
		//push a node
		Studentlist.push_back(stu) ;
		istring.clear() ;
	}

	Priority_Queue<Student> a(Studentlist) ;

	cout << a ;


	return 0 ;
}
