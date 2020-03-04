#include "Date.h"

Date::Date(){
}

Date::Date(string d1){
	year = stoi(d1.substr(0, d1.find_first_of('/')));
	d1 = d1.substr(d1.find_first_of('/') + 1);
	month = stoi(d1.substr(0, d1.find_first_of('/')));
	d1 = d1.substr(d1.find_first_of('/') + 1);
	day = stoi(d1);

}


Date::Date(unsigned short day, unsigned short month, unsigned year){

  // REQUIRES IMPLEMENTATION
}

/*********************************
 * GET Methods
 ********************************/
unsigned short Date::getDay() const{

	return day;

}

  
unsigned short Date::getMonth() const{

	return month;

}
    
unsigned Date::getYear() const{

	return year;

}

/*********************************
 * SET Methods
 ********************************/

void Date::setDay(unsigned short day){
  
	this->day = day;

}
void Date::setMonth(unsigned short month){
  
	this->month = month;

}

void Date::setYear(unsigned year){

	this->year = year;

}


/*********************************
 * Show Date
 ********************************/  

// disply a Date in a nice format
/*ostream& operator<<(ostream& out, const Date & date){

  // REQUIRES IMPLEMENTATION

}*/
