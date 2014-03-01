Homework1
---------
	There are some code :
	<code>int n = 4;
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
		} while(1);</code>
Please design the algorithm named print_words() and the functor class named WordSize()
	
