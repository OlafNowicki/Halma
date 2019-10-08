#pragma once
#include "Gracz.h"
class Czlowiek :public Gracz {
public:
	Czlowiek() :Gracz() {};
	Czlowiek(string imie, char znak) :Gracz() {
			gracz[0].wyglad = znak;
	}
	~Czlowiek() {};
	bool validSkok(Plansza *, int, int, int, int, Gracz*); //czy kolejne skoki sa zgodne z zasadami
	int valid(Plansza *, int, int, int, int, Gracz*);  //czy pierwszy skok jest zgodny z zasadami
	virtual bool Ruch(Plansza *p, int x, int y, int x1, int y1, Gracz* c);// x,y wspolrzedne pionka x1,y1 miesce w ktore ma sie przemiescic
	bool WarunekSkoki(Plansza *p, int x, int y, int x1, int y1); //warunek czy skok jest zgodny z zasadami
	bool skok(Plansza *p, int x, int y, int x1, int y1, Gracz* c); //ruch typu skok
	void KontrolaIntCzlowiek(int &a, int &b); //kontrola intow w klasie
};
