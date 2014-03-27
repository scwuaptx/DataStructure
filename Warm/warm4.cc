#include <iostream>
#include <iterator>
#include <list>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <ctype.h>

using namespace std ;

/*copy_if()*/
template<class InIter,class OutIter , class UnaryPredicate >
OutIter copy_if( InIter start , InIter end , OutIter result , UnaryPredicate pred ){
	while( start != end ) {
		if (pred(*start)) {
			*result = *start ;
			++result ;
		}
		++start ;
	}
	return result ;
}

/*
struct Eng_Word{
	bool operator() (const string& str){
		stringstream ss(str) ;
		int k ;
		ss >> k ;
		if(!ss) return true ;
		return false ;
	}
} ;
*/

/*check string is English word*/
struct Eng_Word{
	bool operator() (const string& str){
		for( int i = 0 ; i < str.size() ; ++i ){
			if( !isalpha(str[i]) ) return false ; 
		}
		return true ;
	}
} ;

/*compare the size of string*/
struct By_Length{
	bool operator() ( const string& strA, const string& strB ){
		return strA.size() <  strB.size() ;
	}
} ;

int main(void) {

	string foo = "be right back in g10 mins" ;
	istringstream istr(foo) ;
	istream_iterator<string> iter(istr) ;

	vector<string> bar ;
	
	//only save English word 
	copy_if( iter , istream_iterator<string>() , back_inserter(bar) , Eng_Word() ) ;
	
	//sort by length of word
	stable_sort( bar.begin() , bar.end() , By_Length() ) ;

	//print "be in mins back right"
	copy( bar.begin() , bar.end() , ostream_iterator<string>(cout," ") ) ;
	
	cout << endl ;

	return 0 ;
}
