#include "Czlowiek.h"
#include "Plansza.h"
#include "Gracz.h"


void Czlowiek::KontrolaIntCzlowiek(int &a, int &b) {  //kontrola poprawnosci intow
	while (!(cin >> a) || !(cin >> b) || a>16 || a<0 || b>16 || b<0) { //dopoki a i b nie sa intem powtorz wprowadzenie
		cout << "ERROR:wpisz liczbe =>0 i 16<=: ";
		cin.clear();
		cin.ignore(132, '\n');
	}
}


	int Czlowiek::valid(Plansza *p, int x, int y, int x1, int y1, Gracz* c) {
		if (p->gra[x][y].wyglad != c->gracz[0].wyglad) {
			return 7;
		}
		if (abs(y1 - y) > 2 || abs(x1 - x) > 2) {
			return 8;
		}
		if (p->gra[x1][y1].wyglad != ' ') {
			return 9;
		}
		return 1;
	}

	bool Czlowiek::WarunekSkoki(Plansza *p, int x, int y, int x1, int y1) {
		if (                           //warunki na skakanie
			((x + 2 == x1) && (y + 2 == y1)) && (p->gra[x + 1][y + 1].wyglad != ' ') || //prawy dó³
			((x == x1) && (y + 2 == y1)) && (p->gra[x][y + 1].wyglad != ' ') || //prawo
			((x - 2 == x1) && (y + 2 == y1)) && (p->gra[x - 1][y + 1].wyglad != ' ') || //prawa góra
			((x + 2 == x1) && (y == y1)) && (p->gra[x + 1][y].wyglad != ' ') || //dol
			((x - 2 == x1) && (y == y1)) && (p->gra[x - 1][y].wyglad != ' ') || //gora
			((x == x1) && (y - 2 == y1)) && (p->gra[x][y - 1].wyglad != ' ') || // lewo
			((x + 2 == x1) && (y - 2 == y1)) && (p->gra[x + 1][y - 1].wyglad != ' ') || // lewy dol
			((x - 2 == x1) && (y - 2 == y1)) && (p->gra[x - 1][y - 1].wyglad != ' ') //lewa gora
			) {
			return true;
		}
		return false;
	}

	bool Czlowiek::validSkok(Plansza *p, int x, int y, int x1, int y1, Gracz* c) {
		if (p->gra[x][y].wyglad != c->gracz[0].wyglad) {
			return false;
		}
		if (abs(y1 - y) != 2 && abs(x1 - x) != 2)  {
			return false;
		} 
		//warunek jest potrzeby gdy ktoœ skoczy o 2 miesca dalej ale miedzy miescami nie ma pionka
		if (((x + 2 == x1) && (y + 2 == y1)) && (p->gra[x + 1][y + 1].wyglad == ' ') || //prawy dó³ 
			((x == x1) && (y + 2 == y1)) && (p->gra[x][y + 1].wyglad == ' ') || //prawo
			((x - 2 == x1) && (y + 2 == y1)) && (p->gra[x - 1][y + 1].wyglad == ' ') || //prawa góra
			((x + 2 == x1) && (y == y1)) && (p->gra[x + 1][y].wyglad == ' ') || //dol
			((x - 2 == x1) && (y == y1)) && (p->gra[x - 1][y].wyglad == ' ') || //gora
			((x == x1) && (y - 2 == y1)) && (p->gra[x][y - 1].wyglad == ' ') || // lewo
			((x + 2 == x1) && (y - 2 == y1)) && (p->gra[x + 1][y - 1].wyglad == ' ') || // lewy dol
			((x - 2 == x1) && (y - 2 == y1)) && (p->gra[x - 1][y - 1].wyglad == ' ') //lewa gora
			) {
			return false;
		}
		if (p->gra[x1][y1].wyglad != ' ') {
			return false;
		}

		return true;
	}

	bool Czlowiek::skok(Plansza *p, int x, int y, int x1, int y1, Gracz* c) {
		if (abs(y1 - y) == 2 || abs(x1 - x) == 2) {  //skok zmienia pozycje o maks 2 pola
			if (WarunekSkoki(p, x, y, x1, y1)) {
				int q = 0;
				if (valid(p, x, y, x1, y1, c) == 7) {
					cout << "nie mozesz sie ruszac pionkami przeciwnika" << endl;
					return false;
				}
				else if (valid(p, x, y, x1, y1, c) == 8) {
					cout << "skok moze zmienic pozycje pionka o maksymalnie 2 pola" << endl;
					return false;
				}
				else if (valid(p, x, y, x1, y1, c) == 9) {
					cout << "miejsce zajete przez inny pionek " << endl;
					return false;
				}
				p->gra[x1][y1].wyglad = p->gra[x][y].wyglad;
				p->usunPionek(x, y);
				cout << "Chcesz skoczyc dalej? 1 tak || inny przycisk nie" << endl;
				cin >> q;
				if (q == 1) {
					int x2, y2;
					p->wypiszPlansze();
					cout << "podaj miescje kolejnego skoku" << endl;
					KontrolaIntCzlowiek(x2, y2);
					while (!validSkok(p, x1, y1, x2, y2, c)) {
						char t;
						cout << "Blednie wykonany skok, prosze o poprawienie" << endl;
						cout << " Jesli chcesz zakonczyc serie skokow wcisnij 't' lub inny przycisk jezeli nie" << endl;
						cin >> t;
						if (t == 't') {
							return true;
						}
						else {
							cout << "Podaj wspolrzedne nowej pozycji :";
							KontrolaIntCzlowiek(x2, y2);
						}
					}
					skok(p, x1, y1, x2, y2, c);
				}
				return false;
			}
			return false;
		}
		return false;
	}

	bool Czlowiek::Ruch(Plansza *p, int x, int y, int x1, int y1, Gracz* c) { // x,y wspolrzedne pionka x1,y1 miesce w ktore ma sie przemiescic

			if (abs(y1 - y) > 1 || abs(x1 - x) > 1) {         //czy nowe pozycje pionka s¹ oddalone od niego samego maksymalnie o 1 bez skoków
				if (abs(y1 - y) == 2 || abs(x1 - x) == 2) {  //skok zmienia pozycje o maks 2 pola
					if (WarunekSkoki(p, x, y, x1, y1)) {
						int q = 0;
						if (valid(p, x, y, x1, y1, c) == 7) {
							cout << "nie mozesz sie ruszac pionkami przeciwnika" << endl;
							return false;
						}
						else if (valid(p, x, y, x1, y1, c) == 8) {
							cout << "skok moze zmienic pozycje pionka o maksymalnie 2 pola" << endl;
							return false;
						}
						else if (valid(p, x, y, x1, y1, c) == 9) {
							cout << "miejsce zajete przez inny pionek " << endl;
							return false;
						}
						p->gra[x1][y1].wyglad = p->gra[x][y].wyglad;
						p->usunPionek(x, y);
						cout << "Chcesz skoczyc dalej? 1 tak || inny przycisk nie" << endl;
						cin >> q;
						if (q == 1) {
							int x2, y2;
							p->wypiszPlansze();
							cout << "podaj miescje kolejnego skoku" << endl;
							KontrolaIntCzlowiek(x2, y2);
							while (!validSkok(p, x1, y1, x2, y2, c)) {
								char t;
								cout << "Blednie wykonany skok, prosze o poprawienie" << endl;
								cout <<"Jesli chcesz zakonczyc serie skokow wcisnij 't' lub inny przycisk jezeli nie" << endl;
								cin >> t;
								if (t == 't') {
									return true;
								}
								else {
									cout << "Podaj wspolrzedne nowej pozycji :";
									KontrolaIntCzlowiek(x2, y2);
								}
							}
							skok(p, x1, y1, x2, y2, c);
						}
						return true;
					}
				}
				return false;
			}
	
			p->gra[x1][y1].wyglad = p->gra[x][y].wyglad; // jesli ruch spelnia wszystkie warunki to pionek pojawi sie na nowym miejscu
			p->usunPionek(x, y);                             // i usunie stara pozycje z planszy
			return true;
	}