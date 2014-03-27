Warm
====

These are some execise for the exam on the course.


Warm1
-----

Fraction of calculation and Fraction list

Warm2
-----


There are some code which create a list .

    list<int> no ;
    for ( i = 0 ; i < 4 ; ++i ) no.push_back(i) ;
    for ( i = 2 ; i < 5 ; ++i ) no.push_front(i) ;

Please use iterator and print like that 

	      0
	    2 0 1
	  3 2 0 1 2
	4 3 2 0 1 2 3

Warm3
-----
hanstrokes.txt is a data of strokes of Chinese word, and the unicode of Chinese word is between 19968 and 40869.
(A) Please print out the Chinese word by storkes.

Warm4
-----
There are some code :

	string foo = "be right back in 10 mins" ;
    istringstream istr(foo) ;
    istream_iterator<string> iter(istr) ;

    vector<string> bar ;

    //only save English word 
    copy_if( iter , istream_iterator<string>() , back_inserter(bar) , Eng_Word() ) ;

    //sort by length of word
    stable_sort( bar.begin() , bar.end() , By_Length() ) ;

    //print "be in mins back right"
    copy( bar.begin() , bar.end() , ostream_iterator<string>(cout," ") ) ;

    cout << endl ;

Please complete the program such that can filter the English word and print the word by length of word.
