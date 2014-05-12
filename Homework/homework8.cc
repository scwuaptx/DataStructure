#include <iostream>
#include <cmath>
#include <queue>
#include <deque>
#include <iomanip>
#include <cstdlib>
#include <ctime>

using namespace std ;
/*Parking Simulation*/

//the probability of arrival of the car
class Car_Arrival{
	private :
		double probability ; 
	public :
		Car_Arrival( double p ) : probability(p){
			srand( static_cast<unsigned>(time(NULL))) ;
		}

	//whether is car coming
	bool is_arrival() const { return ( rand() < probability * RAND_MAX ) ; }
} ;

int random_no( int a , int b ) { return rand()%(b-a+1) + a ; }

//class of car
class Car {
	private :

		int wtime ;
		int in_time ;
		int out_time ;

	public :
		Car() {}

		//The car which needn't to wait
		Car( int in , int parking_min ) :
			wtime(in) , in_time(in) , out_time(in+parking_min) {}

		//The car which need to wait
		Car( int wt , int in , int parking_min ) :
			wtime(wt) , in_time(in) , out_time(in+parking_min) {}
	
		//Time of waiting to park 
		int waiting_time() const { return in_time - wtime ; }

		//Time of parking
		int parking_time() const { return out_time - in_time ; } 
		
		//The time of drive out the park
		int drive_out() const { return out_time ; }
		
		//The time of drive in the park
		int drive_in() const { return in_time ; } 

		friend struct Drive_Out_Earlier ;
} ;


//Compare the car leaving the parking lot of the time
struct Drive_Out_Earlier {
	bool operator()( const Car& a , const Car& b ) const {
		return a.out_time > b.out_time ;
	}

} ;

//Class of Parking lot , FEE is the cost in a minute,
template <int FEE>
class Parking_Lot{
	private :
		int max_parking_no ;	//max of number of car is able to park
		int available_parking_no ; //available of number of car is able to park
		int served_car_no ;	//the car which was served
		int served_car_noA ; //the number of cars which enter the parking lot from the door of A
		int served_car_noB ; //the number of cars which enter the parking lot from the door of B
		int fee_collected ;  
		int total_waiting_time ; //total time of waiting to park
		int total_waiting_timeA ; //total time of waiting to park from the door of A
		int total_waiting_timeB ; //total time of waiting to park from the door of B
		int max_waiting_time ; //Max of time of waiting to park
		int max_waiting_timeA ;  //Max of time of waiting to park from the door of A
		int max_waiting_timeB ; //Max of time of waiting to park from the door of B
		int total_parking_time ; //Total time of parking in the parking lot

		//the priority queue of the car which drive out
		priority_queue< Car , deque<Car> , Drive_Out_Earlier > driveout_queue ;

	public :
		//Constructor
		Parking_Lot( int parking_no ) : max_parking_no(parking_no),
										available_parking_no(parking_no) ,
										served_car_no(0) ,
										served_car_noA(0) ,
										served_car_noB(0) ,
										fee_collected(0),
										total_waiting_time(0) ,
										total_waiting_timeA(0),
										total_waiting_timeB(0) ,
										max_waiting_time(0) ,
										max_waiting_timeA(0) ,
										max_waiting_timeB(0),
										total_parking_time(0) {}

		//Is there only one parking space
		bool space_availableone() const { return available_parking_no == 1 ;}
		//Are there many parking space
		bool space_available() const { return available_parking_no > 1 ;}

		//The car drive in the parking lot form the door of A
		void car_parkinga( int wtime , int drive_in ){
			if( available_parking_no > 0 ){
				int parking_time = random_no(4,36)*5 ;
				int waiting_time = drive_in - wtime ;
				driveout_queue.push(Car(wtime,drive_in,parking_time)) ;
				total_waiting_time += waiting_time ;
				total_waiting_timeA += waiting_time ;
				if ( waiting_time > max_waiting_time ) max_waiting_time = waiting_time ;
				if ( waiting_time > max_waiting_timeA ) max_waiting_timeA = waiting_time ; 
				total_parking_time += parking_time ;
				--available_parking_no ;
				++served_car_noA ;
			}
		}

		//The car drive in the parking lot form the door of B
		void car_parkingb( int wtime , int drive_in ){
			if( available_parking_no > 0 ){
				int parking_time = random_no(4,36)*5 ;
				int waiting_time = drive_in - wtime ;
				driveout_queue.push(Car(wtime,drive_in,parking_time)) ;
				total_waiting_time += waiting_time ;
				total_waiting_timeB += waiting_time ;
				if ( waiting_time > max_waiting_time ) max_waiting_time = waiting_time ;
				if ( waiting_time > max_waiting_timeB ) max_waiting_timeB = waiting_time ;
				total_parking_time += parking_time ;
				--available_parking_no ;
				++served_car_noB ;
			}
		}

		//The car drive out the parking lot
		int car_leaving( int drive_out ){
			Car car ;
			int n = 0 ;
			while( !driveout_queue.empty() && ( driveout_queue.top().drive_out() == drive_out )){
				car = driveout_queue.top() ;
				fee_collected += FEE * static_cast<int>(ceil(car.parking_time()/60.)) ;
				driveout_queue.pop() ;
				++served_car_no ;
				++available_parking_no ;
				++n ;
			}
			return n ;
		}

		template<int F>
		friend ostream& operator<<( ostream& out , const Parking_Lot<F>& foo ){
			out << "每小時收費價 ：" << F << " 元\n" 
				<< "停車場車位數 ：" << foo.max_parking_no << " 位\n\n" ;
			
			out << "                      A入口    B入口  \n"   
				<< "各入口車子進入數量：" << setw(5) << foo.served_car_noA << " 輛 " << setw(5) <<foo.served_car_noB << " 輛\n"  
				<< "各入口平均等候時間：" << setw(5) << (60*foo.total_waiting_timeA)/foo.served_car_noA << " 秒 "
									<< setw(5)	<<	(60*foo.total_waiting_timeB)/foo.served_car_noB << " 秒\n"
				<< "各入口最長等候時間：" << setw(5) << foo.max_waiting_timeA << " 分 " << setw(5) << foo.max_waiting_timeB << " 分\n\n" ; 

			out << "車子進出數量 ：" << foo.served_car_no << " 輛\n" 
				<< "停車場總收入 ：" << foo.fee_collected << " 元\n"
				<< "平均停車時間 ：" << foo.total_parking_time/foo.served_car_no << " 分\n"
				<< "每輛平均收費 ：" << foo.fee_collected/foo.served_car_no << " 元\n"
				<< "平均等候時間 ：" << (60*foo.total_waiting_time)/(foo.served_car_noA+foo.served_car_noB )<< " 秒\n"
				<< "最長等候時間 ：" << foo.max_waiting_time << " 分" ;

			return out ;
		}		

		
		


} ;

int main(){

	int i,j, w ;

	//there are 0.2 car coming in one minute from the door of A
	Car_Arrival incoming_car(0.2) ;
	//there are 0.35 car coming in one minute from the door of B
	Car_Arrival incoming_carB(0.35) ;

	Parking_Lot<30> parking_lot(60) ;

	//The queue of the car which is waiting in front of the door of A
	queue<int> waiting_cars ;
	//The queue of the car which is waiting in front of the door of B
	queue<int> waiting_carsb ;

	//After a day
	for( i = 0 ; i <= 1440 ; ++i ){

		parking_lot.car_leaving(i) ;

		//Whether is there any car coming from the door of A and B
		if( incoming_car.is_arrival() ) waiting_cars.push(i) ;
		if( incoming_carB.is_arrival() ) waiting_carsb.push(i) ;
		
		//If there is only one space to park
		if ( parking_lot.space_availableone()) {
			if( !waiting_cars.empty() && !waiting_carsb.empty()){
				if( waiting_cars.front() < waiting_carsb.front()){
					w = waiting_cars.front() ;
					waiting_cars.pop() ;
					parking_lot.car_parkinga(w,i) ;
				}else{
					w = waiting_carsb.front() ;
					waiting_carsb.pop() ;
					parking_lot.car_parkingb(w,i) ;
				}
			}else if(!waiting_cars.empty()){
				w = waiting_cars.front() ;
				waiting_cars.pop() ;
				parking_lot.car_parkinga(w,i) ;
			}else if(!waiting_carsb.empty()){
				w = waiting_carsb.front() ;
				waiting_carsb.pop() ;
				parking_lot.car_parkingb(w,i) ;
			}else{

			}
		}else if ( parking_lot.space_available()){	//Many space to park
			if( !waiting_cars.empty() && !waiting_carsb.empty()){
				w = waiting_cars.front() ;
				waiting_cars.pop() ;
				parking_lot.car_parkinga(w,i) ;
				w = waiting_carsb.front() ;
				waiting_carsb.pop() ;
				parking_lot.car_parkingb(w,i) ;	
			}else if(!waiting_cars.empty()){
				w = waiting_cars.front() ;
				waiting_cars.pop() ;
				parking_lot.car_parkinga(w,i) ;
			}else if(!waiting_carsb.empty()){
				w = waiting_carsb.front() ;
				waiting_carsb.pop() ;
				parking_lot.car_parkingb(w,i) ;
			}
		}



		if( waiting_cars.size() > 10 )
			cout << i << " : " << waiting_cars.size() << " 輛" << endl ;
	}

	//the remainder of the car 
	while( !waiting_cars.empty() || !waiting_carsb.empty() ){

		parking_lot.car_leaving(i) ;

		if ( parking_lot.space_availableone()) {
			if( !waiting_cars.empty() && !waiting_carsb.empty()){
				if( waiting_cars.front() < waiting_carsb.front()){
					w = waiting_cars.front() ;
					waiting_cars.pop() ;
					parking_lot.car_parkinga(i-w,i) ;
				}else{
					w = waiting_carsb.front() ;
					waiting_carsb.pop() ;
					parking_lot.car_parkingb(i-w,i) ;
				}
			}else if(!waiting_cars.empty()){
				w = waiting_cars.front() ;
				waiting_cars.pop() ;
				parking_lot.car_parkinga(i-w,i) ;
			}else if(!waiting_carsb.empty()){
				w = waiting_carsb.front() ;
				waiting_carsb.pop() ;
				parking_lot.car_parkingb(i-w,i) ;
			}
		}else if ( parking_lot.space_available()){		
			if( !waiting_cars.empty() && !waiting_carsb.empty()){
				w = waiting_cars.front() ;
				waiting_cars.pop() ;
				parking_lot.car_parkinga(i-w,i) ;
				w = waiting_carsb.front() ;
				waiting_carsb.pop() ;
				parking_lot.car_parkingb(i-w,i) ;	
			}else if(!waiting_cars.empty()){
				w = waiting_cars.front() ;
				waiting_cars.pop() ;
				parking_lot.car_parkinga(i-w,i) ;
			}else if(!waiting_carsb.empty()){
				w = waiting_carsb.front() ;
				waiting_carsb.pop() ;
				parking_lot.car_parkingb(i-w,i) ;
			}
		}
		++i ;		
	}

	//output the data
	cout << parking_lot << endl ;
	
	return 0 ;	

}	
