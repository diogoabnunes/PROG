#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <vector>
#include "Packet.h"
#include <map>
#include <iterator>
using namespace std;
void consl_clear();
bool isnum(string a);
int intrec();
int detmes(string mes);
int lerdiames(int mes, int ano);
Date lerdata();
bool cmp_datas(Date d1, Date d2);
bool file_em_branco(ifstream& pFile);
string ltrim(string totrim);
string rtrim(string totrim);
string trim(string totrim);
int lernif();
vector<string> cid(string cidades);
vector<int> str_to_vec_pac(string packs);
vector<Packet> vec_to_vec_pac(vector<int> packs,vector<Packet> pacotes);
vector<Packet> pacotes_cli(string packs_compr, vector<Packet> pacotes);