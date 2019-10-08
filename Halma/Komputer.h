#pragma once
#include "Gracz.h"
#include<time.h>
class Komputer :public Gracz {
public:
	Komputer() :Gracz() {
	}
	~Komputer() {};
	bool Ruch(Plansza *, int, int, int, int, Gracz*);          // ruch komputera
};