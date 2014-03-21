#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
using namespace std ;

bool vowel( char c) {
	return ( c== 'a' || c == 'e' || c == 'i' || c== 'o' || c== 'u') ? true :false ;
}

int main(){

	string code = "dafskjafskjsfbiaouakkkmasljkasafsd" ;
/*serach_n*/
	char c ;
	int i, j, k ;
	bool found = false ;
	for( i = code.size() ; i >= 1 ; --i) {
		for( c = 'a' ; c <= 'z' ; ++c ){
			if ( search_n(code.begin(),code.end(),i,c) != code.end() ){
				found = true ;
				cout << c << "-> " << i << endl ;
			}
		}
		if ( found ) break ;
	}
/*replace*/
	cout << code << endl ;
	replace_if( code.begin() , code.end() , vowel , '-' ) ;
	cout << code << endl ;

	int l ;
	cout << code << endl ;
	l = unique(code.begin(),code.end()) -code.begin() ;
	cout << code.substr(0,l) << endl ;
	
	return 0 ;
}
