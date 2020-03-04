#include "Address.h"
#include "utils.h"

Address::Address(){
}

Address::Address(string data){
	street = trim(data.substr(0, data.find_first_of('/')));
	data = ltrim(data.substr(data.find_first_of('/') + 1));
	doorNumber = stoi(trim(data.substr(0, data.find_first_of('/'))));
	data = ltrim(data.substr(data.find_first_of('/') + 1));
	floor = trim(data.substr(0, data.find_first_of('/')));
	data = ltrim(data.substr(data.find_first_of('/') + 1));
	postalCode = trim(data.substr(0, data.find_first_of('/')));
	data = trim(ltrim(data.substr(data.find_first_of('/') + 1)));
	location = trim(data.substr(0, data.find_first_of('/')));
}

  // metodos GET


string Address::getStreet() const{

	return street;
}

unsigned short Address::getDoorNumber() const{

	return doorNumber;
}

string Address::getFloor() const{
  
	return floor;
}

string Address::getPostalCode() const{

	return postalCode;
}

string Address::getLocation() const{

	return location;
}


  // metodos SET

void Address::setStreet(string street){

	this->street = street;
}

void Address::setDoorNumber(unsigned short doorNumber){

	this->doorNumber = doorNumber;
}

void Address::setFloor(string floor){

	this->floor = floor;
}

void Address::setPostalCode(string postalCode){
	this->postalCode = postalCode;
}

void Address::setLocation(string  location){

	this->location = location;
}


/*********************************
 * Mostrar Address
 ********************************/  

// discplyes an address in a nice format
/*ostream& operator<<(ostream& out, const Address & address){

  // REQUIRES IMPLEMENTATION

}*/

