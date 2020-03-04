#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"
#include "Date.h"
#include "DestinoViag.h"

using namespace std;

class Packet{
 private:
  int id; // packet unique identifier
  DestinoViag sites; // touristic sites to visit
  Date begin;  // begin date
  Date end;  // end date
  double pricePerPerson; // price per person
  unsigned maxPersons; // number of total spaces available in the packet
  unsigned disPersons; //number of spaces still available
  
 public:
	 Packet();
	 Packet(vector<string> sites, Date begin, Date end, double pricePerPerson, unsigned maxPersons);

  // GET methods
  int getId() const;
  DestinoViag getSites() const;
  Date getBeginDate() const;
  Date getEndDate() const;
  double getPricePerPerson() const;
  unsigned getMaxPersons() const;
  unsigned getDisPersons() const;

  // SET methods
  void setId(int id);  // to set negatve if "deprecated"
  void setSites(DestinoViag sites);
  void setBeginDate(Date begin);
  void setEndDate(Date end);
  void setPricePerPerson(double pricePerPerson);
  void setMaxPersons(unsigned maxPersons);
  void setDisPersons(unsigned disPersons);
  void setPacket(vector<string> pack);

  // other methods

  friend ostream& operator<<(ostream& out, const Packet & packet);
};
