#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
using namespace std ;

//GCD function
int GCD( int a , int b ){
	a = abs(a) ;
	b = abs(b) ;	
    if( a == 0 )
        return 1 ;
    if( a >= b )
        return a % b == 0 ? b : GCD( b , a % b ) ;
    else
        return b % a == 0 ? a : GCD( a , b % a ) ;

}

/*--Define Fraction Struct--*/
//constructor
struct Fraction{
        int num , den ;
        Fraction( int n = 0, int d = 1 ): num(n/GCD(n,d)), den(d/GCD(n,d)) {
		if( d < 0 ){ num *= -1 ; den *= -1 ;}
		} ;
} ;

//output operator of Fraction
ostream& operator<< ( ostream& out ,const Fraction& foo ){
    return out << foo.num << '/' << foo.den ;
}

//+ operator of Fraction
Fraction operator+ ( const Fraction& a , const Fraction& b ){
    int newden = a.den * b.den ;
    int newnum = a.num * b.den + a.den * b.num ;
    return Fraction(newnum,newden) ;
}

//- operator of Fraction
Fraction operator- ( const Fraction& a , const Fraction& b){
    int newden = a.den * b.den ;
    int newnum = a.num * b.den - a.den * b.num ;
    return Fraction( newnum , newden ) ;
}

//* operator of Fraction
Fraction operator* ( const Fraction& a , const Fraction& b ){
    return Fraction( a.num * b.num , a.den * b.den ) ;
}

// / operator of Fraction
Fraction operator/ ( const Fraction& a , const Fraction& b ){
    return Fraction( a.num * b.den , a.den * b.num ) ;
}


/*--Infix to Postfix--*/
string Infix2Postfix(string& str){
	
	string word  ;
	stack<string> optrs ; //create a stack to save operator
	stack<int> priority ; //create a stack to save priority of operator
	int optrpri ;
	istringstream istr ;
	ostringstream ostr ;
	istr.str(str) ;
	
	while( istr >> word ){
		//determine whether is operator
		if( word.find_first_of("0123456789") == string::npos ){
			if( !optrs.empty() ){
					optrpri = priority.top() ;
					if( word == "+" || word == "-" ){
						while( optrpri >= 1 && !optrs.empty() ){
							ostr << optrs.top() << " " ;
							optrs.pop() ;
							priority.pop() ;
							if( !optrs.empty() )
								optrpri = priority.top() ;
						}
						optrs.push(word) ;
						priority.push(1) ;
					}else if( word == "(" ){
						priority.push(0) ;
						optrs.push(word) ;
					}else if( word == "*" || word == "/" ){
						while( optrpri >= 2 && !optrs.empty() ){
							ostr << optrs.top() << " " ;
							optrs.pop() ;
							priority.pop() ;
							if( !optrs.empty() )
								optrpri = priority.top() ;
						}
						optrs.push(word) ;
						priority.push(2) ;
					}else{
						while( optrs.top() != "(" ){
							ostr << optrs.top() << " " ;
							optrs.pop() ;
							priority.pop() ;
						}	
						if ( optrs.top() == "(" ){
							optrs.pop() ;
							priority.pop() ;
						}else{
							continue ;
						}
					}
				
	
			}else{
				if( word == "+" || word == "-" ){
					priority.push(1) ;
				}else if( word == "*" || word == "/" ){
					priority.push(2) ;
				}else if( word == "(" ){
					priority.push(0) ;
				}else{
					priority.push(4) ;
				}
				optrs.push(word) ;
			}
		}else{ 
			ostr << word << " " ;
		}

	}

	while(!optrs.empty()){
		ostr << optrs.top() << " " ;
		optrs.pop() ;
		priority.pop() ; 
	}
	
	//return the postfix
	return ostr.str() ; 
}

//string to number
template<typename T>
T Str2Num(string str){
	stringstream ss ;
	T k ;
	ss << str ;
	ss >> k ;
	
	return k ;
}

//string to fraction
Fraction Str2Frac(string& str){
	int i , a , b;
	ostringstream ss ;
	if(str.find_first_of("/") == string::npos){
		a = Str2Num<int>(str) ;
		b = 1 ;
	}else{
		for(i = 0 ; str[i] != '/' ; ++i ){
			ss << str[i] ;
		}
		++i ;
		a = Str2Num<int>(ss.str()) ;
		ss.str("") ;
		for(; str[i] != '\0' ; ++i){
			ss << str[i] ;
		}
		b = Str2Num<int>(ss.str()) ;
	}	
	return Fraction(a,b) ;
}

//Calculate the postfix of fraction
template<typename T>
T CalPostfix(string str){

	stack<T> nums ;
	istringstream istr ;
	string word ;
	T a,b,no;	
	istr.str(str) ;

	while( istr >> word ){
		//if word is number then save to stack
		if( word != "+" && word != "-" && word !="*" && word != "/" ){
			nums.push(Str2Frac(word)) ;
		}else{
			a = nums.top() ;
			nums.pop() ;
			b = nums.top() ;
			nums.pop() ;

			if( word == "+" ){
				no = b + a ; 
			}else if( word == "-" ){
				no = b - a ;
			}else if( word == "*" ){
				no = b * a ;
			}else{
				no = b / a ;
			}
			nums.push(no) ;
		}

	}
	//return the result of postfix of fraction
	return nums.top() ;
}



int main(void){
	
	string line ;
	cout << "> " ;
	getline(cin,line) ;
	cout << Infix2Postfix(line) << endl ;
	cout << CalPostfix<Fraction>(Infix2Postfix(line)) << endl ;

	return 0 ;
}
