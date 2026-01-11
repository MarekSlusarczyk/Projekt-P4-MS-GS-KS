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
				cout << "\n\nWitaj w OLX! Zalogowano jako: " << system.u.zwrocNazweUzytkownika() << endl;
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
		cout << "\n\nMENU OLX" << endl;
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
            int wyswietlono = 0;

            for (int i = 0; i < licznik; i++) {
                if (tablica[i]->zwrocStatus() == 0) {
                    tablica[i]->wyswietl();
                    wyswietlono++;
                }
            }

            if (wyswietlono == 0) {
                cout << "Obecnie nie ma żadnych dostępnych ofert." << endl;
            }
            break;
        }
        case 2: {
            cout << "Wybierz kategorię (1 - Motoryzacja, 2 - Elektronika): ";
            int kat; 
            cin >> kat;
            string szukana = (kat == 1) ? "Motoryzacja" : "Elektronika";

            int wyswietlono = 0;
            cout << "\n--- OFERTY Z KATEGORII: " << szukana << " ---" << endl;

            for (int i = 0; i < licznik; i++) {
                if (tablica[i]->zwrocKategorie() == szukana && tablica[i]->zwrocStatus() == 0) {
                    tablica[i]->wyswietl();
                    wyswietlono++;
                }
            }

            if (wyswietlono == 0) {
                cout << "Brak aktywnych ogłoszeń w tej kategorii." << endl;
            }
            break;
        }
        case 3: {
            cout << "\n--- TWOJE AKTYWNE OGŁOSZENIA ---" << endl;
            bool znaleziono = false;
            for (int i = 0; i < licznik; i++) {
                if (tablica[i]->zwrocWlasciciela() == system.u.zwrocLogin() && tablica[i]->zwrocStatus() == 0) {
                    cout << "ID: [" << i << "] ";
                    tablica[i]->wyswietl();
                    znaleziono = true;
                }
            }

            if (znaleziono) {
                cout << "Podaj ID ogłoszenia do zarządzania (lub -1 żeby wrócić): ";
                int id; cin >> id;
                if (id >= 0 && id < licznik && tablica[id]->zwrocWlasciciela() == system.u.zwrocLogin()) {
                    cout << "1. Edytuj ogłoszenie\n2. Usuń ogłoszenie\nWybór: ";
                    int akcja; cin >> akcja;

                    if (akcja == 1) {
                        // EDYCJA
                        string t, l, o; float c;
                        cin.ignore();
                        cout << "Nowy tytuł: "; getline(cin, t);
                        cout << "Nowa lokalizacja: "; getline(cin, l);
                        cout << "Nowy opis: "; getline(cin, o);
                        cout << "Nowa cena: "; cin >> c;

                        tablica[id]->edytujDaneBazowe(t, l, o, c);

                        // Edycja pola specyficznego dla klasy (rzutowanie typu)
                        if (tablica[id]->zwrocKategorie() == "Motoryzacja") {
                            int p; cout << "Nowy przebieg: "; cin >> p;
                            // Rzutowanie wskaźnika, aby dostać się do metody klasy pochodnej
                            static_cast<Motoryzacja*>(tablica[id])->ustawPrzebieg(p);
                        }
                        else {
                            string s; cout << "Nowy stan: "; cin.ignore(); getline(cin, s);
                            static_cast<Elektronika*>(tablica[id])->ustawStan(s);
                        }
                        cout << "Ogłoszenie zaktualizowane!" << endl;
                    }
                    else if (akcja == 2) {
                        // USUNIĘCIE
                        tablica[id]->ustawStatus(2);
                        cout << "Ogłoszenie usunięte." << endl;
                    }

                    zapiszDoPliku(tablica, licznik); // Zapisujemy zmiany do pliku
                }
            }
            else cout << "Brak ogłoszeń do wyświetlenia." << endl;
            break;
        }
        case 4: {
            if (licznik >= maxRozmiar) {
                powiekszTablice(tablica, maxRozmiar);
            }

            int kat;
            string t, l, o, cecha; float c;
            cout << "Kategoria (1-Motoryzacja, 2-Elektronika): "; cin >> kat;
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