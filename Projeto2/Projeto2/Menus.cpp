#include "Menus.h"
#include "utils.h"


void refresh_cli(Agency& agency) {
	ofstream file;
	string a, b;
	file.open(agency.getclientsfilename());
	//Para cada Cliente este for loop vai escrever no ficheiro as informações desse mesmo cliente.
	for (int i = 0; i < agency.getClients().size(); i++) {
		b = "";
		file << agency.getClients().at(i).getName() << endl;
		file << agency.getClients().at(i).getVATnumber() << endl;
		file << agency.getClients().at(i).getFamilySize() << endl;
		file << agency.getClients().at(i).getAddress().getStreet() << "/" << agency.getClients().at(i).getAddress().getDoorNumber() << "/" << agency.getClients().at(i).getAddress().getFloor() << "/" << agency.getClients().at(i).getAddress().getPostalCode() << "/" << agency.getClients().at(i).getAddress().getLocation() << endl;
		if (agency.getClients().at(i).getPacketList().size() > 0) {
			for (int k = 0; k < agency.getClients().at(i).getPacketList().size(); k++) {
				b += to_string(agency.getClients().at(i).getPacketList().at(k).getId()) + " ;";
			}
			b = b.substr(0, b.size() - 2);
			file << b;
		}
		else {
			file << 0;
		}
		file <<endl<< agency.getClients().at(i).getMoneySpent();
		if (i + 1 != agency.getClients().size()) {
			file << endl << "::::::::::" << endl;
		}
	}
	file.close();
}
void refresh_pac(Agency& agency) {
	if (agency.getPackets().size() == 0) {
		ofstream file2;
		file2.open(agency.getpacketsfilename());
		file2.close();
		return;
	}
	ofstream file;
	string a;
	file.open(agency.getpacketsfilename());
	file << agency.getPackets().at(agency.getPackets().size() - 1).getId() << endl;
	for (int i = 0; i < agency.getPackets().size(); i++) {
		//Este loop escreve as informaçoes de cada pacote no ficheiro de pacotes
		a = " - ";
		file << agency.getPackets().at(i).getId() << endl;
		file << agency.getPackets().at(i).getSites().getMainSite(); //" – "
		if (agency.getPackets().at(i).getSites().getSubSites().size() > 0) {
			for (int j = 0; j < agency.getPackets().at(i).getSites().getSubSites().size(); j++) {
				a += agency.getPackets().at(i).getSites().getSubSites().at(j) + ", ";
			}
			a = a.substr(0, a.find_last_of(','));
			file << a;
		}
		file << endl;
		file << agency.getPackets().at(i).getBeginDate().getYear() << "/";
		file << agency.getPackets().at(i).getBeginDate().getMonth() << "/";
		file << agency.getPackets().at(i).getBeginDate().getDay() << endl;
		file << agency.getPackets().at(i).getEndDate().getYear() << "/";
		file << agency.getPackets().at(i).getEndDate().getMonth() << "/";
		file << agency.getPackets().at(i).getEndDate().getDay() << endl;
		file << agency.getPackets().at(i).getPricePerPerson() << endl;
		file << agency.getPackets().at(i).getMaxPersons() << endl;
		file << agency.getPackets().at(i).getDisPersons();
		if (i + 1 != agency.getPackets().size()) {
			file << endl << "::::::::::" << endl;
		}

	}
	file.close();
}

/*Um menu que filtra os pacotes por disponibilidade e data*/
void filt_pac(Agency& agency) {
	int b;
	string a;
	do {
		consl_clear();
		cout << "### FILTRAR PACOTES ###" << endl;
		cout << "[1] FILTRAR POR DATA" << endl;
		cout << "[2] FILTRAR POR DISPONIBILIDADE" << endl;
		cout << "[0] VOLTAR" << endl;
		b = intrec();
		if (b == 2) {
			cout << "####################" << endl;
			for (int i = 0; i < agency.getPackets().size(); i++) {
				//este for da cout de todos os pacotes com id>0
				if (agency.getPackets().at(i).getId() > 0) {
					a = " - ";
					cout << "Id: " << agency.getPackets().at(i).getId() << endl;
					cout << "Localidades a visitar: " << agency.getPackets().at(i).getSites().getMainSite();
					if (agency.getPackets().at(i).getSites().getSubSites().size() > 0) {
						for (int j = 0; j < agency.getPackets().at(i).getSites().getSubSites().size(); j++) {
							a += agency.getPackets().at(i).getSites().getSubSites().at(j) + ", ";
						}
						a = a.substr(0, a.find_last_of(','));
						cout << a;
					}
					cout << endl;
					cout << "Data de Inicio: " << agency.getPackets().at(i).getBeginDate().getYear() << "/";
					cout << agency.getPackets().at(i).getBeginDate().getMonth() << "/";
					cout << agency.getPackets().at(i).getBeginDate().getDay() << endl;
					cout << "Data de Fim: " << agency.getPackets().at(i).getEndDate().getYear() << "/";
					cout << agency.getPackets().at(i).getEndDate().getMonth() << "/";
					cout << agency.getPackets().at(i).getEndDate().getDay() << endl;
					cout << "Preço por Pessoa: " << agency.getPackets().at(i).getPricePerPerson() << endl;
					cout << "Lugares Totais: " << agency.getPackets().at(i).getMaxPersons() << endl;
					cout << "Lugares Disponiveis: " << agency.getPackets().at(i).getDisPersons();
					if (i + 1 != agency.getPackets().size()) {
						cout << endl << "----------" << endl;
					}
				}
			}
			cout << endl << "####################" << endl;
			cout << "Insira ENTER para Continuar." << endl;
			cin.ignore(1000, '\n');
		}
		else if (b == 1) {
			Date d1, d2;
			int o;
			/*um for que itera sobre todos os pacotes e em seguida um if com uma função cmp_datas() que 
			retorna true caso a data inserida a direita seja posterior a da esquerda*/
			cout << "Se pretender procurar a partir de uma certa data insira '0'." << endl;
			cout << "Se pretender procurar ate uma certa data insira '1'." << endl;
			cout << "Se pretender procurar entre duas datas insira '2'." << endl;
			cout << "Input: ";
			o = intrec();
			if (o == 0) {
				cout << "Insira a data de inicio." << endl;
				d1 = lerdata();
				cout << "####################" << endl;
				cout << "----------" << endl;
				for (int i = 0; i < agency.getPackets().size(); i++) {
					if (cmp_datas(d1, agency.getPackets().at(i).getBeginDate())) {
						a = " - ";
						cout << "Id: " << agency.getPackets().at(i).getId() << endl;
						cout << "Localidades a visitar: " << agency.getPackets().at(i).getSites().getMainSite();
						if (agency.getPackets().at(i).getSites().getSubSites().size() > 0) {
							for (int j = 0; j < agency.getPackets().at(i).getSites().getSubSites().size(); j++) {
								a += agency.getPackets().at(i).getSites().getSubSites().at(j) + ", ";
							}
							a = a.substr(0, a.find_last_of(','));
							cout << a;
						}
						cout << endl;
						cout << "Data de Inicio: " << agency.getPackets().at(i).getBeginDate().getYear() << "/";
						cout << agency.getPackets().at(i).getBeginDate().getMonth() << "/";
						cout << agency.getPackets().at(i).getBeginDate().getDay() << endl;
						cout << "Data de Fim: " << agency.getPackets().at(i).getEndDate().getYear() << "/";
						cout << agency.getPackets().at(i).getEndDate().getMonth() << "/";
						cout << agency.getPackets().at(i).getEndDate().getDay() << endl;
						cout << "Preço por Pessoa: " << agency.getPackets().at(i).getPricePerPerson() << endl;
						cout << "Lugares Totais: " << agency.getPackets().at(i).getMaxPersons() << endl;
						cout << "Lugares Disponiveis: " << agency.getPackets().at(i).getDisPersons();
						cout << endl << "----------" << endl;
					}
				}
				cout << "####################" << endl;
				cout << "Insira ENTER para Continuar." << endl;
				cin.ignore(1000, '\n');

			}
			else if (o == 1) {
				cout << "Indira a data de fim." << endl;
				d2 = lerdata();
				cout << "####################" << endl;
				cout << "----------" << endl;
				for (int i = 0; i < agency.getPackets().size(); i++) {
					if (cmp_datas(agency.getPackets().at(i).getBeginDate(), d2)) {
						a = " - ";
						cout << "Id: " << agency.getPackets().at(i).getId() << endl;
						cout << "Localidades a visitar: " << agency.getPackets().at(i).getSites().getMainSite();
						if (agency.getPackets().at(i).getSites().getSubSites().size() > 0) {
							for (int j = 0; j < agency.getPackets().at(i).getSites().getSubSites().size(); j++) {
								a += agency.getPackets().at(i).getSites().getSubSites().at(j) + ", ";
							}
							a = a.substr(0, a.find_last_of(','));
							cout << a;
						}
						cout << endl;
						cout << "Data de Inicio: " << agency.getPackets().at(i).getBeginDate().getYear() << "/";
						cout << agency.getPackets().at(i).getBeginDate().getMonth() << "/";
						cout << agency.getPackets().at(i).getBeginDate().getDay() << endl;
						cout << "Data de Fim: " << agency.getPackets().at(i).getEndDate().getYear() << "/";
						cout << agency.getPackets().at(i).getEndDate().getMonth() << "/";
						cout << agency.getPackets().at(i).getEndDate().getDay() << endl;
						cout << "Preço por Pessoa: " << agency.getPackets().at(i).getPricePerPerson() << endl;
						cout << "Lugares Totais: " << agency.getPackets().at(i).getMaxPersons() << endl;
						cout << "Lugares Disponiveis: " << agency.getPackets().at(i).getDisPersons();
						cout << endl << "----------" << endl;
					}
				}
				cout << "####################" << endl;
				cout << "Insira ENTER para Continuar." << endl;
				cin.ignore(1000, '\n');
			}
			else if (o == 2) {
				cout << "Insira a data de inicio." << endl;
				d1 = lerdata();
				cout << "Indira a data de fim." << endl;
				d2 = lerdata();
				cout << "####################" << endl;
				cout << "----------" << endl;
				for (int i = 0; i < agency.getPackets().size(); i++) {
					if (cmp_datas(d1, agency.getPackets().at(i).getBeginDate()) && cmp_datas(agency.getPackets().at(i).getEndDate(), d2)) {
						a = " - ";
						cout << "Id: " << agency.getPackets().at(i).getId() << endl;
						cout << "Localidades a visitar: " << agency.getPackets().at(i).getSites().getMainSite();
						if (agency.getPackets().at(i).getSites().getSubSites().size() > 0) {
							for (int j = 0; j < agency.getPackets().at(i).getSites().getSubSites().size(); j++) {
								a += agency.getPackets().at(i).getSites().getSubSites().at(j) + ", ";
							}
							a = a.substr(0, a.find_last_of(','));
							cout << a;
						}
						cout << endl;
						cout << "Data de Inicio: " << agency.getPackets().at(i).getBeginDate().getYear() << "/";
						cout << agency.getPackets().at(i).getBeginDate().getMonth() << "/";
						cout << agency.getPackets().at(i).getBeginDate().getDay() << endl;
						cout << "Data de Fim: " << agency.getPackets().at(i).getEndDate().getYear() << "/";
						cout << agency.getPackets().at(i).getEndDate().getMonth() << "/";
						cout << agency.getPackets().at(i).getEndDate().getDay() << endl;
						cout << "Preço por Pessoa: " << agency.getPackets().at(i).getPricePerPerson() << endl;
						cout << "Lugares Totais: " << agency.getPackets().at(i).getMaxPersons() << endl;
						cout << "Lugares Disponiveis: " << agency.getPackets().at(i).getDisPersons();
						cout << endl << "----------" << endl;
					}
				}
				cout << "####################" << endl;
				cout << "Insira ENTER para Continuar." << endl;
				cin.ignore(1000, '\n');
			}
			else {
			cout << o << " nao e uma entrada válida.\nIntroduza ENTER para voltar.";
			cin.ignore(1000, '\n');
			}
		}
	} while (b != 0);
}
/*Um menu simples que apenas da cout de todos os pacotes ou então abre um outro menu (filt_pac())*/
void ver_pac(Agency& agency) {
	int q, id;
	do {
		consl_clear();
		cout << "### MENU DE VISUALIZAR PACOTES ###" << endl;
		cout << "[1] VER TODOS OS PACOTES" << endl;
		cout << "[2] PROCURAR PACOTE" << endl;
		cout << "[3] FILTRAR" << endl;
		cout << "[0] VOLTAR" << endl;
		q = intrec();
		if (q == 1) {
			string a;
			/*este for da cout de todos os pacotes na agencia disponiveis ou indisponiveis*/
			cout << "####################" << endl;
			for (int i = 0; i < agency.getPackets().size(); i++) {
				a = " - ";
				cout << "Id: " << agency.getPackets().at(i).getId() << endl;
				cout << "Localidades a visitar: " << agency.getPackets().at(i).getSites().getMainSite();
				if (agency.getPackets().at(i).getSites().getSubSites().size() > 0) {
					for (int j = 0; j < agency.getPackets().at(i).getSites().getSubSites().size(); j++) {
						a += agency.getPackets().at(i).getSites().getSubSites().at(j) + ", ";
					}
					a = a.substr(0, a.find_last_of(','));
					cout << a;
				}
				cout << endl;
				cout << "Data de Inicio: " << agency.getPackets().at(i).getBeginDate().getYear() << "/";
				cout <<  agency.getPackets().at(i).getBeginDate().getMonth() << "/";
				cout <<  agency.getPackets().at(i).getBeginDate().getDay() << endl;
				cout << "Data de Fim: " << agency.getPackets().at(i).getEndDate().getYear() << "/";
				cout << agency.getPackets().at(i).getEndDate().getMonth() << "/";
				cout << agency.getPackets().at(i).getEndDate().getDay() << endl;
				cout << "Preço por Pessoa: " << agency.getPackets().at(i).getPricePerPerson() << endl;
				cout << "Lugares Totais: " << agency.getPackets().at(i).getMaxPersons() << endl;
				cout << "Lugares Disponiveis: " << agency.getPackets().at(i).getDisPersons();
				if (i + 1 != agency.getPackets().size()) {
					cout << endl << "----------" << endl;
				}
			}
			cout << endl << "####################" << endl;
			cout << "Insira ENTER para Continuar." << endl;
			cin.ignore(1000, '\n');
		}
		else if (q == 2) {
			/*Este for itera sobre todos os pacotes e apenas da cout do pacote com o ID correspondente ao introduzido pelo
			utilizador*/
			cout << "Insira o ID a procurar: ";
			id = abs(intrec());
			for (int i = 0; i < agency.getPackets().size(); i++) {
				if (id == abs(agency.getPackets().at(i).getId())) {
					cout << "###################" << endl;
					cout << "ID do pacote: " << agency.getPackets().at(i).getId() << endl;
					if (agency.getPackets().at(i).getSites().getSubSites().size() > 0) {
						cout << "Locais a visitar: " << agency.getPackets().at(i).getSites().getMainSite() << " - ";
						for (int k = 0; k < agency.getPackets().at(i).getSites().getSubSites().size() - 1; k++) {
							cout << agency.getPackets().at(i).getSites().getSubSites().at(k) << ", ";
						}
						cout << agency.getPackets().at(i).getSites().getSubSites().at(agency.getPackets().at(i).getSites().getSubSites().size() - 1) << endl;
					}
					else {
						cout << "Locais a visitar: " << agency.getPackets().at(i).getSites().getMainSite() << endl;
					}
					cout << "Data de Inicio: " << agency.getPackets().at(i).getBeginDate().getYear() << "/";
					cout << agency.getPackets().at(i).getBeginDate().getMonth() << "/";
					cout << agency.getPackets().at(i).getBeginDate().getDay() << endl;
					cout << "Data de Fim: " << agency.getPackets().at(i).getEndDate().getYear() << "/";
					cout << agency.getPackets().at(i).getEndDate().getMonth() << "/";
					cout << agency.getPackets().at(i).getEndDate().getDay() << endl;
					cout << "Preço por Pessoa: " << agency.getPackets().at(i).getPricePerPerson() << endl;
					cout << "Lugares Totais: " << agency.getPackets().at(i).getMaxPersons() << endl;
					cout << "Lugares Disponiveis: " << agency.getPackets().at(i).getDisPersons() << endl;
					cout << "###################";
					break;
				}
				if (i == agency.getPackets().size() - 1) {
					cout << "Nenhum pacote tem o ID: " << id;
				}
			}
			cout << endl << "Insira ENTER para continuar.";
			cin.ignore(1000, '\n');
		}
		else if (q == 3) {
			filt_pac(agency);
		}

	} while (q != 0);

}
/*Um menu para criar pacotes*/
void cri_pac(Agency& agency) {
	int csto,lt,rnd;
	string t, pais, dest,sn;
	Date a, af;
	t = "";
	consl_clear();
	cout << "####################" << endl;
	cout << "Insira o destino principal.\n";
	getline(cin, pais, '\n');
	pais = trim(pais);
	cout << "Introduza os locais que pretende visitar um a um. pressione 'Enter' para terminar.\n";
	getline(cin, dest, '\n');
	while (dest != "") {
		if (dest == "") {
			break;
		}
		else {
			t += trim(dest) + ", ";
		}
		getline(cin, dest, '\n');
	}
	if (t != "") {
		t = t.substr(0, t.find_last_of(','));
		t = pais + " - " + t;
	}
	else {
		t = pais;
	}
	DestinoViag ts;
	cout << "Data de Inicio:" << endl;
	a = lerdata();
	cout << "Data de Fim:" << endl;
	af = lerdata();
	bool k = cmp_datas(a, af);
	while (!k) {
		cout << "A data inicial inserida nao pode ser posterior a final." << endl;
		cout << "Data de Inicio:" << endl;
		a = lerdata();
		cout << "Data de Fim:" << endl;
		af = lerdata();
		k = cmp_datas(a, af);
	}
	cout << "Introduza o custo por pessoa: ";
	csto = intrec();
	cout << "Insira o número de lugares totais: ";
	lt = intrec();
	cout << "##############################" << endl;
	cout << "Confirma a informação do pacote?" << endl << "Insira S para confirmar ou N para cancelar." << endl;
	cout << "##############################" << endl << "Locais a visitar: " << t << endl;
	cout << "Data Inicio: " << a.getYear()<<"/"<<a.getMonth()<<"/"<<a.getDay() << endl;
	cout << "Data Fim: " << af.getYear() << "/" << af.getMonth() << "/" << af.getDay() << endl;
	cout << "Custo por Pessoa: " << csto << endl;
	cout << "Lugares Totais: " << lt << endl;
	getline(cin, sn, '\n');
	while (sn != "S" && sn != "N") {
		cout << "Insira ou 'S' ou 'N': ";
		getline(cin, sn);
	}
	bool tes = false;
	do {
		if (sn == "S") {
			Packet h;
			vector<Packet> newPackets = agency.getPackets();
			/*Verifica o ultimo id da agencia para incrementar +1 */
			if (agency.getPackets().size() == 0) {
				rnd = 1;
			}
			else {
				rnd = abs(agency.getMaxPacketsId()) + 1;
			}
			h.setId(rnd);
			string main = trim(t.substr(0, t.find_first_of("-") - 1));
			ts.setMainSite(main);
			vector<string> abc;
			if (t.find("-") != string::npos) {
				t = trim(t.substr(t.find_first_of("-") + 1, t.size()));
				for (int i = 0; i < (count(t.begin(), t.end(), ',')) + 1; i++) {
					abc.push_back(t.substr(0,t.find_first_of(',')));
					t = t.substr(t.find_first_of(',') + 2);
				}
				abc.push_back(t);
			}
			ts.setSubSites(abc);
			/*h é um pacote temporario criado para ser "pushed back" num vetor de pacotes que posteriormente serve para 
			dar set dos pacotes da agencia*/
			h.setSites(ts);
			h.setBeginDate(a);
			h.setEndDate(af);
			h.setPricePerPerson(csto);
			h.setMaxPersons(lt);
			h.setDisPersons(lt);
			newPackets.push_back(h);
			agency.setPackets(newPackets);
			int c = -9999999;
			for (int i = 0; i < agency.getPackets().size(); i++) {
				if (agency.getPackets().at(i).getId() > c) {
					c = abs(agency.getPackets().at(i).getId());
				}
			};
			agency.setMaxPacketsId(c);
			agency.setpacketsInfoHasChanged();
		}
		else if (sn != "N") {
			cout << "Por favor introduza apenas S ou N: ";
			tes = true;
		}
		else {
			cout << "Operação cancelada por sua ordem.";
			cout << "Pressione ENTER para retornar";
			cin.ignore(1000, '\n');
			return;
		}
	} while (tes);
	return;
}
/*Um menu para apagar pacotes*/
void del_pac(Agency& agency) {
	string f, c;
	int a;
	consl_clear();
	do {
		cout << "### APAGAR PACOTE ###" << endl;
		cout << "Insira o id do pacote a apagar. Insira '0' para ver os pacotes existentes." << endl;
		a = abs(intrec());
		if (a == 0) {
			ver_pac(agency);
		}
		consl_clear();
	} while (a == 0);

	for (int i = 0; i < agency.getPackets().size(); i++) {
		if (a == abs(agency.getPackets().at(i).getId())) {
			a = i + 1;
			break;
		}
		if (i == agency.getPackets().size() - 1) {
			cout << "Nenhum pacote tem o ID: " << a;
			cout << "Insira ENTER para retornar.";
			cin.ignore(1000, '\n');
		}
	}

	if (agency.getPackets().size() > 0) {
		/*Da cout das informações do packote (a-1)*/
		cout << "##############################" << endl;
		cout << "Deseja eliminar o pacote?" << endl << "Insira S para confirmar ou N para cancelar." << endl;
		cout << "##############################" << endl;
		c = " - ";
		cout << "Id: " << agency.getPackets().at(a - 1).getId() << endl;
		cout << "Localidades a visitar: " << agency.getPackets().at(a - 1).getSites().getMainSite();
		if (agency.getPackets().at(a - 1).getSites().getSubSites().size() > 0) {
			for (int j = 0; j < agency.getPackets().at(a - 1).getSites().getSubSites().size(); j++) {
				c += agency.getPackets().at(a - 1).getSites().getSubSites().at(j) + ", ";
			}
			c = c.substr(0, c.find_last_of(','));
			cout << c;
		}
		cout << endl;
		cout << "Data de Inicio: " << agency.getPackets().at(a - 1).getBeginDate().getYear() << "/";
		cout << agency.getPackets().at(a - 1).getBeginDate().getMonth() << "/";
		cout << agency.getPackets().at(a - 1).getBeginDate().getYear() << endl;
		cout << "Data de Fim: " << agency.getPackets().at(a - 1).getEndDate().getYear() << "/";
		cout << agency.getPackets().at(a - 1).getEndDate().getMonth() << "/";
		cout << agency.getPackets().at(a - 1).getEndDate().getYear() << endl;
		cout << "Preço por Pessoa: " << agency.getPackets().at(a - 1).getPricePerPerson() << endl;
		cout << "Lugares Totais: " << agency.getPackets().at(a - 1).getMaxPersons() << endl;
		cout << "Lugares Disponiveis: " << agency.getPackets().at(a - 1).getDisPersons() << endl;
		getline(cin, f);
		while (f != "S" && f != "N") {
			cout << "Insira ou 'S' ou 'N': ";
			getline(cin, f);
		}
		if (f == "S") {

			vector<Packet> vetorPackets;
			for (int i = 0; i<agency.getPackets().size(); i++) {
				if (i != a - 1) {
					vetorPackets.push_back(agency.getPackets().at(i));
				}
				else { //se removermos este else a função passa a eliminar os pacotes ao enves de os tornar "invisiveis"
					Packet pacote = agency.getPackets().at(i);
					pacote.setId(-pacote.getId());
					vetorPackets.push_back(pacote);
				}
			}
			agency.setPackets(vetorPackets);
			agency.setpacketsInfoHasChanged();
			cout << "Pacote apagado com sucesso." << endl;
		}
		else if (f == "N") {
			cout << "Operacao cancelada por sua ordem. Insira ENTER para retornar." << endl;
			cin.ignore(1000, '\n');
		}
		else {
			cout << "Input invalido. Operacao Cancelada. Insira ENTER para retornar." << endl;
			cin.ignore(1000, '\n');
		}

	}
	else {
		cout << "##############################" << endl;
		cout << "Nao existem pacotes para apagar. Insira ENTER para retornar." << endl;
		cin.ignore(1000, '\n');
	}
	return;
}//Falta ver pacs
/*Menu que modifica um pacote especifico*/
void mod_spe_pac(Agency& agency, int a) {
	bool x = true;
	Date ai, af;
	string pais, dest, t, qs, ws, es, rs, quero;
	int b, q, w, e, r, csto;
	DestinoViag k;
	vector<Packet> pacotes = agency.getPackets();
	Packet pacote = pacotes.at(a);
	bool o;
	do {
		consl_clear();
		cout << "### Menu de alteracao de pacotes ###" << endl;
		cout << "Pacote de id: " << agency.getPackets().at(a).getId() << endl;
		cout << "[1] ALTERAR LOCAIS" << endl;
		cout << "[2] ALTERAR A DATA" << endl;
		cout << "[3] ALTERAR O CUSTO POR PESSOA" << endl;
		cout << "[4] ADICIONAR LUGARES AO PACOTE" << endl;
		cout << "[5] TORNAR DISPONIVEL" << endl;
		cout << "[0] VOLTAR" << endl;
		b = intrec();
		if (b == 1) {
			
			cout << "Insira o país destino.\n";
			getline(cin, pais, '\n');
			pais = trim(pais);
			cout << "Introduza as outras localidades uma a uma. pressione 'Enter' para terminar.\n";
			getline(cin, dest, '\n');
			while (dest != "") {
				if (dest == "") {
					break;
				}
				else {
					t += trim(dest) + ", ";
				}
				getline(cin, dest, '\n');
			}
			if (t != "") {
				t = t.substr(0, t.find_last_of(','));
				t = pais + " - " + t;
			}
			else {
				t = pais;
			}
			int found = t.find('-');
			if (found != string::npos) {
				k.setMainSite(t.substr(0, t.find_first_of('-') - 1));
				k.setSubSites(cid(t.substr(t.find_first_of('-') + 2)));
				pacotes.at(a).setSites(k);
				agency.setPackets(pacotes);
				agency.getpacketsInfoHasChanged();
			}
			else {
				k.setMainSite(t.substr(0, t.find_first_of('-') - 1));
				k.clearsubSites();
				pacotes.at(a).setSites(k);
				agency.setPackets(pacotes);
				agency.getpacketsInfoHasChanged();
			}
			agency.setMVSites();
			agency.setMVSubSites();
			cout << "Locais atualizados com sucesso." << endl;
			cout << "Novo destino do pacote: " << t << endl;
			t = "";
			cout << "Insira ENTER para continuar.";
			cin.ignore(1000, '\n');
		}
		else if (b == 5) {
			pacotes.at(a).setId(-pacotes.at(a).getId());
			agency.setPackets(pacotes);
			agency.setpacketsInfoHasChanged();
			agency.setMVSites();
			agency.setMVSubSites();
			cout << "Este pacote esta agora disponivel." << endl;
			cout << "Insira ENTER para continuar.";
			cin.ignore(1000, '\n');
		}
		else if (b == 2) {
			cout << "Data de Inicio:" << endl;
			ai = lerdata();
			cout << "Data de Fim:" << endl;
			af = lerdata();
			o = cmp_datas(ai, af);
			while (!o) {
				cout << "A data inicial inserida nao pode ser posterior a final." << endl;
				cout << "Data de Inicio:" << endl;
				ai = lerdata();
				cout << "Data de Fim:" << endl;
				af = lerdata();
				o = cmp_datas(ai, af);

			}
			pacotes.at(a).setBeginDate(ai);
			pacotes.at(a).setEndDate(af);
			agency.setPackets(pacotes);
			agency.getpacketsInfoHasChanged();
			cout << "Data do pacote atualizada com sucesso." << endl;
			cout << "Introduza ENTER para continuar.";
			cin.ignore(1000, '\n');
		}
		else if (b == 3) {
			cout << "Introduza um valor novo para o custo por pessoa do pacote: ";
			csto = intrec();
			pacotes.at(a).setPricePerPerson(csto);
			agency.setPackets(pacotes);
			agency.getpacketsInfoHasChanged();
			cout << "Custo por pessoa do pacote atualizado." << endl;
			cout << "Introduza ENTER para continuar.";
			cin.ignore(1000, '\n');
		}
		else if (b == 4) {
			if (pacotes.at(a).getId() <0) {
				cout << "Adicionar lugares a este pacote vai fazer com que o mesmo passe a estar disponivel." << endl;
				cout << "Pretende prosseguir? Introduza 'S' para prosseguir 'N' para cancelar: ";
				getline(cin, quero, '\n');
			}
			else {
				quero = "S";
			}
			if (quero == "S") {
				cout << "Insira lugares a adicionar ao pacote: ";
				e = intrec();
				while (e == 0) {
					cout << "Nao pode acionar 0 lugares." << endl;
					cout << "Insira lugares a adicionar ao pacote: ";
					e = intrec();
				}
				/*Caso o numero de lugares adicionais ultrapassar o maximo o programa pergunta ao utilizador se ele pretende
				aumentar os lugares maximos*/
				if (pacotes.at(a).getDisPersons() + e > pacotes.at(a).getMaxPersons()) {
					cout << "O numero de lugares adicionado ira aumentar o numero de lugares totais do pacote." << endl;
					cout << "Pretende prosseguir?(Insira 'S' para confirmar ou 'N' para cancelar): ";
					getline(cin, rs, '\n');
					if (rs == "S") {
						pacotes.at(a).setId(abs(pacotes.at(a).getId()));
						pacotes.at(a).setDisPersons(pacotes.at(a).getDisPersons() + e);
						pacotes.at(a).setMaxPersons(pacotes.at(a).getDisPersons());
						agency.setPackets(pacotes);
						agency.setpacketsInfoHasChanged();
						cout << "Lugares disponiveis atualizados com sucesso." << endl;
						cout << "Introduza ENTER para continuar.";
						cin.ignore(1000, '\n');
					}
				}
				else {
					pacotes.at(a).setId(abs(pacotes.at(a).getId()));
					pacotes.at(a).setDisPersons(pacotes.at(a).getDisPersons() + e);
					agency.setPackets(pacotes);
					agency.setpacketsInfoHasChanged();
					cout << "Lugares disponiveis atualizados com sucesso." << endl;
					cout << "Introduza ENTER para continuar.";
					cin.ignore(1000, '\n');
				}
			}
		}
		else if (b == 0) {
			x = false;
		}
	} while (x == true);
	return;
}
/*Menu que apenas le um id de um pacote a modificar*/
void mod_pac(Agency& agency) {
	string b;
	int a;
	vector<int> c;
	do {
		cout << "### MODIFICAR PACOTE ###" << endl;
		cout << "Insira o id do pacote a modificar. Insira '0' para ver os pacotes." << endl;
		a = abs(intrec());
		if (a == 0) {
			ver_pac(agency);
			consl_clear();
		}
	} while (a == 0);
	for (int i = 0; i < agency.getPackets().size(); i++) {
		if (a == abs(agency.getPackets().at(i).getId())) {
			a = i;
			mod_spe_pac(agency,a);
			break;
		}
		if (i == agency.getPackets().size() - 1) {
			cout << "Nenhum pacote tem o ID: " << a<<endl;
			cout << "Insira ENTER para retornar.";
			cin.ignore(1000, '\n');
		}
	}
}
/*Menu geral dos pacotes*/
void pac(Agency& agency) {
	int a;
	bool c = true;
	do {
		consl_clear();
		cout << "### MENU DE PACOTES ###" << endl;
		cout << "[1] CRIAR PACOTE" << endl;
		cout << "[2] APAGAR PACOTE" << endl;
		cout << "[3] VER PACOTES" << endl;
		cout << "[4] MODIFICAR PACOTE" << endl;
		cout << "[0] VOLTAR" << endl;
		a = intrec();
		if (a == 1) {
			cri_pac(agency);
		}
		else if (a == 2) {
			if (agency.getPackets().size() > 0) {
				del_pac(agency);
			}
			else {
				cout << "Nao existem pacotes para apagar. Insira ENTER para continuar." << endl;
				cin.ignore(1000, '\n');
			}

		}
		else if (a == 3) {
			ver_pac(agency);
		}
		else if (a == 4) {
			mod_pac(agency);
		}
		else if (a == 0) {
			c = false;
		}
		else {
			cout << "Valor Inválido.\n";
		}
	} while (c);
}


/*Criação de clientes*/
void cri_cli(Agency& agency) {
	string a, d, g, l, mor, mora,cp,cp4,cp3;
	g = "";
	bool cpcheck = false;
	int b, c, f, o, p4, s3;
	consl_clear();
	cout << "### CRIAR CLIENTE ###" << endl;
	cout << "Insira o nome: ";
	getline(cin, a, '\n');
	a = trim(a);
	cout << "Introduza o nif: ";
	b = lernif();
	cout << "Introduza o numero de pessoas no agregado familiar: ";
	c = intrec();
	cout << "Introduza a morada do cliente:" << endl;
	cout << "Nome da Rua: ";
	getline(cin, mor, '\n');
	mora = mor + " / ";
	cout << "N de Edificio: ";
	o = intrec();
	mora += to_string(o) + " / ";
	cout << "N da porta (Se nao aplicavel insira '-'): ";
	getline(cin, mor, '\n');
	mora += mor + " / ";
	do {
		/*Uma pequena função para ler os codigos postais*/
		cout << "Codigo postal (0000-000): ";
		getline(cin, cp, '\n');
		cp = trim(cp);
		if (cp.find_first_of("-") != string::npos) {
			cp4 = cp.substr(0, cp.find_first_of("-"));
			cp3 = cp.substr(cp.find_first_of("-") + 1);
			if (isnum(cp4)) {
				if (cp4.size()==4 && stoi(cp4) < 10000) {
					if (isnum(cp3)) {
						if (cp3.size()==3 && stoi(cp3) < 1000) {
							cpcheck = true;
						}
					}
				}
			}
		}
		if (cpcheck == false) {
			cout << "Introduza um codigo de postal valido." << endl;
		}
	} while (cpcheck == false);
	mor = trim(cp);
	mora += mor + " / ";
	cout << "Localidade: ";
	getline(cin, mor, '\n');
	mora += mor;

	cout << "##############################" << endl;
	cout << "Confirma a informacao do cliente?" << endl << "Insira S para confirmar ou N para cancelar." << endl;
	cout << "Nome: " << a << endl;
	cout << "nif: " << b << endl;
	cout << "Numero de pessoas no agregado familiar: " << c << endl;
	cout << "Morada: " << mora << endl;
	cout << "##############################" << endl;
	getline(cin, l, '\n');
	while (l != "S" && l != "N") {
		cout << "Insira ou 'S' ou 'N': ";
		getline(cin, l);
	}
	if (l == "S") {
		vector<string> h;
		h.push_back(a);
		h.push_back(to_string(b));
		h.push_back(to_string(c));
		h.push_back(mora);
		h.push_back("0");
		h.push_back("0");
		agency.addClient(h);
		agency.setclientsInfoHasChanged();
		
		cout << "Operacao concluida com sucesso. Insira ENTER para continuar." << endl;
		cin.ignore(1000, '\n');
	}
	else if (l == "N") {
		cout << "Operacao Cancelada. Insira ENTER para continuar." << endl;
		cin.ignore(1000, '\n');
	}
	else {
		cout << "Input invalido. Operacao Cancelada. Insira ENTER para continuar." << endl;
		cin.ignore(1000, '\n');
	}
}
/*Modificar Clientes*/
void mod_cli(Agency &agency,int g) {
	int a, n, p, o, p4, s3;
	string b, mor, mora, cp, cp4, cp3;
	bool cpcheck = false;
	Client cliente = agency.getClients().at(g);
	vector<Client> newclients;
	bool x = true;
	do {
		cliente = agency.getClients().at(g);
		newclients.clear();
		consl_clear();
		cout << "### Modificar o cliente " << agency.getClients().at(g).getName() << " ###" << endl;
		cout << "[1] ATUALIZAR NOME" << endl;
		cout << "[2] ATUALIZAR NIF" << endl;
		cout << "[3] ATUALIZAR MORADA" << endl;
		cout << "[4] ATUALIZAR NUMERO DE PESSOAS NO AGREGADO FAMILIAR" << endl;
		cout << "[0] VOLTAR" << endl;
		cout << "####################" << endl;
		a = intrec();
		if (a == 1) {
			cout << "Insira o novo nome do cliente: ";
			getline(cin, b, '\n');
			cliente.setName(b);
			for (int i = 0; i < agency.getClients().size(); i++) {
				if (i != g) {
					newclients.push_back(agency.getClients().at(i));
				}
				else {
					newclients.push_back(cliente);
				}
			}
			agency.setClients(newclients);
			agency.setclientsInfoHasChanged();
			cout << "Nome atualizado com sucesso.\nNovo nome: " << agency.getClients().at(g).getName();
			cout << endl << "Insira ENTER para continuar.";
			cin.ignore(1000, '\n');
		}
		else if (a == 2) {
			cout << "Insira o novo nif: ";
			n = lernif();
			cliente.setVATnumber(n);
			for (int i = 0; i < agency.getClients().size(); i++) {
				if (i != g) {
					newclients.push_back(agency.getClients().at(i));
				}
				else {
					newclients.push_back(cliente);
				}
			}
			agency.setClients(newclients);
			agency.setclientsInfoHasChanged();
			cout << "Nif atualizado com sucesso.\nNovo nif: " << agency.getClients().at(g).getVATnumber();
			cout << endl << "Insira ENTER para continuar.";
			cin.ignore(1000, '\n');
		}
		else if (a == 3) {
			string newmorada;
			cout << "Introduza a morada do cliente:" << endl;
			cout << "Nome da Rua: ";
			getline(cin, mor, '\n');
			newmorada =trim(mor);
			cout << "N de Edificio: ";
			o = intrec();
			newmorada+=" / " + to_string(o);
			cout << "N da porta (Se nao aplicavel insira '-'): ";
			getline(cin, mor, '\n');
			newmorada += " / " + trim(mor);
			do {
				cout << "Codigo postal (0000-000): ";
				getline(cin, cp, '\n');
				cp = trim(cp);
				if (cp.find_first_of("-") != string::npos) {
					cp4 = cp.substr(0, cp.find_first_of("-"));
					cp3 = cp.substr(cp.find_first_of("-") + 1);
					if (isnum(cp4)) {
						if (cp4.size() == 4 && stoi(cp4) < 10000) {
							if (isnum(cp3)) {
								if (cp3.size() == 3 && stoi(cp3) < 1000) {
									cpcheck = true;
								}
							}
						}
					}
				}
				if (cpcheck == false) {
					cout << "Introduza um codigo de postal valido." << endl;
				}
			} while (cpcheck == false);
			mor = trim(cp);
			newmorada += " / " + trim(mor);;
			cout << "Localidade: ";
			getline(cin, mor, '\n');
			newmorada += " / " + trim(mor);
			cliente.setAddress(newmorada);
			for (int i = 0; i < agency.getClients().size(); i++) {
				if (i != g) {
					newclients.push_back(agency.getClients().at(i));
				}
				else {
					newclients.push_back(cliente);
				}
			}
			agency.setClients(newclients);
			agency.setclientsInfoHasChanged();
			cout << endl << "Insira ENTER para continuar.";
			cin.ignore(1000, '\n');
		}
		else if (a == 4) {
			cout << "Insira o numero de elementos no agregado familiar: ";
			p = intrec();
			cliente.setFamilySize(p);
			for (int i = 0; i < agency.getClients().size(); i++) {
				if (i != g) {
					newclients.push_back(agency.getClients().at(i));
				}
				else {
					newclients.push_back(cliente);
				}
			}
			agency.setClients(newclients);
			agency.setclientsInfoHasChanged();
			cout << "Numero de elementos no agregado atualizado.\nNumero de elementos no agregado atual: " << agency.getClients().at(g).getFamilySize();
			cout << endl << "Insira ENTER para continuar.";
			cin.ignore(1000, '\n');
		}
		else if (a == 0) {
			x = false;
			consl_clear();
		}
	} while (x == true);
}
/*Menu especifico de cada cliente*/
void cliespe(Agency &agency, int g) {
	int a,f,c,d,idpacote;
	bool t;
	do {
		consl_clear();
		cout << "### Ficha de " << agency.getClients().at(g).getName() << " ###" << endl;
		cout << "[1] INFORMACOES DE CLIENTE" << endl;
		cout << "[2] ATUALIZAR INFORMACOES" << endl;
		cout << "[3] PACOTES RECOMENDADOS" << endl;
		cout << "[0] VOLTAR" << endl;
		a = intrec();

		if (a == 1) {
			cout << "##########" << endl;
			cout << "Nome: " << agency.getClients().at(g).getName() << endl;
			cout << "Morada: " << agency.getClients().at(g).getAddress().getStreet() << " / " << agency.getClients().at(g).getAddress().getDoorNumber() << " / ";
			cout << agency.getClients().at(g).getAddress().getFloor() << " / " << agency.getClients().at(g).getAddress().getPostalCode() << " / " << agency.getClients().at(g).getAddress().getLocation() << endl;
			cout << "Numero de Pessoas no Agregado: " << agency.getClients().at(g).getFamilySize() << endl;
			cout << "Pacotes comprados: " << agency.getClients().at(g).getPacketList().size() << endl;
			if (agency.getClients().at(g).getPacketList().size() > 0) {
				cout << "Id dos pacotes comprados: ";
				for (int i = 0; i < agency.getClients().at(g).getPacketList().size(); i++) {
					cout << agency.getClients().at(g).getPacketList().at(i).getId() << " ";

				}
				cout <<endl <<"Dinheiro gasto em pacotes: "<< agency.getClients().at(g).getMoneySpent();
				cout << endl << "##########" << endl;
			}
			else {
				cout << "Dinheiro gasto em pacotes: " << agency.getClients().at(g).getMoneySpent() << endl;
				cout << "##########" << endl;
			}
			cout << "Insira ENTER para continuar.";
			cin.ignore(1000, '\n');
		}
		else if (a == 0) {
			return;
		}
		else if (a == 2) {
			mod_cli(agency,g);
		}
		else if (a == 3) {
			int n;
			cout << "Insira um numero N." << endl;
			cout << "Este numero vai servir para ver as N localidades mais visitadas fazendo o pacote recomendado mais abrangente."<<endl<<"Input: ";
			n = intrec();
			map<string, int> Destinos = agency.getMVSubSites();
			multimap<int, string> sorteddest;
			/*Troca a key com o value e fica guardado num multimap sorteddest*/
			map<string, int> ::iterator its = Destinos.begin();
			for (int k = 0; k < Destinos.size(); k++) {
				sorteddest.insert(make_pair(its->second, its->first));
				its++;
			}
			/*Cria um set ordenado pelas maiores keys do multimap de forma a que este set seja um set com */
			multimap<int, string>::reverse_iterator itera = sorteddest.rbegin();
			set<string> nlocais;
			int keep = n;
			if (n > sorteddest.size())
				n = sorteddest.size();
			for (int i = 0; i < n; i++) {
				nlocais.insert(itera->second);
				itera++;
			}
			/*Neste momento o set nlocais esta ordenado por numero de visitas aos sitios*/
			/*limpar é uma variavel que é utilizada para dar trim e por em maiscula a palavra*/
			string limpar;
			/*setdecli +e um set de todos os pacotes comprados pelo cliente*/
			set<string> setdecli;
			for (int k = 0; k < agency.getClients().at(g).getPacketList().size(); k++) {
				for (int j = 0; j < agency.getClients().at(g).getPacketList().at(k).getSites().getSubSites().size(); j++) {
					limpar=(trim(agency.getClients().at(g).getPacketList().at(k).getSites().getSubSites().at(j)));
					transform(limpar.begin(), limpar.end(), limpar.begin(), ::tolower);
					limpar[0] = toupper(limpar[0]);
					setdecli.insert(limpar);
				}
			}
			set<string> diff;
			/*diff é um set com os locais não visitados pelo cliente e pelos locais do cliente que não pertencem aos
			mais vizitados*/
			set_difference(nlocais.begin(), nlocais.end(), setdecli.begin(), setdecli.end(), inserter(diff, diff.begin()));
			/*Esta interseção novamente com o set de locais mais vizitados remove os locais do cliente que 
			não pertencem aos locais mais visitados deixando assim os locais a visitar pelo cliente*/
			set_intersection(nlocais.begin(), nlocais.end(), diff.begin(), diff.end(), inserter(diff, diff.begin()));
			string testes;
			if (diff.size() > 0) {
				/*Dentro dos pacotes todos da agencia este ciclo for vai dar cout do primeiro em que existir
				um local não visitado pelo cliente e que este local pertença aos mais visitados*/
				for (int k = 0; k < agency.getPackets().size(); k++) {
					for (int i = 0; i < agency.getPackets().at(k).getSites().getSubSites().size(); i++) {
						testes = trim(agency.getPackets().at(k).getSites().getSubSites().at(i));
						transform(testes.begin(), testes.end(), testes.begin(), ::tolower);
						testes[0] = toupper(testes[0]);
						if (diff.find(testes) != diff.end()) {
							cout << "---Pacote Recomendado---" << endl;
							string linha = " - ";
							cout << "Id: " << agency.getPackets().at(k).getId() << endl;
							cout << "Localidades a visitar: " << agency.getPackets().at(k).getSites().getMainSite();
							if (agency.getPackets().at(k).getSites().getSubSites().size() > 0) {
								for (int j = 0; j < agency.getPackets().at(k).getSites().getSubSites().size(); j++) {
									linha += agency.getPackets().at(k).getSites().getSubSites().at(j) + ", ";
								}
								linha = linha.substr(0, linha.find_last_of(','));
								cout << linha;
							}
							cout << endl;
							cout << "Data de Inicio: " << agency.getPackets().at(k).getBeginDate().getYear() << "/";
							cout << agency.getPackets().at(k).getBeginDate().getMonth() << "/";
							cout << agency.getPackets().at(k).getBeginDate().getDay() << endl;
							cout << "Data de Fim: " << agency.getPackets().at(k).getEndDate().getYear() << "/";
							cout << agency.getPackets().at(k).getEndDate().getMonth() << "/";
							cout << agency.getPackets().at(k).getEndDate().getDay() << endl;
							cout << "Preço por Pessoa: " << agency.getPackets().at(k).getPricePerPerson() << endl;
							cout << "Lugares Totais: " << agency.getPackets().at(k).getMaxPersons() << endl;
							cout << "Lugares Disponiveis: " << agency.getPackets().at(k).getDisPersons();
							cout << endl << "------------------------" << endl;
							cout << "Pretende vender este pacote ao cliente?." << endl;
							string soun;
							do {
								cout << "Insira 'S' ou 'N' : ";
								getline(cin, soun, '\n');
							} while (soun != "S" && soun != "N");
							if (soun == "S") {
								f = k;
									d = agency.getPackets().at(k).getDisPersons();
									do {
										t = false;
										cout << "Insira quantos lugares quer vender." << endl;
										c = intrec();
										if (c > d) {
											cout << "Não pode vender mais lugares do que os que existem." << endl;
											cout << "Insira ENTER para retornar.";
											cin.ignore(1000, '\n');
											return;
										}
										else if (c == 0) {
											cout << "Não pode vender 0 lugares a um cliente." << endl;
											cout << "Insira ENTER para retornar.";
											cin.ignore(1000, '\n');
											return;
										}
										else {
											t = true;
										}

									} while (!t);
									vector<Packet> pacotes = agency.getPackets();
									//altera os lugares disponiveis do pacote no indice f para ser esse valor menos os lugares vendidos
									pacotes.at(f).setDisPersons(pacotes.at(f).getDisPersons() - c);
									/*Quando um cliente compra um pacote este tem de ser adicionado aos pacotes comprados pelo cliente mas apenas se este não o tiver
									comprado antes pq se nao um cliente que comprasse um pacote de id 3 quatro vezes ia ter na sua ficha de cliente 4 vezes o mesmo
									pacote. Eu interpretei como se não houvesse repetição do id de pacotes comprados ou seja quando ele compra um pacote esse id fica
									guardado apenas para saber que esse pacote foi comprado e por tanto nao faz sentido ele ter essa informação n vezes*/
									vector<Client> clientes = agency.getClients();
									if (clientes.at(g).getTotalPurchased() > 0) {
										for (int k = 0; k < clientes.at(g).getTotalPurchased(); k++) {
											if (clientes.at(g).getPacketList().at(k).getId() == f) {
												if (pacotes.at(f).getDisPersons() == 0) {
													pacotes.at(f).setId(-pacotes.at(f).getId());
												}
												clientes.at(g).addMoneySpent(c * pacotes.at(f).getPricePerPerson());
												agency.setClients(clientes);
												agency.setPackets(pacotes);
												agency.setclientsInfoHasChanged();
												agency.setpacketsInfoHasChanged();
												agency.setMVSites();
												agency.setMVSubSites();
												cout << "Foram vendidos " << c << " lugares do pacote de id: #" << abs(pacotes.at(f).getId()) << ". Ao cliente : " << clientes.at(g).getName() << "\n#nif:" << clientes.at(g).getVATnumber() << endl;
												cout << "Insira ENTER para voltar.";
												cin.ignore(1000, '\n');
												return;
											}
											if (k == clientes.at(g).getTotalPurchased() - 1 && clientes.at(g).getPacketList().at(k).getId() != a) {
												vector<Packet> cliente = clientes.at(g).getPacketList();
												cliente.push_back(pacotes.at(f));
												clientes.at(g).setPacketList(cliente);
												clientes.at(g).setTotalPurchased(clientes.at(g).getTotalPurchased() + 1);
												clientes.at(g).addMoneySpent(c * pacotes.at(f).getPricePerPerson());
												if (pacotes.at(f).getDisPersons() == 0) {
													pacotes.at(f).setId(-pacotes.at(f).getId());
												}
												agency.setClients(clientes);
												agency.setPackets(pacotes);
												agency.setclientsInfoHasChanged();
												agency.setpacketsInfoHasChanged();
												agency.setMVSites();
												agency.setMVSubSites();
												cout << "Foram vendidos " << c << " lugares do pacote de id: #" << abs(pacotes.at(f).getId()) << ". Ao cliente : " << clientes.at(g).getName() << "\n#nif:" << clientes.at(g).getVATnumber() << endl;
												cout << "Insira ENTER para voltar.";
												cin.ignore(1000, '\n');
												return;
											}
										}
									}
									else {
										vector<Packet> cliente = clientes.at(g).getPacketList();
										cliente.push_back(pacotes.at(f));
										clientes.at(g).setTotalPurchased(clientes.at(g).getTotalPurchased() + 1);
										clientes.at(g).setPacketList(cliente);
										clientes.at(g).addMoneySpent(c * pacotes.at(f).getPricePerPerson());
										if (pacotes.at(f).getDisPersons() == 0) {
											pacotes.at(f).setId(-pacotes.at(f).getId());
										}
										agency.setClients(clientes);
										agency.setPackets(pacotes);
										agency.setclientsInfoHasChanged();
										agency.setpacketsInfoHasChanged();
										agency.setMVSites();
										agency.setMVSubSites();
										cout << "Foram vendidos " << c << " lugares do pacote de id: #" << abs(pacotes.at(f).getId()) << ". Ao cliente : " << clientes.at(g).getName() << "\n#nif:" << clientes.at(g).getVATnumber() << endl;
										cout << "Insira ENTER para voltar.";
										cin.ignore(1000, '\n');
										return;
									}

							}
							else {
								return;
							}

							}
						}
					}

				}
				else {
					cout << "O cliente ja visitou todos os " << keep << " locais mais vizitados." << endl;
					cout << "Insira ENTER para voltar";
					cin.ignore(1000, '\n');
				}
			}
		}while (a != 0);
}
/*Menu que mostra todos os clientes e o respetivo nif e que permite mandar para o menu que ve a ficha cliente de cada um */
void selectcli(Agency &agency) {
	int a;
	string b;
	consl_clear();
	cout << "####################" << endl;
	for (int i = 0; i < agency.getClients().size(); i++) {
		cout << i + 1 << "-" << agency.getClients().at(i).getName() << "  #nif: " << agency.getClients().at(i).getVATnumber() << endl;
	}
	cout << "####################" << endl;
	cout << "Para selecionar um cliente em específico insira o nif." << endl;
	cout << "Insira '0' para voltar." << endl;
	a = intrec();
	for (int i = 0; i < agency.getClients().size(); i++) {
		if (a == 0) {
			break;
		}
		if (a == agency.getClients().at(i).getVATnumber()) {
			cliespe(agency,i);
			break;
		}
		else if (a != agency.getClients().at(i).getVATnumber() && i == agency.getClients().size() - 1) {
			cout << "Não existe nenhum cliente com este nif." << endl;
			cout << "Insira enter para voltar.";
			cin.ignore(1000, '\n');
		}

	}
	return;
}
/*Menu que apaga clientes*/
void del_cli(Agency& agency) { //Funciona

	string f, c;
	int a, b;
	consl_clear();
	b = -2;
	do {
		cout << "### APAGAR CLIENTE ###" << endl;
		cout << "Insira o nif do cliente a apagar. Insira '0' para ver os clientes existentes ou Introduza 1 para cancelar." << endl;
		a = intrec();
		if (a == 0) {
			selectcli(agency);
		}
		if (a == 1) {
			return;
		}
		consl_clear();
	} while (a == 0);
	for (int k = 0; k < agency.getClients().size(); k++) {
		if (agency.getClients().at(k).getVATnumber() == a) {
			b = k;
			break;
		}
	}
	if (b == -2) {
		cout << "O nif introduzido não corresponde a nenhum cliente registrado. Insira ENTER para retornar";
		cin.ignore(1000, '\n');
		return;
	}
	cout << "####################" << endl;
	cout << "Deseja apagar o seguinte cliente?" << endl << "Insira S para confirmar ou N para cancelar." << endl;
	cout << "Nome: " << agency.getClients().at(b).getName() << endl;
	cout << "nif: " << agency.getClients().at(b).getVATnumber() << endl;
	cout << "Numero de pessoas no agregado familiar: " << agency.getClients().at(b).getFamilySize() << endl;
	cout << "Pacotes comprados: ";
	for (int i = 0; i < agency.getClients().at(b).getPacketList().size(); i++) {
		cout << agency.getClients().at(b).getPacketList().at(i).getId() << " ";
	}
	cout << endl << "Dinheiro Gasto: " << agency.getClients().at(b).getMoneySpent() << endl;
	cout << "Apagar um cliente removera o dinheiro gasto!";
	cout << endl << "####################" << endl;
	string h;
	getline(cin, h, '\n');
	while (h != "S" && h != "N") {
		cout << "Insira ou 'S' ou 'N': ";
		getline(cin, h);
	}
	if (h == "S") {
		vector<Client> a;
		for (int k = 0; k < agency.getClients().size(); k++) {
			if (agency.getClients().at(k).getVATnumber() != agency.getClients().at(b).getVATnumber()) {
				a.push_back(agency.getClients().at(k));
			}
		}
		agency.setClients(a);
		agency.setclientsInfoHasChanged();
		cout << "Cliente apagado com sucesso. Introduza ENTER para retornar." << endl;
		cin.ignore(1000, '\n');
	}
	return;
}
/*Menu geral de clientes*/
void cli(Agency& agency) {
	int a;
	bool c = true;
	do {
		consl_clear();
		cout << "### MENU CLIENTES ###" << endl;
		cout << "[1] CRIAR CLIENTE" << endl;
		cout << "[2] APAGAR CLIENTE" << endl;
		cout << "[3] VER CLIENTE" << endl;
		cout << "[0] VOLTAR" << endl;
		a = intrec();
		if (a == 1) {
			cri_cli(agency);
		}
		else if (a == 2) {
			if (agency.getClients().size() > 0) {
				del_cli(agency);
			}
			else {
				cout << "Nao existem clientes para apagar. Insira ENTER para continuar." << endl;
				cin.ignore(1000, '\n');
			}

		}
		else if (a == 3) {
			selectcli(agency);
		}
		else if (a == 0) {
			c = false;
		}
		else {
			cout << "Valor Inválido.\n";
		}
	} while (c);
}
/*Menu de Vender Pacotes*/
void vend_pac(Agency& agency) {
	int a, b, c, d, e, f,idpacote,x;
	bool t;
	do {
		consl_clear();
		cout << "### Menu de Venda de Pacotes ###" << endl;
		cout << "[1] VENDER UM PACOTE" << endl;
		cout << "[0] VOLTAR" << endl;
		x = intrec();
		if (x==0) {
			return;
		}
		else if (x == 1) {
			do {

				consl_clear();
				cout << "####################" << endl;
				cout << "Insira o nif do cliente ao qual quer vender um pacote.\nInsira 1 para ver os clientes existentes ou 0 para voltar: ";
				a = intrec();
				if (a == 1) {
					selectcli(agency);
				}
				else if (a == 0) {
					consl_clear();
					return;
				}
			} while (a == 1);
			e = -1;
			for (int i = 0; i < agency.getClients().size(); i++) {
				if (a == agency.getClients().at(i).getVATnumber()) {
					e = i;
					break;
				}
			}
			//se o e=-1 quer dizer que o nif introduzido não corresponde a nenhum cliente
			if (e == -1) {
				cout << "Nif inserido nao corresponde a nenhum cliente.\nInsira 0 para tentar novamente ou 1 para cancelar: ";
				a = intrec();
				if (a == 0) {
					vend_pac(agency);
					return;
				}
				else if (a == 1) {
					consl_clear();
					break;
				}
			}
			do {
				cout << "Insira o id do pacote que quer vender ao cliente.\nInsira 0 para ver os pacotes." << endl;
				b = intrec();
				if (b == 0) {
					ver_pac(agency);
					consl_clear();
				}
			} while (b == 0);
			idpacote = b;
			//b é o numero de lugares disponiveis
			for (int i = 0; i < agency.getPackets().size(); i++) {
				if (b == abs(agency.getPackets().at(i).getId())) {
					b = i;
					break;
				}
				if (i == agency.getPackets().size() - 1 && b != abs(agency.getPackets().at(i).getId())) {
					cout << "Nenhum pacote tem o ID: " << a;
					cout << "Insira ENTER para retornar.";
					cin.ignore(1000, '\n');
					return;
				}
			}
			f = b;
			if (agency.getPackets().at(f).getId() < 0) {
				cout << "Este pacote nao esta disponivel." << endl;
				cout << "Insira ENTER para retornar.";
				cin.ignore(1000, '\n');
				return;
			}
			d = agency.getPackets().at(f).getDisPersons();
			//este do so deixa o utilizador prosseguir assim que ele inserir um valor valido para os lugares a vender
			do {
				t = false;
				cout << "Insira quantos lugares quer vender." << endl;
				c = intrec();
				if (c > d) {
					cout << "Não pode vender mais lugares do que os que existem." << endl;
					cout << "Insira ENTER para retornar.";
					cin.ignore(1000, '\n');
					return;
				}
				else if (c == 0) {
					cout << "Não pode vender 0 lugares a um cliente." << endl;
					cout << "Insira ENTER para retornar.";
					cin.ignore(1000, '\n');
					return;
				}
				else {
					t = true;
				}

			} while (!t);
			vector<Packet> pacotes = agency.getPackets();
			//altera os lugares disponiveis do pacote no indice f para ser esse valor menos os lugares vendidos
			pacotes.at(f).setDisPersons(pacotes.at(f).getDisPersons() - c);
			/*Quando um cliente compra um pacote este tem de ser adicionado aos pacotes comprados pelo cliente mas apenas se este não o tiver
			comprado antes pq se nao um cliente que comprasse um pacote de id 3 quatro vezes ia ter na sua ficha de cliente 4 vezes o mesmo
			pacote. Eu interpretei como se não houvesse repetição do id de pacotes comprados ou seja quando ele compra um pacote esse id fica
			guardado apenas para saber que esse pacote foi comprado e por tanto nao faz sentido ele ter essa informação n vezes*/
			vector<Client> clientes = agency.getClients();
			if (clientes.at(e).getTotalPurchased() > 0) {
				for (int k = 0; k < clientes.at(e).getTotalPurchased(); k++) {
					if (clientes.at(e).getPacketList().at(k).getId() == idpacote) {
						if (pacotes.at(f).getDisPersons() == 0) {
							pacotes.at(f).setId(-pacotes.at(f).getId());
						}
						clientes.at(e).addMoneySpent(c * pacotes.at(f).getPricePerPerson());
						agency.setClients(clientes);
						agency.setPackets(pacotes);
						agency.setclientsInfoHasChanged();
						agency.setpacketsInfoHasChanged();
						agency.setMVSites();
						cout << "Foram vendidos " << c << " lugares do pacote de id: #" << abs(pacotes.at(f).getId()) << ". Ao cliente : " << clientes.at(e).getName() << "\n#nif:" << clientes.at(e).getVATnumber() << endl;
						cout << "Insira ENTER para voltar.";
						cin.ignore(1000, '\n');
						return;
					}
					if (k == clientes.at(e).getTotalPurchased() - 1 && clientes.at(e).getPacketList().at(k).getId() != a) {
						vector<Packet> cliente = clientes.at(e).getPacketList();
						cliente.push_back(pacotes.at(f));
						clientes.at(e).setPacketList(cliente);
						clientes.at(e).setTotalPurchased(clientes.at(e).getTotalPurchased() + 1);
						clientes.at(e).addMoneySpent(c * pacotes.at(f).getPricePerPerson());
						if (pacotes.at(f).getDisPersons() == 0) {
							pacotes.at(f).setId(-pacotes.at(f).getId());
						}
						agency.setClients(clientes);
						agency.setPackets(pacotes);
						agency.setclientsInfoHasChanged();
						agency.setpacketsInfoHasChanged();
						agency.setMVSites();
						cout << "Foram vendidos " << c << " lugares do pacote de id: #" << abs(pacotes.at(f).getId()) << ". Ao cliente : " << clientes.at(e).getName() << "\n#nif:" << clientes.at(e).getVATnumber() << endl;
						cout << "Insira ENTER para voltar.";
						cin.ignore(1000, '\n');
						return;
					}
				}
			}
			else {
				vector<Packet> cliente = clientes.at(e).getPacketList();
				cliente.push_back(pacotes.at(f));
				clientes.at(e).setTotalPurchased(clientes.at(e).getTotalPurchased() + 1);
				clientes.at(e).setPacketList(cliente);
				clientes.at(e).addMoneySpent(c * pacotes.at(f).getPricePerPerson());
				if (pacotes.at(f).getDisPersons() == 0) {
					pacotes.at(f).setId(-pacotes.at(f).getId());
				}
				agency.setClients(clientes);
				agency.setPackets(pacotes);
				agency.setclientsInfoHasChanged();
				agency.setpacketsInfoHasChanged();
				agency.setMVSites();
				cout << "Foram vendidos " << c << " lugares do pacote de id: #" << abs(pacotes.at(f).getId()) << ". Ao cliente : " << clientes.at(e).getName() << "\n#nif:" << clientes.at(e).getVATnumber() << endl;
				cout << "Insira ENTER para voltar.";
				cin.ignore(1000, '\n');
				return;
			}
		}
	}while (x != 0);
}
/*Informação da Agencia*/
void inf_age(Agency& agency) {
	int c, a,b,e,n;
	bool check = true;
	string caps,ola;
	c = 0;
	a = 0;
	do {
		consl_clear();
		cout<< "### Menu de Informacoes da agencia ###" << endl;
		cout << "[1] INFORMACOES GERAIS" << endl;
		cout << "[2] LOCAIS MAIS VISITADOS" << endl;
		cout << "[0] VOLTAR" << endl;

		b = intrec();
		if (b == 1) {
			consl_clear();
			cout << "####################" << endl;
			cout << "Nome da Agencia: " << agency.getName() << endl;
			cout << "nif: " << agency.getVATnumber() << endl;
			cout << "Numero de clientes: " << agency.getClients().size() << endl;
			cout << "Dinheiro acumulado em vendas: ";
			for (size_t k = 0; k < agency.getPackets().size(); k++) {
				a += (agency.getPackets().at(k).getMaxPersons() - agency.getPackets().at(k).getDisPersons()) * agency.getPackets().at(k).getPricePerPerson();
			}
			cout << a << endl;
			cout << "Nome do ficheiro que contem a informacao da agencia: " << agency.getName() << ".txt" << endl;
			cout << "Nome do ficheiro que contem a informacao dos clientes: " << agency.getclientsfilename() << endl;
			cout << "Nome do ficheiro que contem a informacao dos pacotes: " << agency.getpacketsfilename() << endl;
			cout << "####################" << endl;
			cout << "Insira ENTER para voltar." << endl;
			cin.ignore(1000, '\n');
		}
		else if (b == 2) {
			int abc;
			/*cria um mapa de destinos igual aos locais mais visitaods da agencia*/
			map<string, map<string, int>>::iterator it = agency.getMVSites().begin();
			map<string, int> Destinos;
			for (auto& par : agency.getMVSites()) {
				map<string, int> mapi = par.second;
				for (auto& valores : mapi) {
					map<string, int>::iterator it =  Destinos.find(valores.first);
					if (it != Destinos.end()) {
						it->second++;
					}
					else {
						Destinos.insert(make_pair(valores.first, valores.second));
					}
				}
			}
			/*cria um multimap em que as keys foram trocadas com os valores permitindo assim ordenar por mais visitados*/
			multimap<int, string> sorteddest;
			map<string, int> ::iterator its =Destinos.begin();
			for (int k = 0; k < Destinos.size(); k++) {
				sorteddest.insert(make_pair(its->second, its->first));
				its++;
			}
			cout << "Insira um numero, N para ver os N lugares mais visitados: ";
			abc = intrec();
			while (abc < 1) {
				cout << "Introduza um numero superior a 0: ";
				abc = intrec();
			}
			cout << "---------------" << endl;
			/*Cria um set ordenado com os locais mais visitados primeiro usando um reverse iterator*/
			multimap<int, string>::reverse_iterator itera = sorteddest.rbegin();
			if (abc > sorteddest.size())
				abc = sorteddest.size();
			for (int i = 0; i < abc; i++) {
				cout << itera->second << " - " << itera->first<<" viagens."<<endl;
				itera++;
			}
			cout << "---------------" << endl;
			cout << "Insira ENTER para voltar";
			cin.ignore(1000, '\n');
		}
		else if (b == 0) {
			check = false;
		}
	} while (check);
}

/*Menu Principal*/
void mainMenu(Agency& agency){
	int a = 0;
	bool c = true;
	do {
		consl_clear();
		cout << "### Menu de Gestao da Agencia " << agency.getName() << " ###" << endl;
		cout << "[1] PACOTES" << endl;
		cout << "[2] CLIENTES" << endl;
		cout << "[3] INFORMACOES DA AGENCIA" << endl;
		cout << "[4] VENDAS" << endl;
		cout << "[0] SAIR" << endl;
		a = intrec();
		if (a == 1) {
			pac(agency);
		}
		else if (a == 2) {
			cli(agency);
		}
		else if (a == 3) {
			inf_age(agency);
		}
		else if (a == 4) {
			vend_pac(agency);
		}
		else if (a == 0) {
			if (agency.getclientsInfoHasChanged()) {
				refresh_cli(agency);
			}
			if (agency.getpacketsInfoHasChanged()) {
				refresh_pac(agency);
			}
			return;
		}
	} while (c);
}
    
