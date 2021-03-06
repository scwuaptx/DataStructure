#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std ;

const double PI = 4. * atan(1) ;
class Point{
	private :
		double x , y ;
	public :
		Point( double px = 0 , double py = 0 ): x(px),y(py){}

		double getx() const { return x ;}
		double gety() const { return y ;}

		Point rotate( double ang ) const {
			Point pt ;
			double ang2 = ang*PI/180 ;
			pt.x = x * cos(ang2) - y * sin(ang2) ;
			pt.y = x * sin(ang2) + y * cos(ang2) ;
			return pt ;
		}

		friend ostream& operator<< ( ostream& out , const Point& pt){
			return out << pt.x << " " << pt.y  ;
		}

};

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

class Snowflake{
	private :
		vector<Point> pts ;
		int dep ;
	public :

		Snowflake(Point pt2 = Point(0,0)) {
			Point pt(0,1) ;
			pts.push_back(pt2+pt) ;
			pts.push_back(pt2+pt.rotate(120)) ;
			pts.push_back(pt2+pt.rotate(240)) ;
		}


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


		vector<Point> create( int d ) {		
			generate_pts(d,1) ;
			vector<Point> pts2 = pts ;
			pts2.push_back(pts[0]) ;
			return pts2 ;

		}

} ;

ostream& operator<< ( ostream& out , const vector<Point>& foo){
	for ( int i = 0 ; i < foo.size() ; ++i ) 
		out << foo[i] << "\n" ;
	return out ;
}


int main(void){
	
	int i ;

	for ( i = 1 ; i <= 5  ; ++i){
		cout << Snowflake(Point(2*i,1)).create(i) << endl ;
		cout << endl ;
	}

	return 0 ;
}


