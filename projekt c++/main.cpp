#include <iostream>
#include <string>
#include "logrej.h"

using namespace std;

#ifdef _WIN32
#define SYSTEM system("chcp 1250 > null");

#elif _WIN64
#define SYSTEM system("chcp 1250 > null");

#endif

void mainMenu(SystemLogowania& system);
void appMenu(SystemLogowania& system);

int main() {
	SYSTEM;
	int wybor = 0;
	SystemLogowania system;

	mainMenu(system);

	appMenu(system);

	return 0;
}

void mainMenu(SystemLogowania& system) {
	int wybor = 0;
	while (!system.czyZalogowany()) {
		cout << "MENU LOGOWANIA" << endl;
		cout << "--------------" << endl;
		cout << "1. Logowanie" << endl;
		cout << "2. Rejestracja" << endl;
		cout << "3. Wyjście" << endl;
		cout << "--------------" << endl;
		cin >> wybor;
		switch (wybor) {
		case 1:
			if (system.logowanie()) {
				cout << "Witaj w aplikacji! Zalogowano jako: " << system.u.zwrocLogin() << endl;
			}
			else {
				cout << "Niepoprawny login lub hasło" << endl;
			}
			break;
		case 2:
			system.rejestracja();
			break;
		case 3:
			exit(0);
		}
	}
}

void appMenu(SystemLogowania& system) {
	int wybor = 0;
	while (system.czyZalogowany()) {
		cout << "MENU" << endl;
		cout << "--------------" << endl;
		cout << "1. Przeglądaj wszystkie ogłoszenia" << endl;
		cout << "2. Twoje ogłoszenia" << endl;
		cout << "3. Wystaw na sprzedaż" << endl;
		cout << "4. Wyloguj się" << endl;
		cout << "--------------" << endl;
		cin >> wybor;
		switch (wybor) {

		case 4:
			system.wyloguj();
			mainMenu(system);
			break;
		}
	}
}