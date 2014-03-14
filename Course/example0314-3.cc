#include <iostream>
#include <set>
#include <map>
#include <sstream>
#include <string>
using namespace std ;

struct myless {
	bool operator() ( int i , int j ) const {
		return i/10 < j/10 ;
	}
} ;

int main(void){

	/*iterator of multiset*/
	
	char a[4] = { 'b' , 'o' , 'r' , 'g'  } ;
	multiset<char> b(a,a+4) ;

	multiset<char>::iterator i = b.begin() ;
	for ( ; i != b.end() ; ++i ) cout << *i << ' ' ;


	multiset<char>::reverse_iterator j = b.rbegin() ;
	for ( ; j != b.rend() ; ++j ) cout << *j << ' ' ;
	
	cout << endl ;

	/*insert element in set*/
	set<int> foo ;
	typedef set<int>::iterator SetIter ;
	pair< SetIter , bool > x ;
	SetIter y ;

	foo.insert(9) ;
	foo.insert(5) ;
	x = foo.insert(3) ;
	foo.insert(x.first,8) ;

	int no[5] = { 9 , 2 , 5 , 7 , 3} ;
	foo.insert( no , no+5 ) ;

	for( y = foo.begin() ; y != foo.end() ; ++y ) cout << *y << ' ' ;
	
	cout << endl ;

	/*search element and interval*/
	int n,noo[10] = {88,78,80,65,73,90,75,50,80,69} ;
	typedef multiset<int,myless> SetType ;
	typedef SetType::iterator SetIter ;

	SetType fooo(noo,noo+10) ;
	SetIter k ;
	pair<SetIter,SetIter> m ;
	
	
	cin >> n ;
	cout << "->" ;
	m = fooo.equal_range(n) ;
	if ( m.first != m.second )
		for ( k = m.first ; k != m.second ; ++k ) cout << *k << ' ' ;
	else
		cout << " not found" ;
	cout << endl ;
	

	/*map search*/
	string composers = "Vialdi Handel Bach Haydn Mozart Beethoven "
					   "Schubert Berlioz Weber Mendelssohn Chopin "
					   "Schumann Liszt Bramhs Bruchs Tchaikovsky " ;
	multimap<char,string> collection ;
	string name ;
	istringstream  istr(composers) ;
	
	while( istr >> name ) collection.insert( make_pair(name[0],name) ) ;
	typedef multimap<char,string>::iterator mmiter ;
	char letter ;
	mmiter iter ;
	pair<mmiter,mmiter> piter ;

	while(1) {
		cout << "> Enter a big letter" << endl ;
		cin >> letter ;
		piter = collection.equal_range(letter) ;
		for ( iter = piter.first ; iter != piter.second ; ++iter )
			cout << iter->second << " " ;
		cout << endl ;
	}

	return 0 ;

}
