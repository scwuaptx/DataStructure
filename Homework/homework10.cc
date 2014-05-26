#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
#include <algorithm>

using namespace std ;

const double SMALL = 1.0e-10 ;

/**the class of complete binary tree**/
template <typename T>
class Complete_Binary_Tree {
	private :

		vector<int> foo ;

		//index of son
		int leftson( int i ) const { return 2 * i + 1 ; } 
		int rightson( int i ) const { return 2 * i + 2 ; }
		
		//index of parent
		int parent( int i ) const { return static_cast<int>((i-1)/2) ; }

		//whether is tree node
		bool tree_node( int i ) const {
			return ( i < foo.size() ? true : false ) ;
		} 

		//depth of tree
		int depth ( int i ) const {
			return static_cast<int>(log(i+1)/log(2)+SMALL) ;
		}
	
		//whether is leaf node
		bool is_leaf_node( int i ) const {
			return ( ! tree_node(leftson(i)) ? true : false ) ;
		}

		//print out the tree
		void print_tree( int i , ostream& out ) const {
			if ( tree_node(i) ) {
				print_tree(rightson(i),out) ;
				for ( int j = 0 ; j < depth(i)-1 ; j++ ) out << "|     " ;
				out << ( i > 0 ? "+---> " : "" ) << foo[i] << endl ; 
				print_tree(leftson(i),out) ;
			}

		}

		public :

			//constructor
			Complete_Binary_Tree( int no[] , int size ) : foo(no,no+size) {}
	
			Complete_Binary_Tree( const vector<int>& no ) : foo(no) {}


			//return the max value of the subtree
			T maximum(int i = 0){
				if(tree_node(i)){
					if(!is_leaf_node(leftson(i)))
						return max(maximum(rightson(i)),maximum(leftson(i))) ;
					else if(!tree_node(rightson(i)))
						return foo[leftson(i)] ;
					else
						return max(max(foo[leftson(i)],foo[rightson(i)]),foo[i]) ;
				}
			}

			//show the max value on the node 
			void maxsubtree( int i = 0){
				if(tree_node(i)){
					if(!is_leaf_node(leftson(i)) && !is_leaf_node(rightson(i))){
						maxsubtree(leftson(i)) ;
						maxsubtree(rightson(i)) ;
					}
					if(foo[i] < maximum(i))
						foo[i] = maximum(i) ;

				}
			}

			//the size of the tree
			int size() const { return foo.size() ; } 

			//output operator
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

	//original tree
	cout << "The tree : \n" << cbtree << endl ;

	cbtree.maxsubtree() ;
	
	cout << "max：\n" << cbtree << endl ;

	return 0 ;
}
