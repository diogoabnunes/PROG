#pragma once

#include "Agency.h"
#include "utils.h"
#include <fstream>
#include <iomanip>
#include <functional>
#include <set>
#include <algorithm>


void refresh_cli(Agency& agency);
void refresh_pac(Agency& agency);

vector<string> defMVMsites(vector<Packet> pacotes);

//Funções Packets
void filt_pac(Agency& agency);
void ver_pac(Agency& agency);
void cri_pac(Agency& agency);
void del_pac(Agency& agency);
void mod_spe_pac(Agency& agency, int a);
void mod_pac(Agency& agency);
void pac(Agency& agency);

//Funções Cliente
void inf_age(Agency& agency);
void cri_cli(Agency& agency);
void mod_cli(Agency& agency, int g);
void cliespe(Agency &agency, int g);
void selectcli(Agency& agency);
void del_cli(Agency& agency);
void cli(Agency& agency);

void vend_pac(Agency& agency);
void mainMenu(Agency& agency);

