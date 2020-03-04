#include "DestinoViag.h"

DestinoViag::DestinoViag() {
	mainSite = "";
	vector<string> a;
	subSites = a;
}


DestinoViag::DestinoViag(string destino) {
	mainSite = destino.substr(0,destino.find_first_of("-")-1);
	vector<string> a;
	if (destino.find("-")!=string::npos) {
		destino = destino.substr(destino.find_first_of("-")+2, destino.size());
		if (destino.find(",") != string::npos) {
			for (int i = 0; i < (count(destino.begin(), destino.end(), ',')) + 1; i++) {
				a.push_back(destino.substr(0, destino.find_first_of(',')));
				destino = destino.substr(destino.find_first_of(',') + 2);
			}
		}
		a.push_back(destino);
	}
	subSites = a;
}

void DestinoViag::setMainSite(string site) {
	mainSite = site;
}

void DestinoViag::setSubSites(vector<string> sites) {
	subSites = sites;
}

string DestinoViag::getMainSite() {
	return mainSite;
}

vector<string> DestinoViag::getSubSites() {
	return subSites;
}

void DestinoViag::clearsubSites() {
	vector<string> a;
	subSites = a;
}