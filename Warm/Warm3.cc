#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
using namespace std ;

int UStrtoInt(string s){
	stringstream ss(s) ;
	string n ;
	istringstream is ;
	int k ;
	while( getline(ss,n,'+') ){
		if( n != "U"){
			is.str(n) ;
			is >> hex >> k ;
		}
	}
	return k ;
}

int StrtoInt(string s){
	stringstream ss ;
	int k ;
	ss << s ;
	ss >> k ;
	
	return k ;
}

int main(void){

	locale utf8("zh_TW.UTF-8") ;
	setlocale(LC_ALL,"zh_TW.UTF-8") ;
    ifstream infile("han_strokes.txt") ;
	string line,word,num  ;
	istringstream istring ;

	multimap<int,int> StroketoWord ;
	multimap<int,int> WordtoStroke ;
	multimap<int,int> SumtoStroke ;

	while ( getline(infile,line) ) {
		istring.str(line) ;
		istring >> word ;
		if ( word != "#" && UStrtoInt(word) >= 0x4E00 && UStrtoInt(word) <= 0X9FA5 ) {
			if ( istring >> num ) {
				if ( num == "kTotalStrokes" ){
					istring >> num ;
					StroketoWord.insert(make_pair(StrtoInt(num),UStrtoInt(word))) ;
					WordtoStroke.insert(make_pair(UStrtoInt(word),StrtoInt(num))) ;
				}
			}
		}
		istring.clear() ;
	}
	
	typedef multimap<int,int>::iterator mmiter;
	mmiter iter ;
	multimap<int,int>::reverse_iterator riter ;
	pair<mmiter,mmiter> piter ;

	int i,j,value,sum;
	for ( i = 1 ; i <= 30 ; ++i) {
		wcout <<  i << L" 劃 :" << StroketoWord.count(i) << endl ; 
		piter = StroketoWord.equal_range(i) ;
		j = 0 ;
		sum = 0 ;
		for ( iter = piter.first ; iter!=piter.second ; ++iter){
			j++ ;
			value = iter->second ;
			wcout << *reinterpret_cast<wchar_t*>(&value) ;
			if ( j%25 == 0 ) wcout << endl ; 
		}
		wcout << endl ;
		SumtoStroke.insert(make_pair(StroketoWord.count(i),i)) ;
	}

	for  ( riter = SumtoStroke.rbegin() ; riter != SumtoStroke.rend() ; ++riter ){	
		wcout << riter->second  << L" : " << riter->first << endl ;	
	}

	return 0 ;

}
