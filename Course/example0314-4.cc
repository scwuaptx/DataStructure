#include <iostream>
#include <fstream>
#include <map>
using namespace std ;

class Exam {
	private :
		map<int,int> score ;
	public :
		Exam(const string& fn) {
			int n ;
			ifstream infile(fn.c_str()) ;
			while ( infile >> n ) score[n] += 1 ;
		}

		int score_no(int a , int b) const {
			map<int,int>::const_iterator iter ;
			int total = 0 ;
			for ( iter = score.begin() ; iter != score.end() ; ++iter ){
				if( iter->first >= a && iter->first <= b ){
					total += iter->second ;
				}
			}
		return total ;
		}

};

int main(void){

	Exam foo("score.dat") ;
	int a,b ;
	while(1){
		cout << "> " ;
		cin >> a >> b ;
		cout << "> total: " << foo.score_no(a,b) << endl;
		
	}
	return 0 ;
}
