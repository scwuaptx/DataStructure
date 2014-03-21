#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <iomanip>

using namespace std ;

int main(void){

	locale utf8("zh_TW.UTF-8") ;
	setlocale(LC_ALL,"zh_TW.UTF-8") ;
	wifstream infile("poem.txt") ;
	infile.imbue(utf8) ;
	wstring line ;
	int i , UniofWord , Space = 20;
	map<int,int> word ;  //Create a unicode to number map

	while( getline(infile,line) ) {
		//if line is not empty ,then print the line of word 
		if( line.size() != 0)
			wcout << line ;	
		//typesetting
		for ( i = 0 ; i <= Space-line.size() ; ++i )
			wcout << L"  " ;
		wcout << L" | " ;
		
		//if the Chinese word has been appear greater two times , then print the Chinese word and times.
		for ( i = 0 ; i < line.size() ; ++i ){
			UniofWord = *reinterpret_cast<int*>(&line[i]) ;
			if( UniofWord!= 12290 && UniofWord!= 65292 && UniofWord!= 65218 )  //skip "。" "，" "！"
				word[UniofWord] += 1 ;
			if( word[UniofWord] >= 2)
				wcout  << *reinterpret_cast<wchar_t*>(&UniofWord) << L"[" << word[UniofWord] << L"]" ;
		}	
		wcout << endl ;
	}


	return 0 ;
}
