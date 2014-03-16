#include <iostream>
#include <list>
#include <iomanip>

using namespace std ;

/*Class of Pascal*/
class Pascal {
	private :
		list< list<int> > num ;  //a list of list which collect list of pascal triangle
	
	public :
		Pascal( int n = 0 ){  //The Pascal constrctor
			int i , j ;
			list<int> previous_list ;
			list<int> current_list ;
			list<int>::iterator previous_item ;
			list<int>::iterator current_item ;
			
			num.push_back( list<int>(1,1) ) ; //First element of pascal triangle
			for( i = 0 ; i < n ; ++i ){
				current_list.clear() ;
				current_list.push_back(1) ; //First element of every list of pascal triangle 
				previous_list = num.back() ; //Let Previous_list assign to previous list 
				current_item = previous_list.begin() ; //current item of previous list
				++current_item ; 
				for( previous_item = previous_list.begin() ; previous_item != previous_list.end() && current_item != previous_list.end() ; ++previous_item , ++current_item ){
						current_list.push_back(*previous_item+*current_item) ;
				}
				current_list.push_back(1) ; //Push the final element in the end of every list
				num.push_back(current_list) ;
			}
		} 
	/*Print the pascal triangle method*/
	friend ostream& operator<<( ostream& out , const Pascal& foo ){
			list< list<int> >::const_iterator Pascallist ;  //culomn iterator
			list<int>::const_iterator Pascalelement ; //row iterator

			for( Pascallist = foo.num.begin() ; Pascallist != foo.num.end() ; ++Pascallist ){
				for( Pascalelement = (*Pascallist).begin() ; Pascalelement != (*Pascallist).end() ; ++Pascalelement ){
					out << *Pascalelement << " " ;
				}
				out << endl ;
			}
			return out ;
		}
};


int main(void){

	int n ;
	Pascal pascal ;
	
	while ( 1 ){
		cout << "> " ;
		cin >> n ;
		pascal = Pascal(n) ;
		cout << pascal << endl ;
	}
	
	return 0 ;
}
