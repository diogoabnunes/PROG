#include "utils.h"
using namespace std;

void consl_clear() {
	COORD ini = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO ecra;
	DWORD ecrt;

	GetConsoleScreenBufferInfo(console, &ecra);
	FillConsoleOutputCharacterA(
		console, ' ', ecra.dwSize.X * ecra.dwSize.Y, ini, &ecrt
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		ecra.dwSize.X * ecra.dwSize.Y, ini, &ecrt
	);
	SetConsoleCursorPosition(console, ini);
}
bool isnum(string a) {
	if (a.empty() || ((!isdigit(a[0])) && (a[0] != '-') && (a[0] != '+'))) return false;
	char* p;
	strtol(a.c_str(), &p, 10);
	return (*p == 0);
}
int intrec() {
	string b;
	bool c;
	do {
		getline(cin, b, '\n');
		c = isnum(b);
		if (!c) {
			cout << "Entrada Invalida.\nIntroduza um numero." << endl;
		}
		else {
			break;
		}

	} while (!c);
	return stoi(b);
}
bool file_em_branco(ifstream& pFile)
{
	return pFile.peek() == ifstream::traits_type::eof();
}

string ltrim(string totrim) {
	totrim = totrim.substr(totrim.find_first_not_of(" "));
	return totrim;
}
string rtrim(string totrim) {
	totrim.erase(totrim.find_last_not_of(" ") + 1);
	return totrim;
}
string trim(string totrim) {
	totrim = ltrim(totrim);
	totrim = rtrim(totrim);
	return totrim;
}

int lernif() {
	string b;
	bool c;
	do {
		getline(cin, b, '\n');
		c = isnum(b);
		if (!c) {
			cout << "Entrada Invalida.\nIntroduza o parametro pedido acima." << endl;
		}
		else if (stoi(b) < 100000000 || stoi(b) > 999999999) {
			c = false;
			cout << "Por favor insira um nif valido: ";
		}
		else {
			break;
		}

	} while (!c);
	return stoi(b);
}
int detmes(string mes) {
	mes = trim(mes);
	transform(mes.begin(), mes.end(), mes.begin(), ::tolower);
	if (mes == "janeiro") {
		return 0;
	}
	else if (mes == "fevereiro") {
		return 1;
	}
	else if (mes == "marco") {
		return 2;
	}
	else if (mes == "abril") {
		return 3;
	}
	else if (mes == "maio") {
		return 4;
	}
	else if (mes == "junho") {
		return 5;
	}
	else if (mes == "julho") {
		return 6;
	}
	else if (mes == "agosto") {
		return 7;
	}
	else if (mes == "setembro") {
		return 8;
	}
	else if (mes == "outubro") {
		return 9;
	}
	else if (mes == "novembro") {
		return 10;
	}
	else if (mes == "dezembro") {
		return 11;
	}
	else {
		return 12;
	}
}
int lerdiames(int mes, int ano) {
	int x;
	if (mes == 1) {
		x = intrec();
		while (x < 1 || x>31) {
			cout << "Introduza um dia valido: ";
			x = intrec();
		}
		return x;
	}
	else if (mes == 2) {
		x = intrec();
		if (ano % 4 == 0) {
			if (ano % 100 != 0) {
				while (x < 1 || x>29) {
					cout << "Introduza um dia valido: ";
					x = intrec();
				}
			}
			else if (ano % 400 == 0) {
				while (x < 1 || x>29) {
					cout << "Introduza um dia valido: ";
					x = intrec();
				}
			}
			else {
				while (x < 1 || x>28) {
					cout << "Introduza um dia valido: ";
					x = intrec();
				}
			}
		}
		else {
			while (x < 1 || x>28) {
				cout << "Introduza um dia valido: ";
				x = intrec();
			}
		}
		return x;
	}
	else if (mes == 3) {
		x = intrec();
		while (x < 1 || x>31) {
			cout << "Introduza um dia valido: ";
			x = intrec();
		}
		return x;
	}
	else if (mes == 4) {
		x = intrec();
		while (x < 1 || x>30) {
			cout << "Introduza um dia valido: ";
			x = intrec();
		}
		return x;
	}
	else if (mes == 5) {
		x = intrec();
		while (x < 1 || x>31) {
			cout << "Introduza um dia valido: ";
			x = intrec();
		}
		return x;
	}
	else if (mes == 6) {
		x = intrec();
		while (x < 1 || x>30) {
			cout << "Introduza um dia valido: ";
			x = intrec();
		}
		return x;
	}
	else if (mes == 7) {
		x = intrec();
		while (x < 1 || x>31) {
			cout << "Introduza um dia valido: ";
			x = intrec();
		}
		return x;
	}
	else if (mes == 8) {
		x = intrec();
		while (x < 1 || x>31) {
			cout << "Introduza um dia valido: ";
			x = intrec();
		}
		return x;
	}
	else if (mes == 9) {
		x = intrec();
		while (x < 1 || x>30) {
			cout << "Introduza um dia valido: ";
			x = intrec();
		}
		return x;
	}
	else if (mes == 10) {
		x = intrec();
		while (x < 1 || x>31) {
			cout << "Introduza um dia valido: ";
			x = intrec();
		}
		return x;
	}
	else if (mes == 11) {
		x = intrec();
		while (x < 1 || x>30) {
			cout << "Introduza um dia valido: ";
			x = intrec();
		}
		return x;
	}
	else if (mes == 12) {
		x = intrec();
		while (x < 1 || x>31) {
			cout << "Introduza um dia valido: ";
			x = intrec();
		}
		return x;
	}
}
Date lerdata() {
	string b, a, xit;
	bool c;
	int anoi, xi, mes;
	cout << "Introduza o ano: ";
	anoi = intrec();
	
	cout << "Introduza o mes: ";
	do {
		getline(cin, b, '\n');
		c = isnum(b);
		if (!c) {
			mes = detmes(b);
			if (mes != 12) {
				b = to_string(mes + 1);
				break;
			}
			cout << "Entrada Inválida.\nIntroduza um mes: ";
		}
		else if (stoi(b) > 12) {
			cout << "Entrada Inválida.\nIntroduza um mes: ";
			c = false;
		}
		else {
			break;
		}

	} while (!c);
	a = "0" + b;
	a = "0" + b;
	a = a.substr(a.size() - 2);

	cout << "Introduza o dia: ";
	xi = lerdiames(stoi(a), anoi);
	xit = "0" + to_string(xi);
	xit = xit.substr(xit.size() - 2);
	a = to_string(anoi) + '/' + a + '/' + xit;
	Date dat(a);
	return dat;
}
bool cmp_datas(Date begin, Date d2) {
	if (begin.getYear()< d2.getYear()) {
		return true;
	}
	else if (begin.getMonth() < d2.getMonth()) {
		return true;
	}
	else if(begin.getDay() < d2.getDay())
	 {
		return true;
	}
	return false;
}

vector<string> cid(string cidades) {
	vector<string> a;
	for (int i = 0; i < (count(cidades.begin(), cidades.end(), ',')); i++) {
		a.push_back(cidades.substr(0, cidades.find_first_of(',')));
		cidades = cidades.substr(cidades.find_first_of(',') + 2);
	}
	a.push_back(cidades);
	return a;
}
vector<int> str_to_vec_pac(string packs) {
	vector<int> b;
	int c = count(packs.begin(), packs.end(), ';') + 1;
	for (int i = 0; i < c; i++) {
		b.push_back(stoi(trim(packs.substr(0, packs.find_first_of(';')))));
		packs = trim(packs.substr(packs.find_first_of(';') + 1));
	}
	return b;
}

//utilizando o vetor que contem os ids dos pacotes comprados pelo cliente e da push_back 
//de um vetor de pacotes turisticos para o nome.clientes.at(cliente que esta a ser lido/utilizado).pacote_turistico
vector<Packet> vec_to_vec_pac(vector<int> packs,vector<Packet> pacotes) {
	vector<Packet> a;
	for (int i = 0; i < pacotes.size(); i++) {
		for (int j = 0; j < packs.size(); j++) {
			if (packs.at(j) == abs(pacotes.at(i).getId())) {
				a.push_back(pacotes.at(i));
			}
		}
	}
	return a;
}
//junta as duas funçoes acima numa so basicamente
vector<Packet> pacotes_cli(string packs_compr, vector<Packet> pacotes) {
	vector<Packet> b;
	vector<int> a;
	a = str_to_vec_pac(packs_compr);
	b = vec_to_vec_pac(a,pacotes);
	return b;
}