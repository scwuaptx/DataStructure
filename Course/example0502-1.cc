#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>

using namespace std ;

class Customer_Arrival{
	private :
		double p ;
	public :
		Customer_Arrival( double p2 ): p(p2) {
			srand( static_cast<unsigned>(time(NULL))) ;
		} 
		bool has_new_customer() const {
			return rand() < p * RAND_MAX ;
		}


};

class Car_Washer{
	private :
		int process_time ;
		int remaining_time ;
		int customer_no ;
		int total_waiting_time ;
	public :
		Car_Washer( int ptime ): process_time(ptime), remaining_time(0),
			customer_no(0) , total_waiting_time(0) {}

		bool is_available() const { return remaining_time == 0 ;}

		void start_service( int walting_time ){
			remaining_time = process_time ;
			total_waiting_time += walting_time ;
		}

		void pass_one_min(){
			if( remaining_time ) {
				-- remaining_time  ;
				if ( remaining_time == 0 ) ++customer_no ;

			}
		}
	
	int customer_num() const { return customer_no ; } 
	int avg_waiting_time() const {
		return total_waiting_time/customer_no ;
	}

	friend ostream& operator<<( ostream& out, const Car_Washer& foo ){
		out << foo.customer_no << " been serverd" << endl 
	   		<< "> avg waiting time : "
			<< foo.avg_waiting_time() << endl ;
	}
} ;


int main(void){

	int min , customer_arrival_time , walting_time ;
	int total_waiting_time ;
	Car_Washer washer(5) ;
	Customer_Arrival guest(0.2) ;
	queue<int> waiting_line ;

	total_waiting_time = 0 ;
	for ( min = 480 ; min <= 1320 ; ++min ){
		if ( guest.has_new_customer() ){
			waiting_line.push(min) ;
		}
		
		if ( washer.is_available() ){
			if ( !waiting_line.empty() ){
				customer_arrival_time = waiting_line.front() ;
				walting_time = min - customer_arrival_time ;
				total_waiting_time += walting_time ;
				waiting_line.pop() ;
				washer.start_service(walting_time) ;
			}
		}

		washer.pass_one_min() ;

	}


	cout << washer << endl ;

 	return 0 ;
}
