/*
學號 : 992001525
系級 : 數4B
姓名 : 楊安傑
第_次作業 : 9
編譯環境 : g++ on ubuntu 12.04 LTS
聯絡信箱 : scwuaptx@gmail.com
*/


#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std ;

//define PI
const double PI = 4. * atan(1) ;
//define the class of Point
class Point{
	private :
		double x , y ;
	public :
		//constructor
		Point( double px = 0 , double py = 0 ): x(px),y(py){}

		double getx() const { return x ;}
		double gety() const { return y ;}
		
		//rotate the vector
		Point rotate( double ang ) const {
			Point pt ;
			double ang2 = ang*PI/180 ;
			pt.x = x * cos(ang2) - y * sin(ang2) ;
			pt.y = x * sin(ang2) + y * cos(ang2) ;
			return pt ;
		}

		//output operator
		friend ostream& operator<< ( ostream& out , const Point& pt){
			return out << pt.x << " " << pt.y  ;
		}

};

/*Point operator*/
Point operator+( const Point& pt1 , const Point& pt2 ){
	return Point( pt1.getx()+pt2.getx() , pt1.gety() + pt2.gety() ) ;
}

Point operator-( const Point& pt1 , const Point& pt2 ){
	return Point( pt1.getx()-pt2.getx() , pt1.gety()- pt2.gety() ) ;
}

Point operator/( const Point& pt1 , double c ){
	return Point( pt1.getx()/c , pt1.gety()/c) ;
}

Point operator*( const Point& pt1 , double c ){
	return Point( pt1.getx()*c , pt1.gety()*c ) ;
}

Point operator*( double c , const Point& pt1 ){
	return Point( pt1.getx()*c , pt1.gety()*c ) ;
}

//define the class of Snowflake
class Snowflake{
	private :
		vector<Point> pts ;
		int dep ;
	public :

		//constructor
		Snowflake(Point pt2 = Point(0,0)) {
			Point pt(0,1) ;
			pts.push_back(pt2+pt) ;
			pts.push_back(pt2+pt.rotate(120)) ;
			pts.push_back(pt2+pt.rotate(240)) ;
		}

		//generate the point of flake 
		void generate_pts( int depth , int cdepth ){
			if( depth == cdepth ){
				return ;
			}else{
				vector<Point> q ;
				Point p1 , p2, p3, p4, p5 ;
				for(int  i = 0 ; i < pts.size() ; ++i ){
					p1 = pts[i] ;
					p5 = ( i < pts.size()-1 ? pts[i+1] : pts[0]) ;
					p2 = ( 2*p1 + p5 ) / 3 ;
					p4 = ( p1 + 2*p5 ) / 3 ;
					p3 = p2 + (p4-p2).rotate(-60) ;
					q.push_back(p1) ;
					q.push_back(p2) ;
					q.push_back(p3) ;
					q.push_back(p4) ;
				}
				pts = q ;
				generate_pts(depth,cdepth+1) ;

			}

		}

		//draw the flake
		vector<Point> create( int d ) {		
			generate_pts(d,1) ;
			vector<Point> pts2 = pts ;
			pts2.push_back(pts[0]) ;
			return pts2 ;

		}

} ;

//output operator of vector<Point>
ostream& operator<< ( ostream& out , const vector<Point>& foo){
	for ( int i = 0 ; i < foo.size() ; ++i ) 
		out << foo[i] << "\n" ;
	return out ;
}


int main(void){
	
	int i , j , k, n = 3 ;
	double len = 2.5 ;

	//print the Snowflake 
	for( i = 0 ; i < 2*(n-1) + 1 ; ++i ){
		for( j = 0 ; j < 2*(n-1) + 1  ; ++j ){
			k = max( abs(n-i-1), abs(n-j-1)) ;
			cout << Snowflake(Point(len*(j-n+1),len*(n-1-i))).create(k+1) << endl ;
			cout << endl ;
		}
	}
	
	return 0 ;
}


