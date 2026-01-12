#include "ogloszenia_funkcje.h"
#include "logger.h"
#include <fstream>
#include <sstream>


void powiekszTablice(Ogloszenie**& tablica, int& obecnyMax) {
    int nowyMax = obecnyMax + 10;
    Ogloszenie** nowaTablica = new Ogloszenie * [nowyMax];

    for (int i = 0; i < obecnyMax; i++) {
        nowaTablica[i] = tablica[i];
    }

    delete[] tablica;

    tablica = nowaTablica;
    obecnyMax = nowyMax;

    Logger::zapisz("Zwiêkszono rozmiar tablicy do " + to_string(nowyMax) + " elementów.");
}

void zapiszDoPliku(Ogloszenie** tablica, int licznik) {
    ofstream plik("ogloszenia.txt");
    if (plik.is_open()) {
        for (int i = 0; i < licznik; i++) {
            plik << tablica[i]->sformatujDoZapisu() << endl;
        }
        plik.close();
    }
}

void wczytajZPliku(Ogloszenie**& tablica, int& licznik, int& maxRozmiar) {
    ifstream plik("ogloszenia.txt");
    string linia, kat, t, l, o, wl, cenaStr, statusStr, cechaSpec;

    if (plik.is_open()) {
        while (getline(plik, linia)) {
            if (linia.empty()) continue;

            if (licznik >= maxRozmiar) {
                powiekszTablice(tablica, maxRozmiar);
            }

            stringstream ss(linia);

            getline(ss, kat, ';');
            getline(ss, t, ';');
            getline(ss, l, ';');
            getline(ss, o, ';');
            getline(ss, wl, ';');
            getline(ss, cenaStr, ';');
            getline(ss, statusStr, ';');
            getline(ss, cechaSpec, ';');

            try {
                float c = stof(cenaStr);
                int sO = stoi(statusStr);

                if (kat == "Motoryzacja") {
                    int p = stoi(cechaSpec);
                    tablica[licznik] = new Motoryzacja(t, l, o, wl, c, sO, p);
                }
                else if (kat == "Elektronika") {
                    tablica[licznik] = new Elektronika(t, l, o, wl, c, sO, cechaSpec);
                }

                licznik++;
            }
            catch (...) {
                continue;
            }
        }
        plik.close();
    }
}
void czyszczeniePamieci(Ogloszenie** tablica, int licznik) {
    for (int i = 0; i < licznik; i++) {
        delete tablica[i];
    }
}

string znajdzNazwePoLoginie(string login) {
    ifstream plik("uzytkownicy.txt");
    string linia, pLogin, pHadlo, pNazwa;
    if (plik.is_open()) {
        while (getline(plik, linia)) {
            stringstream ss(linia);
            getline(ss, pLogin, ';');
            getline(ss, pHadlo, ';');
            getline(ss, pNazwa, ';');
            if (pLogin == login) {
                plik.close();
                return pNazwa;
            }
        }
        plik.close();
    }
    return login;
}