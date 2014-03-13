/*list iterator*/
#include <iostream>
#include <list>
using namespace std;


int main(void){
	
	/*Creat a int list*/
	int i , j ;
	list<int> no ;
	for ( i = 0 ; i < 4 ; ++i ) no.push_back(i) ;
	for ( i = 2 ; i < 5 ; ++i ) no.push_front(i) ;

	/*declare the iterator*/
	list<int>::iterator iter ;

	/*Print the triangle of the list*/
	for ( i = 3 ; i >= 0 ; --i ){
		j = 0 ;
		for ( iter = no.begin()  ; iter != no.end()  ; ++iter ){
			if ( j >= i && j < no.size()-i )
				cout << *iter << ' ' ;
			else 
				cout << ' ' << ' ' ;
			++j ;
		}
		cout << endl ;
	}
	return 0 ;	

}
