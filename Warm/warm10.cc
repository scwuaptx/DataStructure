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

struct Student{
	string name ;
	float score ;
	Student() : name("\0"), score(0) {}
	Student& operator=( const Student& foo ){
		name = foo.name ;
		score = foo.score ;
	}
	bool operator<( const Student& foo ) const {
		return score < foo.score ;
	}

} ;

template <typename T , typename LESS = less<T> >
class Priority_Queue{
	
	vector<T> data ;

	int leftson( int i ) const { return 2 * i + 1 ; }
	int rightson( int i ) const { return 2 * i + 2 ; }

	int parent( int i ) const { return (i-1)/2 ; }

	bool tree_node( int i ) const {
		return ( i < data.size() ? true:false ) ;
	}

	int depth( int i ) const {
		return static_cast<int>(log(i+1)/log(2)+SMALL) ;
	}


	void reheap_upward( int i = 0 ){
		int p = parent(i) ;

		while( LESS()(data[p] ,data[i]) || data[p].score  == data[i].score ){
			if( LESS()(data[p] ,data[i] )){
				swap( data[p] , data[i] ) ;
				i = p ;
				if( i == 0 ) return ;
				p = parent(i) ;
			}else{
				if( (data[p].name).size() < (data[i].name).size() )
					swap(data[p],data[i]) ;
				return ;
			}
		}
	}
/*	
	void reheap_upwardname( int i = 0 ){
		int p = parent(i) ;
		while( LESS()(data[p],data[i]) || data[p] == data[i] ){
			if( LESS()(data[p] , data[i] )) {
				swap( data[p] , data[i] ) ;
				swap( name[p] , name[i] ) ;
				i = p ;
				if( i == 0 ) return ;
				p = parent(i) ; 
			}else {
				if( name[p].size() < name[i].size() ){
					swap(name[p],name[i]) ;
				}	
				return ;
			}
		}

	}
*/
	public :

		Priority_Queue() {}
		
		Priority_Queue( const T* a , const T* b){
			for( ; a != b ; ++a ) push(*a) ;
		}

		Priority_Queue( const vector<T>& f ) {
    		for ( int i = 0 ; i < f.size() ; i++ ) push(f[i]) ;
		 }


		int size() const { return data.size() ; }

		void push( const T& a ){
			data.push_back(a) ;
			reheap_upward( size() - 1 ) ;
		}
/*
		void pushname(const T& a, const S& b){
			data.push_back(a) ;
			name.push_back(b) ;
			reheap_upwardname( size() - 1 ) ;
		}
*/
		T top() const { return data[0] ; }
/*
		void pop(){
			data.front() = data.back() ;
			data.pop_back() ;

			reheap_downward(0) ;
		}
*/
		void print_queue_as_tree( int i , ostream& out ) const {
			if(tree_node(i)){
				print_queue_as_tree(rightson(i),out) ;
				for( int j = 0 ; j < depth(i)-1 ; j++ ) out << "|     " ;
				out << ( i > 0 ? "+---> " : "" ) << data[i].name << "[" << data[i].score << "]" <<  endl ;
				print_queue_as_tree(leftson(i), out) ;
			}
		}

		friend ostream& operator<< (ostream& out , const Priority_Queue& foo ){
			foo.print_queue_as_tree(0,out) ;
			return out << endl ;
		}
} ;

int Strtofloat( string s){
	stringstream ss ;
	float k ;
	ss << s ;
	ss >> k ;
	
	return k ;
}

int main() {
	const int N = 9 , M = 6 ;
//	int no[N] = { 4,7,5,8,9,10,7,6,3} ;

	ifstream infile("score.txt") ;
	string line,name, score , id ;
	//vector<string> namelist ; 
	//vector<float> meanlist ;
	vector<Student> Studentlist ;
	Student stu ;
	istringstream istring ;
	float sum , n;	

//	Priority_Queue<int> a(no,no+N) ;
	while( getline(infile,line) ){
		sum = 0 ;
		n = 0 ;
		istring.str(line) ;
		istring >> id ;
		istring >> name ;
		stu.name = name ;
		while( istring >> score ){
			sum += Strtofloat(score) ;
			++n ;
		}
		stu.score = sum/n ;
		Studentlist.push_back(stu) ;
		istring.clear() ;
	}

	Priority_Queue<Student> a(Studentlist) ;

	cout << "> a = \n" << a << endl ;


	return 0 ;
}
