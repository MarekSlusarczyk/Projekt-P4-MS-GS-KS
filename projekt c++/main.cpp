#include <iostream>
#include <string>
#include "logrej.h"
#include "logger.h"
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

        if (!(cin >> wybor)) {
            cout << "Błąd: Należy wpisać cyfrę podaną w menu!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }

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
        cout << "5. Wyszukiwarka ogłoszeń" << endl;
		cout << "6. Wyloguj się" << endl;
		cout << "--------------" << endl;
        if (!(cin >> wybor)) {
            cout << "Błąd: Należy wpisać cyfrę podaną w menu!" << endl;
            cin.clear();
            cin.ignore(1000, '\n');
            continue;
        }
        switch (wybor) {
        case 1: {
            int wyswietlono = 0;
            cout << "\n--- WSZYSTKIE OGŁOSZENIA ---" << endl;
            for (int i = 0; i < licznik; i++) {
                if (tablica[i]->zwrocStatus() == 0) {
                    cout << "ID: [" << i << "] ";
                    string n = znajdzNazwePoLoginie(tablica[i]->zwrocWlasciciela());
                    tablica[i]->wyswietl(n);
                    wyswietlono++;
                }
            }

            if (wyswietlono > 0) {
                int wybor;
                bool poprawnyWybor = false;

                do {
                    cout << "Wpisz ID ogłoszenia, które chcesz kupić (lub -1 aby wrócić): ";
                    if (!(cin >> wybor)) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Błąd: Wpisz poprawną liczbę!" << endl;
                        continue;
                    }

                    if (wybor == -1) break;

                    if (wybor >= 0 && wybor < licznik && tablica[wybor]->zwrocStatus() == 0) {
                        if (tablica[wybor]->zwrocWlasciciela() != system.u.zwrocLogin()) {

                            tablica[wybor]->ustawStatus(1);
                            zapiszDoPliku(tablica, licznik);

                            Logger::zapisz("Użytkownik " + system.u.zwrocLogin() + " kupił produkt o ID: " + to_string(wybor));

                            cout << "\n------------------" << endl;
                            cout << "Zakupiono produkt!" << endl;
                            cout << "------------------" << endl;
                            poprawnyWybor = true;
                        }
                        else {
                            cout << "Błąd: Nie możesz kupić własnego produktu!" << endl;
                        }
                    }
                    else {
                        cout << "Błąd: Nieprawidłowe ID lub oferta jest niedostępna. Spróbuj ponownie." << endl;
                    }
                } while (!poprawnyWybor);

            }
            else {
                cout << "Brak dostępnych ofert." << endl;
            }
            break;
        }
        case 2: {
            int kat;
            bool poprawnaKat = false;

            do {
                cout << "Wybierz kategorię (1 - Motoryzacja, 2 - Elektronika, 3 - Odzież, 4 - Książki): ";
                if (!(cin >> kat)) {
                    cout << "Błąd: Należy wpisać cyfrę!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }
                if (kat >= 1 && kat <= 4) poprawnaKat = true;
                else cout << "Błąd: Wybierz opcję 1, 2, 3 lub 4!" << endl;
            } while (!poprawnaKat);

            string szukana;
            if (kat == 1) szukana = "Motoryzacja";
            else if (kat == 2) szukana = "Elektronika";
            else if (kat == 3) szukana = "Odziez";
            else if (kat == 4) szukana = "Ksiazki";

            int wyswietlono = 0;
            cout << "\n--- OFERTY Z KATEGORII: " << szukana << " ---" << endl;
            for (int i = 0; i < licznik; i++) {
                if (tablica[i]->zwrocKategorie() == szukana && tablica[i]->zwrocStatus() == 0) {
                    cout << "ID: [" << i << "] ";
                    string nazwaDoPokazania = znajdzNazwePoLoginie(tablica[i]->zwrocWlasciciela());
                    tablica[i]->wyswietl(nazwaDoPokazania);
                    wyswietlono++;
                }
            }

            if (wyswietlono > 0) {
                int wybor;
                bool poprawnyWybor = false;

                do {
                    cout << "\nWpisz ID ogłoszenia, które chcesz kupić (lub -1 aby wrócić): ";
                    if (!(cin >> wybor)) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Błąd: Wpisz poprawną liczbę!" << endl;
                        continue;
                    }

                    if (wybor == -1) break;

                    if (wybor >= 0 && wybor < licznik &&
                        tablica[wybor]->zwrocStatus() == 0 &&
                        tablica[wybor]->zwrocKategorie() == szukana) {

                        if (tablica[wybor]->zwrocWlasciciela() != system.u.zwrocLogin()) {
                            tablica[wybor]->ustawStatus(1);
                            zapiszDoPliku(tablica, licznik);

                            Logger::zapisz("Użytkownik " + system.u.zwrocLogin() + " kupił produkt o ID: " + to_string(wybor));

                            cout << "\n------------------" << endl;
                            cout << "Zakupiono produkt!" << endl;
                            cout << "------------------" << endl;
                            poprawnyWybor = true;
                        }
                        else {
                            cout << "Błąd: Nie możesz kupić własnego produktu!" << endl;
                        }
                    }
                    else {
                        cout << "Błąd: To ID nie pasuje do wyświetlonej listy. Spróbuj ponownie." << endl;
                    }
                } while (!poprawnyWybor);

            }
            else {
                cout << "Brak aktywnych ogłoszeń w tej kategorii." << endl;
            }
            break;
        }
        case 3: {
            bool znaleziono = false;
            cout << "\n--- TWOJE AKTYWNE OGŁOSZENIA ---" << endl;
            for (int i = 0; i < licznik; i++) {
                if (tablica[i]->zwrocWlasciciela() == system.u.zwrocLogin() && tablica[i]->zwrocStatus() == 0) {
                    cout << "ID: [" << i << "] ";
                    tablica[i]->wyswietl(system.u.zwrocNazweUzytkownika());
                    znaleziono = true;
                }
            }

            if (znaleziono) {
                int id;
                bool poprawneID = false;

                do {
                    cout << "Podaj ID ogłoszenia do zarządzania (lub -1 żeby wrócić): ";
                    if (!(cin >> id)) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Błąd: Wpisz poprawną liczbę!" << endl;
                        continue;
                    }

                    if (id == -1) break;


                    if (id >= 0 && id < licznik &&
                        tablica[id]->zwrocWlasciciela() == system.u.zwrocLogin() &&
                        tablica[id]->zwrocStatus() == 0) {

                        poprawneID = true;

                        int akcja;
                        bool poprawnaAkcja = false;

                        do {
                            cout << "1. Edytuj ogłoszenie\n2. Usuń ogłoszenie\nWybór: ";
                            if (!(cin >> akcja)) {
                                cout << "Błąd: Należy wpisać cyfrę!" << endl;
                                cin.clear();
                                cin.ignore(1000, '\n');
                                continue;
                            }
                            if (akcja == 1 || akcja == 2) poprawnaAkcja = true;
                            else cout << "Błąd: Wybierz opcję 1,2,3, lub 4!" << endl;
                        } while (!poprawnaAkcja);


                        if (akcja == 1) {
                            string t, l, o; float c;
                            bool poprawnaCena = false;
                            cin.ignore();
                            cout << "Nowy tytuł: "; getline(cin, t);
                            cout << "Nowa lokalizacja: "; getline(cin, l);
                            cout << "Nowy opis: "; getline(cin, o);
                            do {
                                cout << "Nowa cena: ";
                                if (!(cin >> c)) {
                                    cout << "Błąd: Cena musi być liczbą (użyj kropki dla groszy)!" << endl;
                                    cin.clear();            
                                    cin.ignore(1000, '\n');
                                    continue;
                                }

                                if (c >= 0) {
                                    poprawnaCena = true;
                                }
                                else {
                                    cout << "Błąd: Cena nie może być ujemna!" << endl;
                                }

                            } while (!poprawnaCena);

                            tablica[id]->edytujDaneBazowe(t, l, o, c);

                            if (tablica[id]->zwrocKategorie() == "Motoryzacja") {
                                int p;
                                bool poprawnyPrzebieg = false;
                                do {
                                    cout << "Nowy przebieg: ";
                                    if (!(cin >> p)) {
                                        cout << "Błąd: Przebieg musi być liczbą!" << endl;
                                        cin.clear();
                                        cin.ignore(1000, '\n');
                                        continue;
                                    }
                                    if (p >= 0) {
                                        poprawnyPrzebieg = true;
                                    }
                                    else {
                                        cout << "Błąd: Przebieg nie może być ujemny!" << endl;
                                    }
                                } while (!poprawnyPrzebieg);

                                static_cast<Motoryzacja*>(tablica[id])->ustawPrzebieg(p);
                            }
                            else if (tablica[id]->zwrocKategorie() == "Elektronika") {
                                string s;
                                cout << "Nowy stan: ";
                                cin.ignore();
                                getline(cin, s);
                                static_cast<Elektronika*>(tablica[id])->ustawStan(s);
                            }
                            else if (tablica[id]->zwrocKategorie() == "Odziez") {
                                string s;
                                cout << "Nowy rozmiar: ";
                                cin.ignore();
                                getline(cin, s);
                                static_cast<Odziez*>(tablica[id])->ustawRozmiar(s);
                            }
                            else if (tablica[id]->zwrocKategorie() == "Ksiazki") {
                                string s;
                                cout << "Nowy autor: ";
                                cin.ignore();
                                getline(cin, s);
                                static_cast<Ksiazki*>(tablica[id])->ustawAutora(s);
                            }
                            cout << "\n---------------------------------" << endl;
                            cout << "Ogłoszenie zostało zaktualizowane!" << endl;
                            cout << "\n---------------------------------" << endl;
                            zapiszDoPliku(tablica, licznik);
                        }
                        else if (akcja == 2) {
                            tablica[id]->ustawStatus(2);
                            cout << "Ogłoszenie zostało usunięte." << endl;
                            zapiszDoPliku(tablica, licznik);
                        }
                    }
                    else {
                        cout << "Błąd: To nie jest Twoje ogłoszenie lub podano błędne ID! Spróbuj ponownie." << endl;
                    }
                } while (!poprawneID);

            }
            else {
                cout << "Nie masz obecnie żadnych aktywnych ogłoszeń." << endl;
            }
            break;
        }
        case 4: {
            if (licznik >= maxRozmiar) {
                powiekszTablice(tablica, maxRozmiar);
            }

            int kat;
            string t, l, o, cecha; 
            float c;
            bool poprawnaKat = false;
            bool poprawnaCena = false;

            do {
                cout << "Kategoria (1-Motoryzacja, 2-Elektronika, 3-Odziez, 4-Ksiazki): ";
                if (!(cin >> kat)) {
                    cout << "Błąd: Należy wpisać cyfrę!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }
                if (kat >= 1 && kat <= 4 ) poprawnaKat = true;
                else cout << "Błąd: Wybierz opcję 1, 2, 3 lub 4!" << endl;
            } while (!poprawnaKat);
            cin.ignore();
            cout << "Tytuł: "; getline(cin, t);
            cout << "Lokalizacja: "; getline(cin, l);
            cout << "Opis: "; getline(cin, o);
            do {
                cout << "Cena: ";
                if (!(cin >> c)) {
                    cout << "Błąd: Cena musi być liczbą (użyj kropki dla groszy)!" << endl;
                    cin.clear();
                    cin.ignore(1000, '\n');
                    continue;
                }

                if (c >= 0) {
                    poprawnaCena = true;
                }
                else {
                    cout << "Błąd: Cena nie może być ujemna!" << endl;
                }

            } while (!poprawnaCena);

            if (kat == 1) {
                int p;
                cout << "Przebieg: "; cin >> p;
                tablica[licznik] = new Motoryzacja(t, l, o, system.u.zwrocLogin(), c, 0, p);
            }
            else if (kat == 2) {
                cout << "Stan: "; cin.ignore(); getline(cin, cecha);
                tablica[licznik] = new Elektronika(t, l, o, system.u.zwrocLogin(), c, 0, cecha);
            }
            else if (kat == 3) {
                cout << "Rozmiar: "; cin.ignore(); getline(cin, cecha);
                tablica[licznik] = new Odziez(t, l, o, system.u.zwrocLogin(), c, 0, cecha);
            }
            else if (kat == 4) {
                cout << "Autor: "; cin.ignore(); getline(cin, cecha);
                tablica[licznik] = new Ksiazki(t, l, o, system.u.zwrocLogin(), c, 0, cecha);
            }

            licznik++;
            zapiszDoPliku(tablica, licznik);
            cout << "\n------------------------" << endl;
            cout << "Ogłoszenie zostało dodane!" << endl;
            cout << "------------------------" << endl;
            break;
        
        }
        case 5: {
            string fraza;
            cout << "\n--- WYSZUKIWARKA ---" << endl;
            cout << "Wpisz czego szukasz: ";
            cin.ignore();
            getline(cin, fraza);

            int znaleziono = 0;
            cout << "\nWyniki wyszukiwania dla: \"" << fraza << "\"" << endl;
            cout << "---------------------------------------" << endl;

            for (int i = 0; i < licznik; i++) {
                if (tablica[i]->zwrocStatus() == 0) {
                    string tytul = tablica[i]->zwrocTytul();

                    if (tytul.find(fraza) != string::npos) {
                        cout << "ID: [" << i << "] ";
                        string n = znajdzNazwePoLoginie(tablica[i]->zwrocWlasciciela());
                        tablica[i]->wyswietl(n);
                        znaleziono++;
                    }
                }
            }

            if (znaleziono > 0) {
                int wybor;
                bool poprawnyWybor = false;

                do {
                    cout << "Wpisz ID ogłoszenia, które chcesz kupić (lub -1 aby wrócić): ";
                    if (!(cin >> wybor)) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Błąd: Wpisz poprawną liczbę!" << endl;
                        continue;
                    }

                    if (wybor == -1) break;

                    if (wybor >= 0 && wybor < licznik && tablica[wybor]->zwrocStatus() == 0 &&
                        tablica[wybor]->zwrocTytul().find(fraza) != string::npos) {

                        if (tablica[wybor]->zwrocWlasciciela() != system.u.zwrocLogin()) {
                            tablica[wybor]->ustawStatus(1);
                            zapiszDoPliku(tablica, licznik);

                            Logger::zapisz("Użytkownik " + system.u.zwrocLogin() + " kupił produkt o ID: " + to_string(wybor));

                            cout << "\n------------------" << endl;
                            cout << "Zakupiono produkt!" << endl;
                            cout << "------------------" << endl;
                            poprawnyWybor = true;
                        }
                        else {
                            cout << "Błąd: Nie możesz kupić własnego produktu!" << endl;
                        }
                    }
                    else {
                        cout << "Błąd: To ID nie znajduje się na liście wyników wyszukiwania. Spróbuj ponownie." << endl;
                    }
                } while (!poprawnyWybor);

            }
            else {
                cout << "Brak wyników pasujących do frazy." << endl;
            }
            break;
        }
        case 6:
            system.wyloguj();
            break;
        }
	}

}
