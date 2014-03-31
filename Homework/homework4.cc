#include <iostream>
#include <string>
#include <fstream>
#include <set>
#include <vector>
#include <algorithm>

using namespace std ;


int main(void){
	
	locale utf8("zh_TW.UTF-8") ;
	setlocale(LC_ALL,"zh_TW.UTF-8") ;
	wifstream infile("poem2.txt") ; //Read the file of the poem set.
	infile.imbue(utf8) ;
	wstring line ;
	int i ;
	vector< set<wchar_t> > PoemList ;  //Create a list to save poem set
	set<wchar_t>  PoemSet , intersection , temp;  //Create a a set to save the word of poem
	
	//Save every poem in sets.
	while( getline(infile,line) ){
		for( i = 0 ; i < line.size() ; ++i ){
			if( line[i] != L'。' && line[i] !=  L'，' )
				PoemSet.insert(line[i]) ; 
		}
		PoemList.push_back(PoemSet) ;
		PoemSet.clear() ; 
	}
	
	intersection = PoemList[0] ;
	
	//Find the intersection of the sets.
	for( i = 1 ; i < PoemList.size()  ; ++ i ){
		set_intersection(intersection.begin(), intersection.end(), 
				PoemList[i].begin(), PoemList[i].end(),
				inserter(temp,temp.begin())) ;
		intersection = temp ;
		temp.clear() ;
	}

	set<wchar_t>::iterator iter ;

	//Print the intersection of the sets.
	for( iter = intersection.begin() ; iter != intersection.end() ; ++iter ) wcout << *iter << L' ' ;

	wcout << endl ;

	return 0 ;

}
