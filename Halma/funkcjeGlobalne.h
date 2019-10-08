#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <conio.h>
#include "Gracz.h"
#include "Czlowiek.h"
#include "Komputer.h"
#include "Plansza.h"
#include "Pionek.h"
#include <Windows.h>
#include <time.h>
using namespace std;
void KontrolaInt(int &a, int &b) {  //kontrola poprawnosci intow
	while (!(cin >> a) || !(cin >> b) || a>16 || a<0 || b>16 || b<0) { //dopoki a i b nie sa intem powtorz wprowadzenie
		cout << "ERROR:wpisz liczbe >0 i <16: ";
		cin.clear();
		cin.ignore(132, '\n');
	}
}
//////////////////////////////////////////////////////////////////////////
void KontrolaChar(string &a, char &b) { //kontrola poprawnosci charow
	while (true) {
		cout << "Wybierz znak reprezentujacy pionek: ";
		getline(cin, a);

		if (a.length() == 1 && a[0] != ' ') { //jesli string ma 1 znak
			b = a[0];    //to pionek jest rowny temu znakowi
			break;
		}

		cout << "Wpisz znak! jeden znak(i nie spacje)" << endl;
	}
}
//////////////////////////////////////////////////////////////////////////
void KontrolaString(string &a) { //kontrola poprawnosci stringow
	while (true) {
		int x = 0;
		cout << "Podaj pseudonim: ";
		getline(cin, a);
		int b = a.length();
		for (int i = 0; i < b; ++i) {  //przeszukuje string
			if (a[i] == ' ') {   //jesli spacja dodaj do x
				x++;
			}
		}
		if (x != 0) {  //jesli x jest zerem to string nie ma spacji, przechodzi dalej
			cout << "Podaj pseudonim, ale bez spacji" << endl;
		}
		else {
			break;
		}
	}
}
//////////////////////////////////////////////////////////////////////////
template <typename T>
inline T const& Max(T const& a, T const& b) {   //Szablon funkcji, wybiera wiekszy z dwoch  podanych zmiennych, np: string-string,int-int,char-char. 
	return a > b ? a : b;
}
int losowanie() {  // sposób losowania, który gracz zaczyna jako pierwszy
	srand((unsigned int)time(NULL));
	int type = rand() % 3;
	int test;
	int test2;
	if (type == 0) { test = rand() % 10 + 48; }
	else if (type == 1) { test = rand() % 25 + 65; }
	else if (type == 2) { test = rand() % 25 + 97; }
	if (type == 0) { test2 = rand() % 10 + 48; }
	else if (type == 1) { test2 = rand() % 25 + 65; }
	else if (type == 2) { test2 = rand() % 25 + 97; }
	return Max(test, test2);
}
//////////////////////////////////////////////////////////////////////////
void setConsole() { //wymiary konsoli
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r); //przechwytuje aktualny rozmiar

	MoveWindow(console, r.left, r.top, 800, 600, TRUE); //800 szerokosc 600 wysokosc
}
//////////////////////////////////////////////////////////////////////////
void kontrolaXY(Plansza*a, int &x, int &y, Gracz &g) { //zarzadzanie poczatkowym wyborem gracza
	if (a->getWyglad(x, y) == ' ' || a->getWyglad(x, y) == g.getWyglad()) { //jesli wybrane pole jest polem przeciwnika, albo puste popraw
		while (a->getWyglad(x, y) == ' ' || a->getWyglad(x, y) == g.getWyglad()) {
			cout << "Wybrales puste pole, lub pole przeciwnika wybierz ponownie :";
			KontrolaInt(x, y);
		}
	}
}
//////////////////////////////////////////////////////////////////////////
int kontrolaX1Y1(Plansza*a, int &x, int &y, Gracz &g,Gracz &g2) { //zarzadzanie polem na ktore jest wykonywany skok
	char c = { 0 };
	if (a->getWyglad(x, y) == g.getWyglad()|| a->getWyglad(x, y) == g2.getWyglad()) {
		while (a->getWyglad(x, y) == g.getWyglad()|| a->getWyglad(x, y) == g2.getWyglad()) {
			cout << "Wybrane pole jest zajete przez inny pionek! Podaj nowa pozycje:";
			KontrolaInt(x, y);
			cout << "\nZablokowales sie? t -tak || inny przycisk nie:";
			cin >> c;
			if (c == 't') {
				return 0;
			}
			else {
				if (a->getWyglad(x, y) != ' ') {
					cout << "Wybrane pole jest zajete przez inny pionek! wybierz od nowa:" << endl;
					return 0;
				}
				return 1;
			}
		}
	}
	return 1;
}
/////////////////////////////////////////////////////////////////////////
void GraczTura(Plansza &b,Gracz &a,Gracz &c,int &x,int &y,int &x2,int &y2) {
	cout << "Wybierz pozycje pionka ktorym chcesz sie ruszyc :";
	KontrolaInt(x, y);
	kontrolaXY(&b, x, y, c);
	cout << "Wybierz na ktore pole ma sie przemiescic:";
	KontrolaInt(x2, y2);
	while (!kontrolaX1Y1(&b, x2, y2, a, c)) {
		cout << "Wybierz pozycje pionka ktorym chcesz sie ruszyc:";
		KontrolaInt(x, y);
		while (b.getWyglad(x, y) != a.getWyglad()) {
			cout << "Wybierz SWOJEGO pionka, ktorym chcesz sie ruszyc:";
			KontrolaInt(x, y);
		}
		cout << "Wybierz na ktore pole ma sie przemiescic:";
		KontrolaInt(x2, y2);
	}
}
//////////////////////////////////////////////////////////////////////////
void Tura(Gracz &a, Plansza &b, Gracz &c) {
	int x, y, x2, y2;
	cout << "tura gracza:" << a.getNazwa() << endl;
	GraczTura(b, a, c, x, y, x2, y2);
	if (!a.Ruch(&b, x, y, x2, y2, &a)) {
		cout << "Pionek moze sie przemiescic maksymalnie o 1 pozycje bez skokow:" << endl;
		while (!a.Ruch(&b, x, y, x2, y2, &a)) {
			GraczTura(b, a, c, x, y, x2, y2);
		}
	}
}
//////////////////////////////////////////////////////////////////////////
void wygrana(Gracz *a, Gracz *b, Plansza &c) {
	if (a->getWygrana() == 1) {
		c.wypiszPlansze();
		cout << "Wygral gracz :" << a->getNazwa() << " Koniec gry" << endl;
		c.WynikMeczu("log", a, b);
		exit(0);
	}
	c.wypiszPlansze();
}
//////////////////////////////////////////////////////////////////////////
void losowanieGracza(Gracz *&gracz1, Gracz *&gracz2, string *nazwa1, string *nazwa2, char *pionek, char *pionek2) {
	gracz1 = new Czlowiek(*nazwa1, *pionek);
	gracz1->setNazwa(*nazwa1);
	gracz2 = new Czlowiek(*nazwa2, *pionek2);
	gracz2->setNazwa(*nazwa2);
	cout << "Zaczyna gracz " << gracz1->getNazwa() << endl;
	system("pause");
}
//////////////////////////////////////////////////////////////////////////
void GraLudzi() {
	int n = losowanie(); // przechowywanie wylosowaniej liczby
	int m; // przechowywanie wylosowanej liczby nr2
	Gracz *nr1 = NULL;
	Gracz *nr2 = NULL;
	string gracz1, gracz2; //pseudonimy graczy
	char g1 = { 0 }; //pionek gracz1
	char g2 = { 0 }; //pionek gracza2
	string input = ""; //do kontroli charow
	cout << "* wybierzcie swoje pseudonimy oraz znak reprezentujacy wasze pionki" << endl;
	cout << "* podczas podawania ruchow pionka najpierw podajcie wiersz, a po spacji kolumne" << endl;
	/////////////////////////////////////////////////////////////////////////////
	cin.ignore();
	cout << "gracz 1:" << endl;
	KontrolaString(gracz1);
	KontrolaChar(input, g1);
	putchar('\n');
	//////////////////////////////////////////////////////////////////////////
	cout << "gracz 2:" << endl;
	KontrolaString(gracz2);
	while (gracz2 == gracz1) {
		cout << endl << "Nazwy nie moga byc takie same! gracz 2:";
		KontrolaString(gracz2);
	}
	KontrolaChar(input, g2);
	while (g2 == g1) {
		cout << "Pionki musza byc rozne" << endl;
		KontrolaChar(input, g2);
	}
	////////////////////////////////////////////////////////////////////////////////
	m = losowanie();
	cout << "Zgodnie z zasadami, gracz rozpoczynajacy zostanie wylosowany:" << endl;
	system("pause");
	system("cls");
	if (n > m) {
		losowanieGracza(nr1, nr2, &gracz1, &gracz2, &g1, &g2);
	}
	else {
		losowanieGracza(nr1, nr2, &gracz2, &gracz1, &g2, &g1);
	}
	////////////////////////////////////////////////////////////////////////////////////
	Plansza plansza(nr1, nr2);
	plansza.wypiszPlansze();
	do {
		Tura(*nr1, plansza, *nr2);
		plansza.Wygrana(nr1, nr2);
		wygrana(nr1, nr2, plansza);
		//////////////////////////////////////////////////////////////////////
		Tura(*nr2, plansza, *nr1);
		plansza.Wygrana(nr1, nr2);
		wygrana(nr2, nr1, plansza);
	} while (1);
}
//////////////////////////////////////////////////////////////////////////
void GraKomputer() {
	string gracz1;//pseudonim gracza
	char g1 = { 0 }; //pionek gracz1
	string input = ""; //do kontroli charow
	cin.ignore();
	cout << "Wybrano gre na komputer, w tym trybie zawsze zaczyna czlowiek" << endl << endl;
	cout << "wybierz swoj pseudonim" << endl;
	KontrolaString(gracz1);
	KontrolaChar(input, g1);
	while (g1 == '@') {
		cout << "Twoj pionek nie moze sie rownac @" << endl;
		KontrolaChar(input, g1);
	}
	Gracz *nr1 = new Czlowiek(gracz1, g1);
	nr1->setNazwa(gracz1);
	Gracz *nr2 = new Komputer();
	Plansza plansza(nr1, nr2);
	plansza.wypiszPlansze();
	do {
		///////////////////////////////////////////////////
		Tura(*nr1, plansza, *nr2);
		plansza.Wygrana(nr1, nr2);
		wygrana(nr1, nr2, plansza);
		///////////////////////////////////////////////////
		cout << "tura gracza:" << nr2->getNazwa() << endl;
		int a = 0, b = 0, c = 0, d = 0;
		nr2->Ruch(&plansza, a, b, c, d, nr2);
		plansza.Wygrana(nr1, nr2);
		wygrana(nr2, nr1, plansza);
		///////////////////////////////////////////////////
	} while (1);
}