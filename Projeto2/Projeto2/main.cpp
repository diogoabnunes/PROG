#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>

#include "Address.h"
#include "Agency.h"
#include "Client.h"
#include "Date.h"
#include "defs.h"
#include "Menus.h"
#include "Packet.h"
#include "utils.h"

int main() {
	string  teste,teste2, AGENCY_FILE_NAME;
	ifstream agen;
	consl_clear();
	cout << "### Joao Rosario up201806334 & Diogo Nunes  up201808546 ###" << endl;
	cout << "Introduza o nome da agencia: ";
	getline(cin, AGENCY_FILE_NAME);
	AGENCY_FILE_NAME = AGENCY_FILE_NAME + ".txt";
	agen.open(AGENCY_FILE_NAME);
	if (agen.fail()) {
		cout << "A agencia nao existe.\nIntroduza 'S' para tentar novamente.\nIntroduza 'N' se pretende sair\nInput: ";
		getline(cin, teste);
		while (teste != "S" && teste != "N") {
			cout << "Insira ou 'S' ou 'N': ";
			getline(cin, teste);
		}
		if (teste == "S") {
			do {
				consl_clear();
				cout << "### Joao Rosario up201806334 & Diogo Nunes  up201808546 ###" << endl;
				cout << "Introduza o nome da agencia: ";
				getline(cin, AGENCY_FILE_NAME);
				AGENCY_FILE_NAME = AGENCY_FILE_NAME + ".txt";
				agen.open(AGENCY_FILE_NAME);
				if (agen.fail()) {
					cout << "A agencia nao existe.\nIntroduza 'S' para tentar outra vez ou 'N' para cancelar\nInput: ";
					getline(cin, teste2);
					if(teste2=="N"){
						return 2;
					}
				}
				else {
					teste = "N";
				}
			} while (teste=="S");
		}
		else {
			return 1;
		}
	}
	Agency agency(AGENCY_FILE_NAME);   // create the agency
	mainMenu(agency); // initial menu inicial with the major options of the application
  
  return 0;
}
