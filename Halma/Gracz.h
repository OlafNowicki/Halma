#pragma once
#include <string.h>
#include <iostream>
#include "Plansza.h"
#include "Pionek.h"
using namespace std;
class Gracz {
protected:
	string nazwa;
	int wygrana;
public:
	Pionek gracz[1];
	Gracz() :nazwa("Jan"), wygrana(0) {
			gracz[0].wyglad = '@';
	};
	virtual bool Ruch(Plansza*, int, int, int, int, Gracz*) = 0;

	~Gracz(){};
	char getWyglad() {return gracz[0].wyglad;}
	string getNazwa() { return nazwa; }
	int getWygrana() { return wygrana; }

	void setNazwa(string c) {nazwa = c;}
	void setWygrana() { wygrana = 1; }
};
