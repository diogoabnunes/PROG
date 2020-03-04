#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"
#include "Packet.h"
#include "Address.h"
#include "utils.h"

using namespace std;

class Client{
 private:
  string name; // name of the client
  unsigned VATnumber; // VAT number of client
  unsigned short familySize;  // number of family members
  Address address; // client's address
  vector<Packet> packets; // vector to store client's packets bought
  unsigned  totalPurchased; // total value spent by the client
  unsigned moneyspent;

 public:
	Client();
	Client(string name, unsigned VATnumber, unsigned short familySize, Address address);  // for a new client
	Client(vector<string> a);  // client read from file
	

  // GET methods
  
  string getName() const;
  unsigned getVATnumber() const;
  unsigned short getFamilySize() const;
  Address getAddress() const;
  vector<Packet> getPacketList() const;
  unsigned getTotalPurchased() const;
  unsigned getMoneySpent() const;
 
  
  // SET methods
  
  void setName(string name);
  void setVATnumber(unsigned VATnumber);
  void setFamilySize(unsigned short familySize);
  void setAddress(Address address);
  void setPacketList(vector<Packet> & packets);
  void setTotalPurchased(unsigned totalPurchased);
  void setClient(vector<string> a,vector<Packet> pacotes);
  void setMoneySpent(unsigned dinheiro);
  
  // other methods
  void addMoneySpent(unsigned dinheiro);
  
  friend ostream& operator<<(ostream& out, const Client & client);
};
