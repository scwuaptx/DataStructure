#include <iostream>
#include <vector>
#include <deque>
#include <list>

using namespace std;

int main(){

	int i,j;
	deque<int> a ;          //initial a which is a deque

	for ( i = 0 ; i < 10 ; ++i) a.push_back(i) ; //add a element at the end of a

	for ( i = 0 ; i < a.size() ; ++i){   //print  a
		cout << a[i] << endl;
	}

	list<int> b ;			//initial b which is a list

	b.push_back(3) ;		//add a element at the end of b
	b.push_back(8) ;		// b = 3 8
	b.push_front(5) ;		//add a element at the front of b
	b.push_front(7) ;		// b = 7 5 3 8
	b.pop_front() ;			//remove the element at front of b
	b.pop_back() ;			//remove the element at end of b
	b.front() = 9 ;			//change the value which at the front of b
	cout << b.front() << ' ' << b.back() << endl ;

	return 0;

}
