#pragma once
#include "Pionek.h"
#include <string.h>
#include <iostream>
using namespace std;
class Gracz;
class Plansza {                  //Klasa odpowiadajaca za wyglad planszy i rzeczy z ni¹ zwiazane
public:
	Pionek gra[16][16];     // plansza wg zasad ma wymiary 16x16

	void usunPionek(int x, int y);  //usuwanie pionka z danego pola

	Plansza();
	Plansza(Gracz *&, Gracz *&);
	~Plansza();

	char getWyglad(int x,int y) {return gra[x][y].wyglad;}
	void wypiszPlansze();
	void Wygrana(Gracz *, Gracz *);
	void WynikMeczu(string, Gracz *&, Gracz *&);

};