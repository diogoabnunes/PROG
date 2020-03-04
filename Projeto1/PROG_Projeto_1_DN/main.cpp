// Projeto 1 | PROG MIEIC | Diogo Nunes
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
using namespace std;

//------- REMOVER ESPAÇOS NO INICIO E NO FIM DE UMA STRING ----------- (FEITO)
void rtrim(string &s)
{
	s.erase(s.find_last_not_of(" ") + 1);
}
void ltrim(string &s)
{
	s.erase(0, s.find_first_not_of(" "));
}
void trim(string &s)
{
	rtrim(s);
	ltrim(s);
}

//------STRUCTS-------------
struct Address
{
	string rua;
	string nporta;
	string nandar; // "-" se não aplicável
	string codpostal;
	string local;
};
struct Date
{
	int year;
	int month;
	int day;
};
struct TravelPack
{
	int id;
	string percurso;
	Date datai;
	Date dataf;
	int priceperperson;
	int nmaxperson;
	int ndisponiveis;
};
struct Client
{
	string nome;
	int nif;
	int agregado_familiar;
	Address morada;
	string packs_comprados;
};
struct Agency
{
	string nome;
	string nif;
	Address morada;
	string url;
	vector <Client> clientes;
	vector <TravelPack> travel_packs;
};

bool valid_year(int iday, int fday, int imonth, int fmonth, int iyear, int fyear)
{
	if (iday < fday)
	{
		if (imonth <= fmonth)
		{
			if (fyear >= iyear)
				return true;
		}
		else
		{
			if (fyear > iyear)
				return true;
		}
	}
	if (iday = fday)
	{
		if (imonth < fmonth)
		{
			if (fyear >= iyear)
				return true;
		}
		else
		{
			if (fyear > iyear)
				return true;
		}
	}
	else // if (iday > fday)
	{
		if (imonth < fmonth)
		{
			if (fyear >= iyear)
				return true;
		}
		else
		{
			if (fyear > iyear)
				return true;
		}
	}
	return false;
}

//-------FUNÇÕES PRINCIPAIS-----------------
void add_TravelPack(string &td, vector <TravelPack> &v)
{
	fstream f;
	f.open(td, ios::in);
	string last_pack_created;
	getline(f, last_pack_created); // READ THE LAST PACK CREATED
	f.close();

	TravelPack new_pack;
	new_pack.id = stoi(last_pack_created) + 1;	// APPEND TO PACKS THE ID OF THE NEW PACK (OLD +1)

	cin.clear();
	cin.ignore(1000, '\n');

	cout << "Destino: ";
	getline(cin, new_pack.percurso);
	cout << "Data de inicio: " << endl;
	bool check;
	do
	{
		cout << "Dia: ";
		if (cin >> new_pack.datai.day && new_pack.datai.day >=1 && new_pack.datai.day <=31)
			check = true;
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			check = false;
		}
	} while (!check);
	do
	{
		cout << "Mes: ";
		if (cin >> new_pack.datai.month && new_pack.datai.month >= 1 && new_pack.datai.month <=12)
			check = true;
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			check = false;
		}
	} while (!check);
	do
	{
		cout << "Ano: ";
		if (cin >> new_pack.datai.year && new_pack.datai.year >= 2019 && new_pack.datai.year < 3000)
			check = true;
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			check = false;
		}
	} while (!check);

	cout << "Data de fim: " << endl;
	do
	{
		cout << "Dia: ";
		if (cin >> new_pack.dataf.day && new_pack.dataf.day >= 1 && new_pack.dataf.day <= 31)
			check = true;
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			check = false;
		}
	} while (!check);
	do
	{
		cout << "Mes: ";
		if (cin >> new_pack.dataf.month && new_pack.dataf.month >= 1 && new_pack.dataf.month <= 12)
			check = true;
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			check = false;
		}
	} while (!check);
	do
	{
		cout << "Ano: ";
		if (cin >> new_pack.dataf.year && new_pack.dataf.year >= 2019 && new_pack.dataf.year < 3000 && 
			valid_year(new_pack.datai.day, new_pack.dataf.day, new_pack.datai.month, new_pack.dataf.month, new_pack.datai.year, new_pack.dataf.year))
			check = true;
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			check = false;
		}
	} while (!check);

	do
	{
		cout << "Preco por pessoa: ";
		if (cin >> new_pack.priceperperson)
			check = true;
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			check = false;
		}
	} while (!check);
	do
	{
		cout << "Numero de lugares disponiveis: ";
		if (cin >> new_pack.nmaxperson)
			check = true;
		else
		{
			cin.clear();
			cin.ignore(1000, '\n');
			check = false;
		}
	} while (!check);
	new_pack.ndisponiveis = new_pack.nmaxperson;

	v.push_back(new_pack);

	f.open(td, ios::out);
	int i = 0;
	f << new_pack.id << endl;
	f << v.at(i).id << endl;
	f << v.at(i).percurso << endl;
	f << setfill('0') << setw(4) << to_string(v.at(i).datai.year) << "/" << setw(2) << to_string(v.at(i).datai.month) << "/" << setw(2) << to_string(v.at(i).datai.day) << endl;
	f << setfill('0') << setw(4) << to_string(v.at(i).dataf.year) << "/" << setw(2) << to_string(v.at(i).dataf.month) << "/" << setw(2) << to_string(v.at(i).dataf.day) << endl << setfill('0');
	f << v.at(i).priceperperson << endl;
	f << v.at(i).nmaxperson << endl;
	f << v.at(i).ndisponiveis << endl;
	
	for (unsigned int i = 1; i < v.size(); i++)
	{
		f << "::::::::::" << endl;
		f << v.at(i).id << endl;
		f << v.at(i).percurso << endl;
		f << setfill('0') << setw(4) << to_string(v.at(i).datai.year) << "/" << setw(2) << to_string(v.at(i).datai.month) << "/" << setw(2) << to_string(v.at(i).datai.day) << endl;
		f << setfill('0') << setw(4) << to_string(v.at(i).dataf.year) << "/" << setw(2) << to_string(v.at(i).dataf.month) << "/" << setw(2) << to_string(v.at(i).dataf.day) << endl << setfill('0');
		f << v.at(i).priceperperson << endl;
		f << v.at(i).nmaxperson << endl;
		f << v.at(i).ndisponiveis << endl;
	}
	f.close();
	cout << "Pacote adicionado!\n";
}
void elim_TravelPack(string &td, vector <TravelPack> &v)
{
	fstream f;
	f.open(td, ios::in);
	string last_pack_created;
	getline(f, last_pack_created); // READ THE LAST PACK CREATED
	f.close();
	int id_last_pack = stoi(last_pack_created);
	int id_pack;
	cout << "ID do Pacote de Viagens: ";
	cin >> id_pack;
	
	int a = -1;
	for (unsigned int i = 0; i < v.size(); i++)
	{
		if (v.at(i).id == id_pack)
			a = i;
	}	

	if (a == -1)
		cout << "Nao existe nenhum pacote com esse ID...\n";
	else
	{
		vector<TravelPack>::iterator it = v.begin();
		for (int k = 0; k < a; k++)
			it++;
		v.erase(it);
		cout << "Pacote eliminado!\n";
	}

	string datai, dataf;

	f.open(td, ios::out);
	f << last_pack_created << endl;
	unsigned int i = 0;
	f << v.at(i).id << endl;
	f << v.at(i).percurso << endl;
	f << setfill('0') << setw(4) << to_string(v.at(i).datai.year) << "/" << setw(2) << to_string(v.at(i).datai.month) << "/" << setw(2) << to_string(v.at(i).datai.day) << endl;
	f << setfill('0') << setw(4) << to_string(v.at(i).dataf.year) << "/" << setw(2) << to_string(v.at(i).dataf.month) << "/" << setw(2) << to_string(v.at(i).dataf.day) << endl << setfill('0');
	f << v.at(i).priceperperson << endl;
	f << v.at(i).nmaxperson << endl;
	f << v.at(i).ndisponiveis << endl;

	for (i = 1; i < v.size(); i++)
	{
		f << "::::::::::" << endl;
		f << v.at(i).id << endl;
		f << v.at(i).percurso << endl;
		f << setfill('0') << setw(4) << to_string(v.at(i).datai.year) << "/" << setw(2) << to_string(v.at(i).datai.month) << "/" << setw(2) << to_string(v.at(i).datai.day) << endl;
		f << setfill('0') << setw(4) << to_string(v.at(i).dataf.year) << "/" << setw(2) << to_string(v.at(i).dataf.month) << "/" << setw(2) << to_string(v.at(i).dataf.day) << endl << setfill('0');
		f << v.at(i).priceperperson << endl;
		f << v.at(i).nmaxperson << endl;
		f << v.at(i).ndisponiveis << endl;
	}
	f.close();
}
void add_Client(string &cd, vector <Client> &v)
{
	fstream f;

	Client new_client;
	string morada, data_nif;

	cin.clear();
	cin.ignore(1000, '\n');

	cout << "Nome: ";
	getline(cin, new_client.nome);
	cout << "NIF: ";
	getline(cin, data_nif);
	new_client.nif = stoi(data_nif);
	cout << "Agregado familiar: ";
	cin >> new_client.agregado_familiar;
	cout << "Morada: " << endl;

	cin.clear();
	cin.ignore(1000, '\n');
	
	cout << "Rua: ";
	getline(cin, new_client.morada.rua);
	cout << "Numero da porta: ";
	getline(cin, new_client.morada.nporta);
	cout << "Numero no andar: ";
	getline(cin, new_client.morada.nandar);
	cout << "Codigo-postal: "; 
	getline(cin, new_client.morada.codpostal);
	cout << "Localidade: ";
	getline(cin, new_client.morada.local);
	new_client.packs_comprados = "0";
	
	v.push_back(new_client);

	f.open(cd, ios::out);
	int i = 0;
	f << v.at(i).nome << endl;
	f << v.at(i).nif << endl;
	f << v.at(i).agregado_familiar << endl;
	morada = v.at(i).morada.rua + " / " + v.at(i).morada.nporta + " / " + v.at(i).morada.nandar + " / " + v.at(i).morada.codpostal + " / " + v.at(i).morada.local;
	f << morada << endl;
	f << v.at(i).packs_comprados << endl;

	for (unsigned int i = 1; i < v.size(); i++)
	{
		f << "::::::::::" << endl;
		f << v.at(i).nome << endl;
		f << v.at(i).nif << endl;
		f << v.at(i).agregado_familiar << endl;
		morada = v.at(i).morada.rua + " / " + v.at(i).morada.nporta + " / " + v.at(i).morada.nandar + " / " + v.at(i).morada.codpostal + " / " + v.at(i).morada.local;
		f << morada << endl;
		f << v.at(i).packs_comprados << endl;
	}
	f.close();
	cout << "Cliente adicionado!\n";
}
void elim_Client(string &cd, vector <Client> &v)
{
	fstream f;
	int nif_client;
	string morada;
	cout << "NIF do cliente a eliminar: ";
	cin >> nif_client;

	int a = -1;
	for (unsigned int i = 0; i < v.size(); i++)
	{
		if (v.at(i).nif == nif_client)
			a = i;
	}

	if (a == -1)
		cout << "Nao existe nenhum cliente com esse nif......\n";
	else
	{
		vector<Client>::iterator it = v.begin();
		for (int k = 0; k < a; k++)
			it++;
		v.erase(it);
		cout << "Cliente eliminado!\n";
	}

	f.open(cd, ios::out);
	int i = 0;
	f << v.at(i).nome << endl;
	f << v.at(i).nif << endl;
	f << v.at(i).agregado_familiar << endl;
	morada = v.at(i).morada.rua + " / " + v.at(i).morada.nporta + " / " + v.at(i).morada.nandar + " / " + v.at(i).morada.codpostal + " / " + v.at(i).morada.local;
	f << morada << endl;
	f << v.at(i).packs_comprados << endl;

	for (unsigned int i = 1; i < v.size(); i++)
	{
		f << "::::::::::" << endl;
		f << v.at(i).nome << endl;
		f << v.at(i).nif << endl;
		f << v.at(i).agregado_familiar << endl;
		morada = v.at(i).morada.rua + " / " + v.at(i).morada.nporta + " / " + v.at(i).morada.nandar + " / " + v.at(i).morada.codpostal + " / " + v.at(i).morada.local;
		f << morada << endl;
		f << v.at(i).packs_comprados << endl;
	}
	f.close();
}
void alt_TravelPack(string &td, vector <TravelPack> &v)
{
	int id;
	cout << "ID do Pacote de Viagens: ";
	cin >> id;

	fstream f;
	f.open(td, ios::in);
	string last_pack_created;
	getline(f, last_pack_created); // READ THE LAST PACK CREATED
	f.close();

	int a = -1;
	for (unsigned int i = 0; i < v.size(); i++)
	{
		if (v.at(i).id == id)
		{	
			a = 1;
			v.at(i).id = id;
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Destino: ";
			getline(cin, v.at(i).percurso);
			cout << "Data de início: " << endl;
			bool check;
			do
			{
				cout << "Dia: ";
				if (cin >> v.at(i).datai.day && v.at(i).datai.day >= 1 && v.at(i).datai.day <= 31)
					check = true;
				else
				{
					cin.clear();
					cin.ignore(1000, '\n');
					check = false;
				}
			} while (!check);
			do
			{
				cout << "Mes: ";
				if (cin >> v.at(i).datai.month && v.at(i).datai.month >= 1 && v.at(i).datai.month <= 12)
					check = true;
				else
				{
					cin.clear();
					cin.ignore(1000, '\n');
					check = false;
				}
			} while (!check);
			do
			{
				cout << "Ano: ";
				if (cin >> v.at(i).datai.year && v.at(i).datai.year >= 2019 && v.at(i).datai.year < 3000)
					check = true;
				else
				{
					cin.clear();
					cin.ignore(1000, '\n');
					check = false;
				}
			} while (!check);

			cout << "Data de fim: " << endl;
			do
			{
				cout << "Dia: ";
				if (cin >> v.at(i).dataf.day && v.at(i).dataf.day >= 1 && v.at(i).dataf.day <= 31)
					check = true;
				else
				{
					cin.clear();
					cin.ignore(1000, '\n');
					check = false;
				}
			} while (!check);
			do
			{
				cout << "Mes: ";
				if (cin >> v.at(i).dataf.month && v.at(i).dataf.month >= 1 && v.at(i).dataf.month <= 12)
					check = true;
				else
				{
					cin.clear();
					cin.ignore(1000, '\n');
					check = false;
				}
			} while (!check);
			do
			{
				cout << "Ano: ";
				if (cin >> v.at(i).dataf.year && v.at(i).dataf.year >= 2019 && v.at(i).dataf.year < 3000 &&
					valid_year(v.at(i).datai.day, v.at(i).dataf.day, v.at(i).datai.month, v.at(i).dataf.month, v.at(i).datai.year, v.at(i).dataf.year))
					check = true;
				else
				{
					cin.clear();
					cin.ignore(1000, '\n');
					check = false;
				}
			} while (!check);

			do
			{
				cout << "Preco por pessoa: ";
				if (cin >> v.at(i).priceperperson)
					check = true;
				else
				{
					cin.clear();
					cin.ignore(1000, '\n');
					check = false;
				}
			} while (!check);
			do
			{
				cout << "Numero de lugares disponiveis: ";
				if (cin >> v.at(i).nmaxperson)
					check = true;
				else
				{
					cin.clear();
					cin.ignore(1000, '\n');
					check = false;
				}
			} while (!check);
			v.at(i).ndisponiveis = v.at(i).nmaxperson;
		}
		cout << "Pacote alterado!\n";
	}
	if (a == -1)
		cout << "Nao existe nenhum pacote com esse ID...\n";

	f.open(td, ios::out);
	int i = 0;
	f << last_pack_created << endl;
	f << v.at(i).id << endl;
	f << v.at(i).percurso << endl;
	f << setfill('0') << setw(4) << to_string(v.at(i).datai.year) << "/" << setw(2) << to_string(v.at(i).datai.month) << "/" << setw(2) << to_string(v.at(i).datai.day) << endl;
	f << setfill('0') << setw(4) << to_string(v.at(i).dataf.year) << "/" << setw(2) << to_string(v.at(i).dataf.month) << "/" << setw(2) << to_string(v.at(i).dataf.day) << endl << setfill('0');
	f << v.at(i).priceperperson << endl;
	f << v.at(i).nmaxperson << endl;
	f << v.at(i).ndisponiveis << endl;

	for (unsigned int i = 1; i < v.size(); i++)
	{
		f << "::::::::::" << endl;
		f << v.at(i).id << endl;
		f << v.at(i).percurso << endl;
		f << setfill('0') << setw(4) << to_string(v.at(i).datai.year) << "/" << setw(2) << to_string(v.at(i).datai.month) << "/" << setw(2) << to_string(v.at(i).datai.day) << endl;
		f << setfill('0') << setw(4) << to_string(v.at(i).dataf.year) << "/" << setw(2) << to_string(v.at(i).dataf.month) << "/" << setw(2) << to_string(v.at(i).dataf.day) << endl << setfill('0');
		f << v.at(i).priceperperson << endl;
		f << v.at(i).nmaxperson << endl;
		f << v.at(i).ndisponiveis << endl;
	}
	f.close();

}
void vender_TravelPack_to_Client(string &cd, string &td, vector <Client> &vc, vector <TravelPack> &v)
{
	int nif_client;
	fstream fc, f;
	fc.open(cd);
	cout << "NIF do cliente: ";
	cin >> nif_client;

	int c = -1;
	for (unsigned int iii = 0; iii < vc.size(); iii++)
	{
		if (vc.at(iii).nif == nif_client)
			c = iii;
	}

	if (c == -1)
		cout << "Nao existe nenhum cliente com esse nif......\n";
	else
	{
		int id_pack;
		f.open(td);
		cout << "ID do pacote de viagens: ";
		cin >> id_pack;

		int t = -1;
		for (unsigned int ii = 0; ii < v.size(); ii++)
		{
			if (v.at(ii).id == id_pack)
			{
				t = ii;
				if (v.at(ii).ndisponiveis >= 1)
				{
					v.at(ii).ndisponiveis -= 1;
					string last_pack_created;
					getline(f, last_pack_created); // READ THE LAST PACK CREATED
					f.close();

					f.open(td, ios::out);
					f << last_pack_created << endl;
					unsigned int i = 0;
					f << v.at(i).id << endl;
					f << v.at(i).percurso << endl;
					f << setfill('0') << setw(4) << to_string(v.at(i).datai.year) << "/" << setw(2) << to_string(v.at(i).datai.month) << "/" << setw(2) << to_string(v.at(i).datai.day) << endl;
					f << setfill('0') << setw(4) << to_string(v.at(i).dataf.year) << "/" << setw(2) << to_string(v.at(i).dataf.month) << "/" << setw(2) << to_string(v.at(i).dataf.day) << endl << setfill('0');
					f << v.at(i).priceperperson << endl;
					f << v.at(i).nmaxperson << endl;
					f << v.at(i).ndisponiveis << endl;

					for (i = 1; i < v.size(); i++)
					{
						f << "::::::::::" << endl;
						f << v.at(i).id << endl;
						f << v.at(i).percurso << endl;
						f << setfill('0') << setw(4) << to_string(v.at(i).datai.year) << "/" << setw(2) << to_string(v.at(i).datai.month) << "/" << setw(2) << to_string(v.at(i).datai.day) << endl;
						f << setfill('0') << setw(4) << to_string(v.at(i).dataf.year) << "/" << setw(2) << to_string(v.at(i).dataf.month) << "/" << setw(2) << to_string(v.at(i).dataf.day) << endl << setfill('0');
						f << v.at(i).priceperperson << endl;
						f << v.at(i).nmaxperson << endl;
						f << v.at(i).ndisponiveis << endl;
					}
					f.close();
					cout << "Pacote vendido!\n";
				}
				else
					cout << "O pacote que escolheu ja nao tem lugares disponiveis...";
			}
		}
		f.close();

		if (t == -1)
			cout << "Nao existe nenhum pacote com esse ID...\n";
		else
		{
			// para o cliente c comprar o pacote com id t
			if (vc.at(c).packs_comprados == "0")
				vc.at(c).packs_comprados = to_string(id_pack);
			else
			{
				string data;
				data = vc.at(c).packs_comprados;
				data = data.substr(0, data.find_last_of(";"));
				data = data.erase(0, data.find_last_of(";") + 1);
				vc.at(c).packs_comprados += " ; " + to_string(id_pack);
			}
			string morada;
			int i = 0;
			fc << vc.at(i).nome << endl;
			fc << vc.at(i).nif << endl;
			fc << vc.at(i).agregado_familiar << endl;
			morada = vc.at(i).morada.rua + " / " + vc.at(i).morada.nporta + " / " + vc.at(i).morada.nandar + " / " + vc.at(i).morada.codpostal + " / " + vc.at(i).morada.local;
			fc << morada << endl;
			fc << vc.at(i).packs_comprados << endl;

			for (unsigned int i = 1; i < vc.size(); i++)
			{
				fc << "::::::::::" << endl;
				fc << vc.at(i).nome << endl;
				fc << vc.at(i).nif << endl;
				fc << vc.at(i).agregado_familiar << endl;
				morada = vc.at(i).morada.rua + " / " + vc.at(i).morada.nporta + " / " + vc.at(i).morada.nandar + " / " + vc.at(i).morada.codpostal + " / " + vc.at(i).morada.local;
				fc << morada << endl;
				fc << vc.at(i).packs_comprados << endl;
			}
			fc.close();
		}
	}
}
void info_cli(string &file)
{
	Client v;
	string data;
	ifstream i;
	i.open(file);
	if (i.is_open())
	{
		while (getline(i, data))
		{
			cout << "Nome: " << data << endl;
			getline(i, data);
			cout << "NIF: " << data << endl;
			getline(i, data);
			cout << "Agregado familiar: " << data << endl;
			getline(i, data);
			cout << "Morada: " << data << endl;
			getline(i, data);
			cout << "Pacotes comprados: " << data << endl;
			getline(i, data); // (data = "::::::::" if ins't over yet)
			cout << data << endl;
		}
	}
}
void info_packs(string &file)
{
	string data;
	ifstream i;
	i.open(file);
	if (i.is_open())
	{
		getline(i, data);
		cout << "Ultimo pacote criado: " << data << endl << endl;

		while (getline(i, data))
		{
			cout << "ID: " << data << endl;
			getline(i, data);
			cout << "Destino: " << data << endl;
			getline(i, data);
			cout << "Data de inicio: " << data << endl;
			getline(i, data);
			cout << "Data de fim: " << data << endl;
			getline(i, data);
			cout << "Preco por pessoa: " << data << endl;
			getline(i, data);
			cout << "Numero de lugares inicialmente disponiveis: " << data << endl;
			getline(i, data);
			cout << "Numero de lugares atualmente disponiveis: " << data << endl;
			getline(i, data);
			if (data != "0")
				cout << data << endl;
		}
	}
}

//-----INFORMAÇÃO-------------
Date decompose_data(string &dd)
{
	Date data;
	string aux;
	aux = dd.substr(0, dd.find_first_of("/")); dd.erase(0, dd.find_first_of("/") + 1);
	trim(aux);
	data.year = stoi(aux);
	aux = dd.substr(0, dd.find_first_of("/")); dd.erase(0, dd.find_first_of("/") + 1);
	trim(aux);
	data.month = stoi(aux);
	trim(aux);
	data.day = stoi(aux);
	return data;
}
Address decompose_morada(string &ad)
{
	Address morada;
	morada.rua = ad.substr(0, ad.find_first_of("/")); ad.erase(0, ad.find_first_of("/") + 1); trim(morada.rua);
	morada.nporta = ad.substr(0, ad.find_first_of("/")); ad.erase(0, ad.find_first_of("/") + 1); trim(morada.nporta);
	morada.nandar = ad.substr(0, ad.find_first_of("/")); ad.erase(0, ad.find_first_of("/") + 1); trim(morada.nandar);
	morada.codpostal = ad.substr(0, ad.find_first_of("/")); ad.erase(0, ad.find_first_of("/") + 1); trim(morada.codpostal);
	morada.local = ad.substr(0, ad.find_first_of('\n')); trim(morada.local);
		
	return morada;
}
vector <TravelPack> decompose_travelpacks(string &s)
{
	vector <TravelPack> v;
	TravelPack pack;
	string data, last_pack_created, str_id, datai, dataf;
	ifstream file;
	file.open(s);

	getline(file, last_pack_created);

	while (getline(file, str_id))
	{
		pack.id = stoi(str_id);
		getline(file, pack.percurso);
		getline(file, datai);
		pack.datai = decompose_data(datai);
		getline(file, dataf);
		pack.dataf = decompose_data(dataf);
		getline(file, data);
		pack.priceperperson = stoi(data);
		getline(file, data);
		pack.nmaxperson = stoi(data);
		getline(file, data);
		pack.ndisponiveis = stoi(data);
		getline(file, data);
		if (data == "::::::::::" || data == "")
			v.push_back(pack);
		else
			break;
	}

	return v;
}
vector <Client> decompose_clientes(string &s)
{
	vector <Client> v;
	Client cli;
	string agr_fam, morada, packs, data, nif;
	ifstream file;
	file.open(s);


	while (getline(file, cli.nome))
	{
		getline(file, nif);
		cli.nif = stoi(nif);
		getline(file, agr_fam);
		cli.agregado_familiar = stoi(agr_fam);
		getline(file, morada);
		cli.morada = decompose_morada(morada);
		getline(file, cli.packs_comprados); //cli.packs_comprados = stoi(packs);			//cli.packs_comprados = decompose_packs_comprados(data); //acabar
		getline(file, data);
		if (data == "::::::::::" || data == "")
			v.push_back(cli);
		else
			break;
	}
	return v;
}

//---------VETORES PARA TORNAR A FUNÇÃO MAIN MAIS ELEGANTE ------------------
string agency_name()
{
	string agency;						                 // agency
	cout << "Nome da agencia: "; cin >> agency;
	agency.append(".txt");								// agency.txt
	return agency;
}
Agency readAgency(string &file)
{
	string clientes_morada, clientes_agencia, pacotes_agencia;
	ifstream fa;
	Agency agencia;
	
	system("cls");
	
	fa.open(file);
	if (fa.is_open())
	{
		getline(fa, agencia.nome);
		getline(fa, agencia.nif);
		getline(fa, agencia.url);

		getline(fa, clientes_morada);
		agencia.morada = decompose_morada(clientes_morada);
		getline(fa, clientes_agencia);
		agencia.clientes = decompose_clientes(clientes_agencia);
		getline(fa, pacotes_agencia);
		agencia.travel_packs = decompose_travelpacks(pacotes_agencia);

		cout << "Leitura bem sucedida!\n";
	}
	else
	{
		cout << "Ficheiro nao encontrado...\n" << endl; system("pause"); exit(1);
	}

	fa.close();

	return agencia;
}
string clientsAgency(string &s)
{
	ifstream file;
	file.open(s);
	string str;

	for (int i = 1; i <= 4; i++)
		getline(file, str);
	getline(file, str);
	return str;
}
string packsAgency(string &s)
{
	ifstream file;
	file.open(s);
	string str;

	for (int i = 1; i <= 5; i++)
		getline(file, str);
	getline(file, str);
	return str;
}

int main()
{	
	string name_agency = agency_name();
	Agency data_agency = readAgency(name_agency);		// READ ALL THE DATA ABOUT THE AGENCY

	string agency_clients = clientsAgency(name_agency);
	string agency_packs = packsAgency(name_agency);
	
	int what_to_do = 1, what_to_do_here = 1;			// MAIN OF THE PROGRAM: MENU AND FUNCTIONS TO DO

	do {
		cout << "\nO que pretende fazer? \n\n[1] Gerir Pacotes de Viagens \n[2] Gerir Clientes \n[3] Visualizar Informacao \n[0] Sair \n";
		cin >> what_to_do; cout << endl;
		system("cls");

		switch (what_to_do)
		{
		case 0: {
			cout << "\nObrigado pela sua escolha!\n\n";
			system("pause");
			exit(0); }																			// THE ONLY EXIT OF THE PROGRAM

		case 1:
			do {
				cout << "\nGerir Pacotes de Viagens\n\n[1] Adicionar \n[2] Alterar \n[3] Eliminar \n[0] Voltar \n";
				cin >> what_to_do_here;
				system("cls");

				switch (what_to_do_here)
				{
				case 0:
					break;
				case 1:
					cout << "Adicionar Pacotes de Viagens\n\n";
					add_TravelPack(agency_packs, data_agency.travel_packs);
					system("pause");
					break;
				case 2:
					cout << "Alterar Pacotes de Viagens\n\n";
					alt_TravelPack(agency_packs, data_agency.travel_packs);
					system("pause");
					break;
				case 3:
					cout << "Eliminar Pacotes de Viagens\n\n";
					elim_TravelPack(agency_packs, data_agency.travel_packs);
					system("pause");
					break;
				default:
					cout << "Nao percebi...!\n\n";
					break;
				}

			} while (what_to_do_here != 1 && what_to_do_here != 2 && what_to_do_here != 3 && what_to_do_here != 0);
			break;

		case 2:
			do {
				cout << "\nGerir Clientes\n\n[1] Adicionar \n[2] Vender \n[3] Eliminar \n[0] Voltar \n";
				cin >> what_to_do_here;
				system("cls");

				switch (what_to_do_here)
				{
				case 0:
					break;
				case 1:
					cout << "Adicionar Clientes\n\n";
					add_Client(agency_clients, data_agency.clientes);
					system("pause");
					break;
				case 2:
					cout << "Vender um Pacote de Viagens a Clientes\n\n";
					vender_TravelPack_to_Client(agency_clients, agency_packs, data_agency.clientes, data_agency.travel_packs);
					system("pause");
					break;
				case 3:
					cout << "Eliminar Clientes\n\n";
					elim_Client(agency_clients, data_agency.clientes);
					system("pause");
					break;
				default:
					cout << "Nao percebi...!\n";
					break;
				}
			} while (what_to_do_here != 1 && what_to_do_here != 2 && what_to_do_here != 3 && what_to_do_here != 0);
			break;

		case 3:
			do {
				cout << "\nVisualizacao de Informacao\n\n[1] Sobre Clientes \n[2] Sobre Pacotes de Viagens \n[0] Voltar \n";
				cin >> what_to_do_here;
				system("cls");

				switch (what_to_do_here)
				{
				case 0:
					break;
				case 1:
					cout << "Sobre Clientes\n\n";
					info_cli(agency_clients);
					system("pause");
					break;
				case 2:
					system("CLS");
					cout << "Sobre Pacotes de Viagens\n\n";
					info_packs(agency_packs);
					system("pause");
					break;
				default:
					cout << "Nao percebi...!\n";
					break;
				}
			} while (what_to_do_here != 1 && what_to_do_here != 2 && what_to_do_here != 0);
			break;

		default:
			cout << "Nao percebi...!\n";
			break;
		}
		system("cls");
	} while (what_to_do != 0);
}
// n linhas