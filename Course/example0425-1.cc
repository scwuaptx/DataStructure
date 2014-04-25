#include <iostream>
#include <string>
#include <sstream>
#include <stack>

using namespace std ;

int main(void){
	stack<char> foo ;
	istringstream istr ;
	string line ;
	char para ;
	bool flag ;

	while(1){
		cout << "> " ;
		getline( cin , line ) ;
		istr.str(line) ;
		flag = false ;
		while( istr >> para ){
			if( para == '(' ){
				foo.push(para) ;
			}else if( para == ')' ){
				if(foo.empty()){
					flag = true ;
					break ;
				}else{
					foo.pop() ;
				}
			}else{

			}
		}

		istr.clear() ;

			if( !foo.empty() || flag ){
				cout << "> not balanced\n" ;
				while(!foo.empty()) foo.pop() ;
			}else if( !flag ){
				cout << "> balaced\n" ;
			}
		}
	


	return 0 ;
}
