#include<iostream>
#include<stack>
#include<string>
#include<sstream>
#include<ctype.h>

using namespace std ;

/*char to int*/
int ChtoInt(char s){
	return s-'0' ;
}


int main(void){
	
	stack<int>  nums ;
	stack<char> optrs ;
	string line;
	ostringstream ostr ;
	istringstream istr ;
	char para ;
	int no , a, b, c;
	char op ,word;

	while(1){
		cout << "> " ;
		getline( cin , line ) ;
		istr.str(line) ;

		while( istr >> word ){	
			if(isdigit(word)){
				nums.push(ChtoInt(word)) ;
			}else{
				if( word == ')'){
					if(!nums.empty()){
						if(nums.size() > 1){
							b = nums.top() ;
							nums.pop() ;
							a = nums.top() ;
							nums.pop() ;
							ostr << a << " " << b  << " " ;
						}else{
							a = nums.top() ;
							nums.pop() ;
							ostr << a << " " ;
						}
					}
					op = optrs.top() ;
					optrs.pop() ;

					ostr << op << " " ;
				}else if( word == '+' || word == '-' || word == '*' || word == '/' ){
					optrs.push(word) ;
				}else if( word == '('){
					continue ;	
				}
			}

		}
		istr.clear() ;
		cout << ostr.str() << endl ;
		ostr.str("") ;
	}


	return 0 ;
}
