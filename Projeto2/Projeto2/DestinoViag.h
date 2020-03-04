#pragma once
#include <vector>
#include <string>

using namespace std;

class DestinoViag {
private:
	string mainSite;
	vector<string> subSites;
public:
	DestinoViag();
	DestinoViag(string destino);

	string getMainSite();
	vector<string> getSubSites();

	void setMainSite(string Site);
	void setSubSites(vector<string> places);
	void clearsubSites();
};