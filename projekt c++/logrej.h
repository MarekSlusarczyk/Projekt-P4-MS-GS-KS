#ifndef LOGREJ_H
#define LOGREJ_H

#include <iostream>
#include <string>

using namespace std;

class Uzytkownik {
public:
    string nazwaUzytkownika;
    string login;
    string haslo;

    string zwrocLogin() const;
    string zwrocNazweUzytkownika() const;
};

class SystemLogowania {
private:
    bool zalogowany = false;
public:
    Uzytkownik u;

    void rejestracja();
    bool logowanie();
    bool czyZalogowany();
    void wyloguj();
};

#endif