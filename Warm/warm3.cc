#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <iomanip>
using namespace std ;


/*Hex String to int*/
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

/*String to int*/
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

/*Read the Data*/
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

/*Print the chinese word of every strokes*/
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

/*Sort with strokes*/
	for  ( riter = SumtoStroke.rbegin() ; riter != SumtoStroke.rend() ; ++riter ){	
		wcout << setw(4) << riter->second  << L" 畫 : " <<  setw(4) <<riter->first << L" 個" << endl ;	
	}

	return 0 ;

}
