#include<iostream>
#include<stack>
#include<string>
#include<sstream>
#include<ctype.h>

using namespace std ;

/*String to int*/
int ChtoInt(char s){
	return s-'0' ;
}


int main(void){
	
	stack<int>  nums ;
	stack<char> optrs ;
	string line;
	istringstream istr ;
	char para ;
	bool flag ;
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
					b = nums.top() ;
					nums.pop() ;
					a = nums.top() ;
					nums.pop() ;
					op = optrs.top() ;
					optrs.pop() ;
					if( op == '+' ){
						c = a + b ;
					}else if( op == '-' ){
						c = a - b ;
					}else if( op == '*'){
						c = a * b ;
					}else if( op == '/'){
						c = a/b ;
					}
					nums.push(c) ;
				}else if( word == '+' || word == '-' || word == '*' || word == '/' ){
					optrs.push(word) ;
				}else if( word == '('){
					continue ;	
				}
			}

		}
		istr.clear() ;
		cout << nums.top() ;
	}


	return 0 ;
}
