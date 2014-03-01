#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

class WordSize {	//The class of WordSize.
	private :
		int num ;
	public :
		WordSize(const int& n = 0) : num(n) {}		//Constructor
		//If the size of str inputed by the user greater than numi, than return ture.
		bool operator() ( const string& str ) const {	
			return str.size() >= num ;						
		}
};

template < class S , class T >
void print_words(S start , S end , T WordSize){
		for ( S i = start ; i != end ; ++i){
			//If the size of input is greater than num, than print the string
			if(WordSize(*i))
				cout << *i << ' ';
		}
		return ;
}

int main(void){

	int n = 4;
	string line , word ;
	istringstream istr ;
	vector<string> strs ;
	
	do{
		cout << "> " ;
		getline(cin ,line) ;
		istr.str(line) ;
		while ( istr >> word ) strs.push_back(word);
		istr.clear() ;
		//Print the string that the size of the string greater than n in the string list.
		print_words( strs.begin() , strs.end() , WordSize(n) ) ;
		strs.clear() ;
	} while(1);


}
