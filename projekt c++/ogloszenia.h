#ifndef OGLOSZENIA_H
#define OGLOSZENIA_H

#include <iostream>
#include <string>

using namespace std;

class Ogloszenie {
protected:
    string tytul;
    string lokalizacja;
    string opis;
    string dodanePrzez;
    float cena;
    int statusOgloszenia; // 0 - aktywne, 1 - kupione, 2 - usuniête przez u¿ytkownika
public:
    Ogloszenie(string t, string l, string o, string d, float c, int sO) : tytul(t), lokalizacja(l), opis(o), dodanePrzez(d), cena(c), statusOgloszenia(sO) {}

    virtual ~Ogloszenie() {}
    virtual void wyswietl() = 0;
    virtual string zwrocKategorie() = 0;
    string zwrocWlasciciela() { 
        return dodanePrzez; 
    }
    virtual string sformatujDoZapisu() = 0;
    int zwrocStatus() { 
        return statusOgloszenia; 
    }
    void ustawStatus(int sO) { 
        statusOgloszenia = sO; 
    }
    void edytujDaneBazowe(string t, string l, string o, float c) {
        tytul = t; 
        lokalizacja = l; 
        opis = o; 
        cena = c;
    }
};

class Motoryzacja : public Ogloszenie {
    int przebieg;
public:
    Motoryzacja(string t, string l, string o, string d, float c, int sO, int p) : Ogloszenie(t, l, o, d, c, sO), przebieg(p) {}

    void wyswietl() override {
        cout << "[MOTORYZACJA] " << endl;
        cout << "Tytu³: " << tytul << endl;
        cout << "Opis: " << opis << endl;
        cout << "Cena: " << cena << " z³" << endl;
        cout << "Przebieg: " << przebieg << " km" << endl;
        cout << "-----------------------\n" << endl;
    }
    string zwrocKategorie() override { return "Motoryzacja"; }

    string sformatujDoZapisu() override {
        return "Motoryzacja;" + tytul + ";" + lokalizacja + ";" + opis + ";" + dodanePrzez + ";" + to_string(cena) + ";" + to_string(statusOgloszenia) + ";" + to_string(przebieg);
    }

    void ustawPrzebieg(int p) { 
        przebieg = p; 
    }
};

class Elektronika : public Ogloszenie {
    string stan;
public:
    Elektronika(string t, string l, string o, string d, float c, int sO, string s) : Ogloszenie(t, l, o, d, c, sO), stan(s) {}

    void wyswietl() override {
        cout << "[ELEKTRONIKA]" << endl;
        cout << "Tytu³: " << tytul << endl;
        cout << "Opis: " << opis << endl;
        cout << "Cena: " << cena << " z³" << endl;
        cout << "Stan: " << stan << endl;
        cout << "-----------------------\n" << endl;
    }
    string zwrocKategorie() override { return "Elektronika"; }

    string sformatujDoZapisu() override {
        return "Elektronika;" + tytul + ";" + lokalizacja + ";" + opis + ";" + dodanePrzez + ";" + to_string(cena) + ";" + to_string(statusOgloszenia) + ";" + stan;
    }

    void ustawStan(string s) { 
        stan = s; 
    }
};

#endif