#include "Komputer.h"
#include "Gracz.h"
bool Komputer::Ruch(Plansza *p, int x, int y, int x1, int y1, Gracz* c) {          // ruch komputera
		srand((unsigned int)time(NULL));
		 x = rand() % 16;                    //losuje wiersz pionka
		 y = rand() % 16;                    //losuje kolumne pionka

		 x1 = rand() % 16;                   // nowy wiersz pionka
		 y1 = rand() % 16;                   //nowa kolumna pionka

		 // warunki na wybór przez komputer pionka, jesli wybierze nie swoj pionek, albo otoczony z kazdej strony
		while (p->gra[x][y].wyglad != c->gracz[0].wyglad || (p->gra[x + 1][y].wyglad != ' ' &&
			p->gra[x - 1][y].wyglad != ' ' &&
			p->gra[x][y + 1].wyglad != ' ' &&
			p->gra[x][y - 1].wyglad != ' ' &&
			p->gra[x + 1][y + 1].wyglad != ' ' &&
			p->gra[x - 1][y - 1].wyglad != ' ' &&
			p->gra[x + 1][y - 1].wyglad != ' ' &&
			p->gra[x - 1][y + 1].wyglad != ' ')) {
			x = rand() % 16;
			y = rand() % 16;
			if (x == 0 && y == 0) {   //jesli wylosowano lewy gorny rog
				if (p->gra[x + 1][y].wyglad != ' ' &&p->gra[x][y + 1].wyglad != ' ' &&p->gra[x + 1][y + 1].wyglad != ' ') {
					x = rand() % 16;
					y = rand() % 16;
				}
			}
			else if (x == 15 && y == 15) { //jesli wylosowano prawy dolny dolny rog
				if (p->gra[x - 1][y].wyglad != ' ' &&p->gra[x][y - 1].wyglad != ' ' &&p->gra[x - 1][y - 1].wyglad != ' ') {
					x = rand() % 16;
					y = rand() % 16;
				}
			}
			if (y == 0) {
				if (p->gra[x + 1][y].wyglad != ' ' &&p->gra[x - 1][y].wyglad != ' ' &&p->gra[x][y + 1].wyglad != ' '&&p->gra[x + 1][y + 1].wyglad != ' '&&p->gra[x - 1][y + 1].wyglad != ' ') {
					x = rand() % 16;
					y = rand() % 16;
				}
			}
			else if (y == 15) {
				if (p->gra[x + 1][y].wyglad != ' ' &&p->gra[x - 1][y].wyglad != ' ' &&p->gra[x][y - 1].wyglad != ' '&&p->gra[x + 1][y - 1].wyglad != ' '&&p->gra[x - 1][y - 1].wyglad != ' ') {
					x = rand() % 16;
					y = rand() % 16;
				}
			}
			if (x == 15) {
				if (p->gra[x][y + 1].wyglad != ' ' &&p->gra[x][y - 1].wyglad != ' ' &&p->gra[x - 1][y].wyglad != ' '&&p->gra[x - 1][y - 1].wyglad != ' '&&p->gra[x - 1][y + 1].wyglad != ' ') {
					x = rand() % 16;
					y = rand() % 16;
				}
			}

		}


		while ((abs(y1 - y) > 1 || abs(x1 - x) > 1) || p->gra[x1][y1].wyglad != ' ') { //dopoki nowa pozycja pionka nie jest wieksza o 1, lub nowa pozycja pionka jest zajeta 
			x1 = rand() % 16;                                //losuj nowe x1,y1
			y1 = rand() % 16;
		}
		//printf("[%d][%d]->[%d][%d]", x, y, x1, y1);            //wyswietlenie jaki ruch zostal wykonany
		cout << "[" << x << "]" << "[" << y << "]" << "->" << "[" << x1 << "]" << "[" << y1 << "]";
		system("PAUSE");

		p->gra[x1][y1].wyglad = p->gra[x][y].wyglad;
		p->usunPionek(x, y);                                  //i usun pionek ze stara pozycja



		return true;

	}