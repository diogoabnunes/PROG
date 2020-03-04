#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

#include "defs.h"
#include "Address.h"
#include "Client.h"
#include "Packet.h"
#include "utils.h"

using namespace std;

class Agency{
 private:
  string name; // name of the  agency
  unsigned int VATnumber; // VAT number of the agency
  Address address; // address of the agency
  string URL; // URL of the agency Web site
  vector<Client> clients; // vector to store the existing clients
  vector<Packet> packets; // vector to store the existing packets
  
  map<string,map<string,int>> MVSites;
  map<string, int> MVSubSites;
  map< int,string> MVSub10;
  string clientsfilename;
  string packetsfilename;
  
  bool clientsInfoHasChanged; // flag that is set to "true" if at least one client has been changed/added/deleted
  bool packetsInfoHasChanged; // flag that is set to "true" if at least one packet has been changed/added/deleted
  unsigned int maxClientsId; // maximum value among all clients identifiers
  int maxPacketsId; // maximum value among all packets identifiers

 public:
  Agency(string fileName);

  // GET
  string getName() const;
  unsigned getVATnumber() const;
  Address getAddress() const;
  string getURL() const;
  vector<Client> getClients() const;
  vector<Packet> getPackets() const;

  map<string,map<string,int>> getMVSites();
  map<string, int> getMVSubSites();
  map<int,string> getMVSub10();
  string getclientsfilename();
  string getpacketsfilename();

 
  bool getclientsInfoHasChanged();
  bool getpacketsInfoHasChanged();

  int getMaxPacketsId();
  
  // SET
  void setName(string name);
  void setVATnumber(unsigned VATnumber);
  void setAddress(Address address);
  void setURL(string url);
  void setClients(vector<Client> & clients);
  void setPackets(vector<Packet> & packets);
  void addClient(vector<string> cliente);

  void setMVSites();
  void setMVSubSites();
  void setMVSub10();

  void setclientsInfoHasChanged();
  void setpacketsInfoHasChanged();
  // other methods */

  void setMaxPacketsId(int Id);
  
  friend ostream& operator<<(ostream& out, const Agency & agency);

};
