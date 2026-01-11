#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class Uzytkownik {
public:
    string login;
    string haslo;

    string zwrocLogin() const {
        return this->login;
    }
};

class SystemLogowania {
    bool zalogowany = false;
public:
    Uzytkownik u;

    void rejestracja() {
        string sprawdzenieLogin, sprawdzenieHaslo;
        bool zajety = false;
        do {
            zajety = false;
            cout << "Podaj login: ";
            cin >> u.login;

            ifstream plikOdczyt("uzytkownicy.txt");
            if (plikOdczyt.is_open()) {
                while (plikOdczyt >> sprawdzenieLogin >> sprawdzenieHaslo) {
                    if (sprawdzenieLogin == u.login) {
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
            cout << "Powtorz has³o: ";
            cin >> haslo2;

            if (u.haslo != haslo2) {
                cout << "B³¹d! Has³a nie s¹ takie same." << endl;
            }
            else {
                ofstream plikZapis("uzytkownicy.txt", ios::app);
                if (plikZapis.is_open()) {
                    plikZapis << u.login << " " << u.haslo << endl;
                    plikZapis.close();
                    cout << "Konto zosta³o utworzone!" << endl;
                }
                break;
            }
        }
    }

    bool logowanie() {
        string login, haslo, plikLogin, plikHaslo;
        cout << "Podaj login: ";
        cin >> login;
        cout << "Podaj haslo: ";
        cin >> haslo;

        ifstream plik("uzytkownicy.txt");
        while (plik >> plikLogin >> plikHaslo) {
            if (plikLogin == login && plikHaslo == haslo) {
                u.login = login;
                this->zalogowany = true;
                plik.close();
                return true;
            }
        }
        plik.close();
        return false;
    };

    bool czyZalogowany() {
        return this->zalogowany;
    }

    void wyloguj() {
        this->zalogowany = false;
        cout << "Wylogowano pomyœlnie" << endl;
    }
};