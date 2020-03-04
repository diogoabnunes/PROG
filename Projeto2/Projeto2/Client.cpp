#include "Client.h"


Client::Client() {
	name = "undefined";
	VATnumber = 000000000;
	familySize = 0;
	Address address;
	this->address = address;
	vector<Packet> a;
	this->packets = a;
	totalPurchased = 0;
}
Client::Client(string name, unsigned VATnumber, unsigned short familySize, Address address){
	this->name = name;
	this->VATnumber = VATnumber;
  
}
Client::Client(vector<string> a){
	name = a.at(0);
	VATnumber = stoi(a.at(1));
	familySize = stoi(a.at(2));
	Address address(a.at(3));
	this->address = address;
	totalPurchased = 0;
	moneyspent = 0;
}

// GET 

string Client::getName() const{
  
	return name;
}  
unsigned Client::getVATnumber() const{
  
	return VATnumber;
}
unsigned short Client::getFamilySize() const{
  
	return familySize;
}
Address Client::getAddress() const{
  
	return address;
}
vector<Packet> Client::getPacketList() const{
  
	return packets;
}
unsigned Client::getTotalPurchased() const{
  
	return totalPurchased;
}

unsigned Client::getMoneySpent() const {
	return moneyspent;
}
  
// SET
	  
void Client::setName(string nome){
  
	this->name = nome;
}
void Client::setVATnumber(unsigned VATnumber){
  
	this->VATnumber= VATnumber;
}
void Client::setFamilySize(unsigned short familySize){
  
	this->familySize = familySize;
}
void Client::setAddress(Address address){
  
	this->address = address;
}
void Client::setPacketList(vector<Packet> & packets){
  
	this->packets = packets;
}
void Client::setTotalPurchased(unsigned totalPurchased){
  
	this->totalPurchased = totalPurchased;
}
void Client::setMoneySpent(unsigned dinheiro) {
	this-> moneyspent = dinheiro;
}
void Client::addMoneySpent(unsigned dinheiro) {
	this->moneyspent += dinheiro;
}
void Client::setClient(vector<string> a,vector<Packet> pacotes) {
	name = a.at(0);
	VATnumber = stoi(a.at(1));
	familySize = stoi(a.at(2));
	Address address(a.at(3));
	this->address = address;
	packets=pacotes_cli(a.at(4), pacotes);
	totalPurchased = packets.size();
	moneyspent = stoi(a.at(5));

}

// outros metodos

//ostream& operator<<(ostream& out, const Client & client){

  // REQUIRES IMPLEMENTATION 

//}
