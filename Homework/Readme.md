Homework1
---------

There are some code :

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
Please design the algorithm named print_words() and the functor class named WordSize()

Homework2
---------
There are some code :
	
	#include <iostream>
	#include <list>
	#include <iomanip>

	using namespace std ;
	
	class  Pascal {
		private :
			list< list<int> >  num ;

		public :
			Pascal( int n = 0 ) {
		// complete the block
		...
		}
	friend ostream& operator<<( ostream& out , const Pascal& foo ) {
		// complete the block
		...
		}
	};

	int main() {

    int  n ;
    Pascal  pascal ;

    while ( 1 ) {
        cout << "> " ;
        cin >> n ;
        pascal = Pascal(n) ;
        cout << pascal << endl ;
    }

    return 0 ;

	}

Please complete the block and not use vector, deque and array.
Let it can print out a pascal triangle.

Ex:

input :

	4

output :

	1
	1   1
	1   2   1
	1   3   3   1

Homework3
---------

Reference to the third Problem in http://www.ziyou.math.ncu.edu.tw/~ziyou/c++/

Homework4
---------

Reference to the fifth Problem in http://www.ziyou.math.ncu.edu.tw/~ziyou/c++/

Homework5
---------
There are some code :

	Pascal  foo ;
	while ( 1 ) {
	   cin >> n ;
	   foo.reset(n) ;
	   cout << foo << endl ;
	}

Design a class of Pascal to complete the program.

Homework6
---------

Design a class of List which include sort(Comp cp) such that it can sort element of list.

For example :

	foo.sort() ;  //from small to big
	cout << wsetw(4) << foo << endl ;  // print the element of list
	foo.sort( large_first() ) ;  // from big to small
	cout << wsetw(4) << foo << endl ;


Homework7
---------

Design the function of infix to postfix and calculate the value of formula which is Fraction.

Homework8
---------

Design a program which simulate the parking lot with two entrances in a day.
