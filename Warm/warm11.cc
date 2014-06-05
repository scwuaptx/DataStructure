#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <iterator>
#include <iomanip>
#include <algorithm>

using namespace std ;

// 字串 key 轉整數
int  to_int( const string & key ) {
    int  no = 0 ;
    for ( int i = 0 ; i < key.size() ; ++i ) {
        no += static_cast<int>(key[i]) ;
    }
    return no ;
}


// 整數 key 轉整數
int  to_int( const int& key ) {
    return  key ;
}


// hash table use quadratic probing
template <typename T>
class  Chained_Hash {
  private :

    vector< list<T> >       ptrs ;       // 資料
	int             listsize ;

    // hash 函數
    int  hash( const T& key ) const { 
        return  to_int(key) % listsize ;
    }

  public :
    
    // 建構函式
    Chained_Hash( const int s ) 
        :  listsize(s) {
			int i ;
			list<T> a ;
			for( i = 0 ; i < s ; ++i ){
				ptrs.push_back(a) ;
			}
		}

	T size() { return listsize ; }


    // 搜尋 key
    bool  findelement( const T& key ) const {

        int  i ;
        i = hash(key) ;
		if( find(ptrs[i].begin(),ptrs[i].end(), key) != ptrs[i].end() ){
			return true ;
		}else{
    	    return  false ;
		}
    }
   

    // 插入 key
    bool  insert( const T& key ) {
        int i ;
        i = hash(key) ;
		ptrs[i].push_back(key) ;		
        return  true ;
        
    }


    // 刪除 key
    bool  erasekey( const T& key ) {
        
        int  i ;
        i = hash(key) ;
     	if( findelement(key) ){
			ptrs[i].erase(find(ptrs[i].begin(),ptrs[i].end(),key)) ;
			return true ;
		}else{
			return false ;
		}
        
    }


    // 清除 hash table
    void  clear() {
		listsize = 0 ;
		while( ptrs.size() > 0) ptrs.pop() ;
    }
  


    // 列印 hash_table
    friend ostream&  operator<<( ostream& out , const Chained_Hash& foo ) {
		vector< list<int> >::const_iterator iter1 ;
		list<int>::const_iterator iter2 ;
		int i ;        

		for ( iter1 = foo.ptrs.begin() ; iter1 != foo.ptrs.end() ; ++iter1 ) {
			if( (*iter1).size() > 0 ){
				i = 1 ;
				for( iter2 = (*iter1).begin() ; iter2 != (*iter1).end() ; ++iter2 , ++i ){
					if(i < (*iter1).size() )
						out << *iter2 << " -> " ;
					else
						out << *iter2 ;
					
				}
				out << endl ;
			}else{
				out << " - " << endl ;
			}
        }
        out << endl ;
        return out ;
    }
            
};



int main() {

	const int S = 14 ;
	int no[S] = { 18 , 3 , 21 , 7 , 11 , 20 , 8 ,
              39 , 33 , 56 , 36 , 13 , 25 , 23 } ;

	int n ;
    // 整數 hash table
    Chained_Hash<int>  foo(10) ;

    for ( int i = 0 ; i < S ; ++i ) foo.insert(no[i]) ;

	while(1){
	    cout << foo ;
		cout << "> " ;
		cin >> n ;
		if(foo.findelement(n)){
			cout << "element is found" << endl ;
			foo.erasekey(n) ;
			cout << "element be erase" ;
		}else{ 
			cout << "element not found" << endl ;
		}
	}
    return 0 ;

}
