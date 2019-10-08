#define _CRT_SECURE_NO_WARNINGS
#include "Plansza.h"
#include "Gracz.h"
#include <time.h>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;


void Plansza::usunPionek(int x, int y) {   //usuwanie pionka z danego pola
		gra[x][y].wyglad = ' ';
}

Plansza::Plansza(Gracz *&c, Gracz *&c2) {  //konstruktor tworzacy plansze, dla danych 2 graczy

	for (int i = 0;i < 16;i++) {               
		for (int j = 0;j < 16;j++) {
			gra[i][j].wyglad = ' ';                   //wypelnienie tablicy pustymi znakami
		}
	}
	for (int i = 0;i < 5;i++) {
		for (int j = 0;j < 5;j++) {
			gra[i][j].wyglad = c->gracz[0].wyglad;   // wypelnienie tablicy nad przekatna 6 znakami gracza 1
			if (i + j >= 6) {
				gra[i][j].wyglad= ' ';
			}
		}
	}
	for (int i = 11;i < 16;i++) {
		for (int j = 11;j < 16;j++) {
			gra[i][j].wyglad =c2->gracz[0].wyglad;   // wypelnienie tabliczy nad przekatna 24 znakami gracza 2
			if (i + j <= 24) {
				gra[i][j].wyglad = ' ';
			}
		}
	}
}


void Plansza::wypiszPlansze() {  //metoda odpowiada za wypisanie tablicy z jej aktualna zawartoscia na ekran

	system("cls");  //odswiezanie ekranu
	int a=0;

	cout <<"     0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15"<<endl;
	cout<<"   -----------------------------------------------------------------"<<endl;
	for (int i = 0;i < 16;i++) {
		cout << "   |";
		for (int j = 0;j < 16;j++) {
			cout << ' ' << getWyglad(i, j) << " |";
		}
		cout << " "<< a++;
	cout<<endl<<"   -----------------------------------------------------------------"<<endl;
	}


}

void Plansza::Wygrana(Gracz *c,Gracz*c2) {   //metoda sprawdza czy pozycje pionkow na planszy pozwalaja na wygranie partii
	int wyg1 = 0;  //liczy punkty wygranej gracza 1
	int wyg2 = 0;  //liczy punkty wygranej gracza 2
	for (int i = 0;i < 5;i++) {
		for (int j = 0;j < 5;j++) {
			if (gra[i][j].wyglad ==c2->gracz[0].wyglad&& (i + j < 6)) {				              
					wyg1++;  //jesli pionek gracza 2 jest na pozycji startowej gracza 1, dodaj 1 				
			}	
		}
	}	
	for (int i = 11;i < 16;i++) {
		for (int j = 11;j < 16;j++) {
			if (gra[i][j].wyglad ==c->gracz[0].wyglad&& (i + j > 24)) {				           
					wyg2++; //jesli pionek gracza 1 jest na pozycji startowej gracza 2, dodaj 1				
			}
		}
	}
	if (wyg1 == 19) {
		c2->setWygrana();
	}
	if (wyg2 == 19) {
		c->setWygrana();
	}
}

Plansza::~Plansza() {
}


void Plansza::WynikMeczu(string plik,Gracz *&c,Gracz *&c2) {//zapis do pliku wyniku meczu
	time_t now = time(0);
	char* czas = ctime(&now); //czas zakonczenia gry

	plik += ".txt";  //dodanie do nazwy pliku rozszerzenia .txt
	ofstream log(plik, std::ios_base::app); //strumien do pliku

	if (log.is_open()) //czy mozna otworzyc plik
	{
		log << czas << " Wygrana: " << c->getNazwa()<<": "<< c->getWygrana() << " Przegrana: " << c2->getNazwa()<< ": "<< c2->getWygrana() << endl;
		log.close();
	}
	else cout << "nie mozna otworzyc pliku" << endl;
}
Plansza::Plansza() {
}