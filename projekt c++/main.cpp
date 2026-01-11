#include <iostream>
#include <string>
#include "logrej.h"
#include "ogloszenia_funkcje.h"

using namespace std;

#ifdef _WIN32
#define SYSTEM system("chcp 1250 > null");

#elif _WIN64
#define SYSTEM system("chcp 1250 > null");

#endif

void mainMenu(SystemLogowania& system);
void appMenu(SystemLogowania& system, Ogloszenie**& tablica, int& licznik, int& maxRozmiar);

int main() {
	SYSTEM;
	SystemLogowania system;

	int maxRozmiar = 2;
	int licznikOgloszen = 0;

	Ogloszenie** bazaOgloszen = new Ogloszenie * [maxRozmiar];

	wczytajZPliku(bazaOgloszen, licznikOgloszen, maxRozmiar);

	mainMenu(system);

	if (system.czyZalogowany()) {
		appMenu(system, bazaOgloszen, licznikOgloszen, maxRozmiar);
	}

	zapiszDoPliku(bazaOgloszen, licznikOgloszen);
	czyszczeniePamieci(bazaOgloszen, licznikOgloszen);
	delete[] bazaOgloszen;

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

void appMenu(SystemLogowania& system, Ogloszenie**& tablica, int& licznik, int& maxRozmiar) {
	int wybor = 0;
	while (system.czyZalogowany()) {
		cout << "MENU OLX (Zalogowany jako: " << system.u.zwrocNazweUzytkownika() << ")" << endl;
		cout << "--------------" << endl;
		cout << "1. Przeglądaj wszystkie ogłoszenia" << endl;
		cout << "2. Filtruj ogłoszenia według kategorii" << endl;
		cout << "3. Twoje ogłoszenia" << endl;
		cout << "4. Dodaj ogłoszenie" << endl;
		cout << "5. Wyloguj się" << endl;
		cout << "--------------" << endl;
		cin >> wybor;
        switch (wybor) {
        case 1: {
            cout << "\n--- AKTUALNE OFERTY ---" << endl;
            for (int i = 0; i < licznik; i++) {
                if (tablica[i]->zwrocStatus() == 0) tablica[i]->wyswietl();
            }
            break;
        }
        case 2: {
            cout << "Wybierz kategorię (1 - Motoryzacja, 2 - Elektronika): ";
            int kat; cin >> kat;
            string szukana = (kat == 1) ? "Motoryzacja" : "Elektronika";
            for (int i = 0; i < licznik; i++) {
                if (tablica[i]->zwrocKategorie() == szukana && tablica[i]->zwrocStatus() == 0) {
                    tablica[i]->wyswietl();
                }
            }
            break;
        }
        case 3: {
            cout << "\n--- TWOJE OGŁOSZENIA ---" << endl;
            bool znaleziono = false;
            for (int i = 0; i < licznik; i++) {
                if (tablica[i]->zwrocWlasciciela() == system.u.zwrocLogin() && tablica[i]->zwrocStatus() == 0) {
                    cout << "ID: [" << i << "] ";
                    tablica[i]->wyswietl();
                    znaleziono = true;
                }
            }
            if (znaleziono) {
                cout << "Podaj ID do usunięcia (lub -1 żeby wrócić): ";
                int id; 
                cin >> id;
                if (id >= 0 && id < licznik && tablica[id]->zwrocWlasciciela() == system.u.zwrocLogin()) {
                    tablica[id]->ustawStatus(2);
                    cout << "Ogłoszenie zostało usunięte (ukryte)." << endl;
                }
            }
            else cout << "Nie masz aktywnych ogłoszeń." << endl;
            break;
        }
        case 4: {
            if (licznik >= maxRozmiar) {
                powiekszTablice(tablica, maxRozmiar);
            }

            int kat;
            string t, l, o, cecha; float c;
            cout << "Kategoria (1-Auto, 2-Elektronika): "; cin >> kat;
            cin.ignore();
            cout << "Tytuł: "; getline(cin, t);
            cout << "Lokalizacja: "; getline(cin, l);
            cout << "Opis: "; getline(cin, o);
            cout << "Cena: "; cin >> c;

            if (kat == 1) {
                int p; cout << "Przebieg: "; cin >> p;
                tablica[licznik] = new Motoryzacja(t, l, o, system.u.zwrocLogin(), c, 0, p);
            }
            else {
                cout << "Stan: "; cin.ignore(); getline(cin, cecha);
                tablica[licznik] = new Elektronika(t, l, o, system.u.zwrocLogin(), c, 0, cecha);
            }
            licznik++;
            zapiszDoPliku(tablica, licznik);
            cout << "Dodano pomyślnie!" << endl;
            break;
        }
        case 5:
            system.wyloguj();
            break;
        }
	}
}