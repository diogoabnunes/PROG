#include "Agency.h"
#include <fstream>

vector<Client> info_cli(string clientes_temp,vector<Packet> pacotes) {
	vector<Client>  fcli;
	string t;
	vector<string> a;
	Client b;
	ifstream file(clientes_temp);
	if (file_em_branco(file))
	{
		return fcli;
	}
	file.close();
	file.open(clientes_temp);
	while (getline(file, t, '\n')) {
		if (t == "::::::::::") {
			b.setClient(a,pacotes);
			fcli.push_back(b);
			a.clear();
		}
		else {
			a.push_back(t);
		}
	}
	b.setClient(a,pacotes);
	fcli.push_back(b);
	file.close();
	return fcli;
}
vector<Packet> conj_pacotes(string packs_name) {
	vector<Packet> b;
	ifstream file;
	string t, f; //f é o último pacote adicionado
	vector<string> a;
	Packet pack;
	int d = 1;
	file.open(packs_name);
	getline(file, f, '\n');
	//Este ciclo da push_back para um vetor a toda a informação que ler da file até encotrar a divisoria entre dois 
	//clientes nomeadamente "::::::::::"
	while (getline(file, t, '\n')) {
		if (t == "::::::::::") {
			pack.setPacket(a);
			b.push_back(pack);
			a.clear();
			d += 1;
		}
		else {
			a.push_back(t);
		}
	}
	if (a.size() > 0) {
		pack.setPacket(a);
		b.push_back(pack);
	}
	file.close();
	return b;
}

Agency::Agency(string fileName){
	/*Um constructor que utiliza o nome do ficheiro de agencia para dar set up aos parametros da agencia*/
	ifstream f;
	string a,b, morada,p,p2;
	map<string,int> MVMainSitesmap;
	f.open(fileName);
	getline(f, name, '\n');
	getline(f, a, '\n');
	VATnumber= stoi(a);
	getline(f, morada, '\n');
	Address address(morada);
	this->address = address;
	getline(f, URL, '\n');
	getline(f, a, '\n');
	getline(f, b, '\n');
	f.close();
	this->clientsfilename = a;
	this->packetsfilename = b;
	packets = conj_pacotes(b);
	clients = info_cli(a,packets);
	this->packets = packets;
	this->clients = clients;
	int c = -9999999;
	for (int i = 0; i < packets.size(); i++) {
		if (abs(packets.at(i).getId())> c) {
			c = abs(packets.at(i).getId());
		}
	}
	map<string, int> MVutil;
	for (int k = 0; k < clients.size(); k++) {
		MVutil.clear();
		/*Uma função que itera sobre todos os pacotes comprados pelos clientes e sobre as localidades para criar um map
		que tem uma key que e uma string e um valor que e outro map assim um destino portugal por exemplo ter um map
		associado que contem as viagens aos locais de portugal*/
		for (int j = 0; j < clients.at(k).getPacketList().size(); j++) {
			p2 = trim(clients.at(k).getPacketList().at(j).getSites().getMainSite());
			transform(p2.begin(), p2.end(), p2.begin(), ::tolower);
			p2[0] = toupper(p2[0]);
			if (clients.at(k).getPacketList().at(j).getSites().getSubSites().size() > 0) {
				for (int i = 0; i < clients.at(k).getPacketList().at(j).getSites().getSubSites().size(); i++) {
					p = trim(clients.at(k).getPacketList().at(j).getSites().getSubSites().at(i));
					transform(p.begin(), p.end(), p.begin(), ::tolower);
					p[0] = toupper(p[0]);
					map<string, map<string, int>>::iterator it = MVSites.find(p2);
					if (it != MVSites.end()) {
						MVutil = MVSites.at(p2);
						/*se uma key já exitir esta fução incrementa as visitas a esse sitio  se não existir cria um par 
						em que o valor da key é um(uma visita a esse sitio)*/
						map<string, int>::iterator it = MVutil.find(p);
						if (it != MVutil.end()) {
							it->second++;
						}
						else {
							MVutil.insert(make_pair(p, 1));
						}
						MVSites[p2] = MVutil;
					}
					else {
						MVutil.insert(make_pair(p, 1));
						MVSites.insert(make_pair(p2, MVutil));
					}
				}
			}
			else {
				MVSites.insert(make_pair(p2, MVutil));
			}
		}
	}
	/*Itera sobre o map que contem uma string e o map(ver comentario acima) e faz com que ele se transforme num map
	apenas com strings e inteiros(todas as localidades esquecendo o destino principal)*/
	map<string, map<string, int>>::iterator it = MVSites.begin();
	map<string, int> Destinos;
	for (auto& par : MVSites) {
		map<string, int> mapi = par.second;
		for (auto& valores : mapi) {
			map<string, int>::iterator it = Destinos.find(valores.first);
			if (it != Destinos.end()) {
				it->second++;
			}
			else {
				Destinos.insert(make_pair(valores.first, valores.second));
			}
		}
	}
	MVSubSites = Destinos;
	/*multimap<int, string> sorteddest;
	map<string, int> ::iterator its = Destinos.begin();
	for (int k = 0; k < Destinos.size(); k++) {
		sorteddest.insert(make_pair(its->second, its->first));
		its++;
	}*/
	this->maxPacketsId = c;
	this->clientsInfoHasChanged = false;
	this->packetsInfoHasChanged = false;
}

// GET

string Agency::getName() const{
	return name;
}

unsigned Agency::getVATnumber() const{
	return VATnumber;
}

Address Agency::getAddress() const{

	return address;
}

string Agency::getURL() const{

	return URL;
}

vector<Client> Agency::getClients() const{

	return clients;
}

vector<Packet> Agency::getPackets() const{

	return packets;
}

string Agency::getclientsfilename() {
	return clientsfilename;
}

string Agency::getpacketsfilename() {
	return packetsfilename;
}

bool Agency::getclientsInfoHasChanged() {
	return clientsInfoHasChanged;
}

bool Agency::getpacketsInfoHasChanged() {
	return packetsInfoHasChanged;
}

int Agency::getMaxPacketsId() {
	return maxPacketsId;
}

map<string,map<string,int>> Agency::getMVSites() {
	return MVSites;
}

map<string, int> Agency::getMVSubSites() {
	return MVSubSites;
}

// SET

void Agency::setName(string name){

	this->name = name;
}
void Agency::setVATnumber(unsigned VATnumber){

	this->VATnumber = VATnumber;
}
void Agency::setAddress(Address address){

	this->address = address;
}
 void Agency::setURL(string url){

	  this->URL = url;

}
 void Agency::setClients(vector<Client> & clients){

	 this->clients = clients;

}
void Agency::setPackets(vector<Packet> & packets){

	this->packets = packets;

}
void Agency::addClient(vector<string> cliente) {
	Client client(cliente);
	clients.push_back(client);

}

void Agency::setclientsInfoHasChanged() {
	this->clientsInfoHasChanged = true;
}

void Agency::setpacketsInfoHasChanged() {
	this->packetsInfoHasChanged = true;
}

void Agency::setMaxPacketsId(int Id) {
	this->maxPacketsId = Id;
}

void Agency::setMVSites() {
	MVSites.clear();
	/*esta função e igual a que esta no constructor (ver comentarios acima)*/
	string p,p2;
	map<string, int> MVutil;
	for (int k = 0; k < clients.size(); k++) {
		MVutil.clear();
		for (int j = 0; j < clients.at(k).getPacketList().size(); j++) {
			p2 = trim(clients.at(k).getPacketList().at(j).getSites().getMainSite());
			transform(p2.begin(), p2.end(), p2.begin(), ::tolower);
			p2[0] = toupper(p2[0]);
			if (clients.at(k).getPacketList().at(j).getSites().getSubSites().size() > 0) {
				for (int i = 0; i < clients.at(k).getPacketList().at(j).getSites().getSubSites().size(); i++) {
					p = trim(clients.at(k).getPacketList().at(j).getSites().getSubSites().at(i));
					transform(p.begin(), p.end(), p.begin(), ::tolower);
					p[0] = toupper(p[0]);
					map<string, map<string, int>>::iterator it = MVSites.find(p2);
					if (it != MVSites.end()) {
						MVutil = MVSites.at(p2);
						map<string, int>::iterator it = MVutil.find(p);
						if (it != MVutil.end()) {
							it->second++;
						}
						else {
							MVutil.insert(make_pair(p, 1));
						}
						MVSites[p2] = MVutil;
					}
					else {
						MVutil.insert(make_pair(p, 1));
						MVSites.insert(make_pair(p2, MVutil));
					}
				}
			}
			else {
				MVSites.insert(make_pair(p2, MVutil));
			}
		}
	}
}

void Agency::setMVSubSites() {
	map<string, map<string, int>>::iterator it = MVSites.begin();
	map<string, int> Destinos;
	for (auto& par : MVSites) {
		map<string, int> mapi = par.second;
		for (auto& valores : mapi) {
			map<string, int>::iterator it = Destinos.find(valores.first);
			if (it != Destinos.end()) {
				it->second++;
			}
			else {
				Destinos.insert(make_pair(valores.first, valores.second));
			}
		}
	}
	MVSubSites = Destinos;
}

void Agency::setMVSub10() {
	multimap<int, string> sorteddest;
	map<string, int> ::iterator its = MVSubSites.begin();
	for (int k = 0; k < MVSubSites.size(); k++) {
		sorteddest.insert(make_pair(its->second, its->first));
		its++;
	}
	map<int, string> Destinosvisit;
	multimap<int, string>::reverse_iterator itera = sorteddest.rbegin();
	for (int i = 0; i < sorteddest.size(); i++) {
		Destinosvisit.insert(make_pair(itera->first, itera->second));
		itera++;
	}
	MVSub10 = Destinosvisit;
}


/*********************************
 * Mostrar Loja
 ********************************/  

// mostra o conteudo de uma agencia
/*ostream& operator<<(ostream& out, const Agency & agency){

  // A IMPLEMENTATION REQUIRED 
}*/
