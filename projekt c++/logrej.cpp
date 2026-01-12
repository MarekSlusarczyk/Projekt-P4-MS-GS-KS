#include "logrej.h"
#include "logger.h"
#include <fstream>
#include <sstream>

string Uzytkownik::zwrocLogin() const {
    return this->login;
}

string Uzytkownik::zwrocNazweUzytkownika() const {
    return this->nazwaUzytkownika;
}

void SystemLogowania::rejestracja() {
    string linia, plikLogin, plikHaslo;
    bool zajety = false;

    cout << "Podaj wyœwietlan¹ nazwê u¿ytkownika (np. Imiê Nazwisko): ";
    cin.ignore();
    getline(cin, u.nazwaUzytkownika);

    do {
        zajety = false;
        cout << "Podaj login: ";
        cin >> u.login;

        ifstream plikOdczyt("uzytkownicy.txt");
        if (plikOdczyt.is_open()) {
            while (getline(plikOdczyt, linia)) {
                stringstream ss(linia);
                getline(ss, plikLogin, ';');
                if (plikLogin == u.login) {
                    zajety = true;
                    break;
                }
            }
            plikOdczyt.close();
        }

        if (zajety) {
            cout << "B³¹d: U¿ytkownik o takim loginie ju¿ istnieje!" << endl;
        }
    } while (zajety);

    string haslo2 = "";
    while (true) {
        cout << "Podaj has³o: ";
        cin >> u.haslo;
        cout << "Powtórz has³o: ";
        cin >> haslo2;

        if (u.haslo != haslo2) {
            cout << "B³¹d! Has³a nie s¹ takie same." << endl;
        }
        else {
            ofstream plikZapis("uzytkownicy.txt", ios::app);
            if (plikZapis.is_open()) {
                plikZapis << u.login << ";" << u.haslo << ";" << u.nazwaUzytkownika << endl;
                plikZapis.close();
                cout << "Konto zosta³o utworzone!" << endl;
                Logger::zapisz("Utworzono nowe konto: " + u.login);
            }
            break;
        }
    }
}

bool SystemLogowania::logowanie() {
    string loginInput, hasloInput, linia, plikLogin, plikHaslo, plikNazwaUzytkownika;
    cout << "Podaj login: ";
    cin >> loginInput;
    cout << "Podaj has³o: ";
    cin >> hasloInput;

    ifstream plik("uzytkownicy.txt");
    if (plik.is_open()) {
        while (getline(plik, linia)) {
            stringstream ss(linia);
            getline(ss, plikLogin, ';');
            getline(ss, plikHaslo, ';');
            getline(ss, plikNazwaUzytkownika, ';');

            if (plikLogin == loginInput && plikHaslo == hasloInput) {
                u.login = loginInput;
                u.nazwaUzytkownika = plikNazwaUzytkownika;
                Logger::zapisz("Zalogowano u¿ytkownika: " + u.login);
                this->zalogowany = true;
                plik.close();
                return true;
            }
        }
        plik.close();
    }
    return false;
}

bool SystemLogowania::czyZalogowany() {
    return this->zalogowany;
}

void SystemLogowania::wyloguj() {
    this->zalogowany = false;
    this->u.login = "";
    cout << "Wylogowano pomyœlnie" << endl;
}