#include "Packet.h"

Packet::Packet() {
	id = 0;
	DestinoViag sites;
	this->sites = sites;
	Date begin;
	this->begin = begin;
	Date end;
	this->end = end;
	pricePerPerson = 0;
	maxPersons = 0;
	disPersons = 0;
}
Packet::Packet(vector<string> sites, Date inicio, Date fim, double precoPessoa, unsigned maxPessoas){

  // REQUIRES IMPLEMENTATION
}

  // metodos GET

int Packet::getId() const{

	return id;
}

DestinoViag Packet::getSites() const{

	return sites;
}

Date Packet::getBeginDate() const{

	return begin;
}

Date Packet::getEndDate() const{

	return end;
}

double Packet::getPricePerPerson() const{

	return pricePerPerson;
}

unsigned Packet::getMaxPersons() const{

	return maxPersons;
}

unsigned Packet::getDisPersons() const {
	return disPersons;
}

  // metodos SET

void Packet::setId(int id){

	this->id = id;
}

void Packet::setSites(DestinoViag sites){

	this->sites = sites;
}

void Packet::setBeginDate(Date begin){

	this->begin = begin;
}

void Packet::setEndDate(Date end){

	this->end = end;
}

void Packet::setPricePerPerson(double pricePerPerson){

	this->pricePerPerson = pricePerPerson;
}

void Packet::setMaxPersons(unsigned maxPersons){

	this->maxPersons = maxPersons;
}

void Packet::setDisPersons(unsigned disPersons) {
	this->disPersons = disPersons;
}

void Packet::setPacket(vector<string> pack) {
	id = stoi(pack.at(0));
	DestinoViag a(pack.at(1));
	sites = a;
	Date c(pack.at(2));
	begin = c;
	Date b(pack.at(3));
	end = b;
	pricePerPerson = stoi(pack.at(4));
	maxPersons = stoi(pack.at(5));
	disPersons = stoi(pack.at(6));
}

/*********************************
 * Show Packet information
 ********************************/  

// shows a packet content 
/*ostream& operator<<(ostream& out, const Packet & packet){

  // REQUIRES IMPLEMENTATION
}*/
