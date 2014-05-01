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

void Reverse(string &str){
	int i ;
	char temp ;
	
	for( i = 0 ; i < str.length() /2 ; ++i ){
		temp = str[i] ;
		str[i] = str[str.length()-i-1] ;
		str[str.length()-i-1] = temp ;
	}

}


int main(void){
	
	stack<int>  nums ;
	stack<char> optrs ;
	string line,result;
	ostringstream ostr ;
	istringstream istr ;
	char para ;
	int no , a, b, c;
	char op ,word;

	while(1){
		cout << "> " ;
		getline( cin , line ) ;
		Reverse(line) ;
		istr.str(line) ;
	/* infix to prefix */
		while( istr >> word ){	
			if(isdigit(word)){
				ostr << word << " " ;
			}else{
				if( word == '('){
					do{
						op = optrs.top() ;
						optrs.pop() ;
						if( op != ')')
							ostr << op << " " ;
					} while( op != ')') ;

				}else if( word == '+' || word == '-' || word == '*' || word == '/' ){
					optrs.push(word) ;
				}else if( word == ')'){
					optrs.push(word) ;	
				}
			}

		}
		istr.clear() ;
		result = ostr.str() ;
		Reverse(result) ;
		cout << "Prefix : " <<result << endl ;
		ostr.str("") ; //clean up the ostr
	
	/* calculate prefix */
		Reverse(result) ; // input of prefix
		istr.str(result) ;
		while( istr >> word ){
			if(isdigit(word))
				nums.push(ChtoInt(word)) ;
			else{
				b = nums.top() ;
				nums.pop() ;
				a = nums.top() ;
				nums.pop() ;
	
				if( word == '+' ){
					no = b + a  ;		
				}else if( word == '-' ){
					no = b - a ;
				}else if( word == '*' ){
					no = b * a ;
				}else{
					no = b / a ;
				}
				
				nums.push(no) ;
			}

		
		}
		cout << "Ans : " << nums.top() << endl ;
		nums.pop() ;
		istr.clear() ;
	}


	return 0 ;
}
