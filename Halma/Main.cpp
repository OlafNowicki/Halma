#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "funkcjeGlobalne.h"
using namespace std;
int main() {
		setConsole();
		char a; //wybór trybu
		cout << "****************************************ZASADY****************************************************" << endl;
		cout << "* Aby wygrac nalezy wszystkie wasze pionki postawic na pozycji startowej przeciwnika*" << endl;
		cout << "* kazdy pionek moze ruszyc sie o 1 pole, bez skokow*" << endl;
		cout << "* Przeskoczyc mozna przez kazdy pionek*" << endl;
		cout << "* w kazdym ruchu mozna ruszyc sie tylk 1 pionkiem*" << endl << endl << endl << endl;
		cout << "Witam w grze Halma, chcesz zagrac na:" << endl << "czlowieka 1" << endl << "komputer 2" << endl<<"dowolny inny przycisk wyjscie"<<endl;
		cin >> a;
		if (a == '1') {
			GraLudzi();
		}
		else if (a == '2') {
			GraKomputer();
		}
		else {
			cout << "Do zobaczenia!"<<endl;
			system("EXIT");
		}
	}
