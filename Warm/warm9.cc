#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std ;

const double SMALL = 1.0e-10 ;

template <typename T>
class Complete_Binary_Tree {
	private :

		vector<int> foo ;

		int leftson( int i ) const { return 2 * i + 1 ; } 
		int rightson( int i ) const { return 2 * i + 2 ; }
		
		int parent( int i ) const { return static_cast<int>((i-1)/2) ; }

		bool tree_node( int i ) const {
			return ( i < foo.size() ? true : false ) ;
		} 

		int depth ( int i ) const {
			return static_cast<int>(log(i+1)/log(2)+SMALL) ;
		}

		bool is_leaf_node( int i ) const {
			return ( ! tree_node(leftson(i)) ? true : false ) ;
		}

		void print_tree( int i , ostream& out ) const {
			if ( tree_node(i) ) {
				print_tree(rightson(i),out) ;
				for ( int j = 0 ; j < depth(i)-1 ; j++ ) out << "|       " ;
				out << ( i > 0 ? "+--->   " : "" ) << foo[i] << endl ; 
				print_tree(leftson(i),out) ;
			}

		}

		void print_subtree_sum( int i , ostream& out ) const {
			if ( tree_node(i) ){
				print_subtree_sum(rightson(i),out) ;
				for( int j = 0 ; j < depth(i)-1 ; j++ ) out << "|" ;
				out << ( i > 0 ? "+--->" : "" ) << subtree_sum(i) << endl ;
				print_subtree_sum(leftson(i),out) ;
			}
		}

		void subtree_nodes( int i , vector<int>& bar ) const {
			if( tree_node(i) ){
				bar.push_back(i) ;
				if ( tree_node(leftson(i))) subtree_nodes(leftson(i),bar) ;
				if ( tree_node(rightson(i))) subtree_nodes(rightson(i),bar) ;

			}
		}

		public :

			Complete_Binary_Tree( int no[] , int size ) : foo(no,no+size) {}
	
			Complete_Binary_Tree( const vector<int>& no ) : foo(no) {}


			Complete_Binary_Tree subtree( int k ) const {
				vector<int> no ;
				subtree_nodes(k,no) ;
				sort(no.begin(),no.end()) ;
				vector<int> num(no.size()) ;
				for( int i = 0 ; i < num.size() ; ++ i ) num[i] = foo[no[i]] ;
				return Complete_Binary_Tree(num) ;
			}

			string print_subtree_sum( int i = 0 ) const {
				ostringstream ostr ;
				print_subtree_sum(i,ostr) ;
				return ostr.str() ;
			}

			void swap_nodes( int i = 0 ){
				if ( tree_node(i) ){
					if (tree_node(rightson(i))){
						swap(foo[leftson(i)],foo[rightson(i)]) ;
					}
					swap_nodes(rightson(i)) ;
					swap_nodes(leftson(i)) ;
				}
			}

			T subtree_sum( int i = 0 ) const {
				if ( ! tree_node(i) ){
					return T(0) ; 
				}else{
					return foo[i] + subtree_sum(leftson(i)) + subtree_sum(rightson(i)) ;
				}
			}

			T leaf_sum( int i = 0 ) const {
				if ( ! tree_node(i) ) {
					return T(0) ;
				}else{
					if( is_leaf_node(i) ){
						return foo[i] ;
					}else{
						return leaf_sum(leftson(i)) + leaf_sum(rightson(i)) ;
					}
				}
			}

			T odd_sum( int i = 0 ) const {
				if ( ! tree_node(i) )  {
					return  T(0) ;
				}else{
					if ( foo[i] % 2 )
						return foo[i] + odd_sum(leftson(i)) + odd_sum(rightson(i)) ;
					else
						return odd_sum(leftson(i)) + odd_sum(rightson(i)) ; 
				}	
			}

			T between_sum( int a , int b , int i = 0 ) const {
				if (! tree_node(i) ){
					return T(0) ; 
				} else {
					if ( foo[i] >= a && foo[i] <= b ) {
						return foo[i] + between_sum(a,b,rightson(i)) + between_sum(a,b,leftson(i)) ;
					}else {
						return between_sum(a,b,rightson(i)) + between_sum(a,b,leftson(i)) ;
					}
				}
			}

			T rightson_sum ( int i = 0 ) const {
				if( ! tree_node(i) ){
					return T(0) ;
				}else{
					if( i > 0 && rightson(parent(i)) == i ){
						return foo[i] + rightson_sum(rightson(i)) + rightson_sum(leftson(i)) ;
					}else{
						return rightson_sum(rightson(i)) + rightson_sum(leftson(i)) ;
					}
				}
			}

			void parentbig( int i = 0 ){
				if(tree_node(i) && i > 0 ){
					if(foo[parent(i)] < foo[i]){
						swap(foo[parent(i)],foo[i]) ;
					}
					parentbig(parent(i)) ;
				}


			}

			void rearrange( int i = 0 ){
				if(tree_node(i)){
					for( int j = i+1  ; j <= foo.size() - i ; j++ ){
						parentbig(j) ;
					}
				}
			}

			int size() const { return foo.size() ; } 

			template <class S>
			friend ostream& operator<< ( ostream& out , const Complete_Binary_Tree<S>& foo ){
				foo.print_tree(0,out) ;
				return out ;
			}

} ;

int main(void){

	const int s = 10 ;
	int no[s] = { 2 , 3, 1 ,8 , 7 , 4 , 9 , 6 , 5 , 3 } ; 

	Complete_Binary_Tree<int> cbtree( no , s ) ;

	cout << "The tree : \n" << cbtree << endl ;

	cbtree.rearrange() ;
	
	cout << "Rearrange：\n" << cbtree << endl ;

	return 0 ;
}
