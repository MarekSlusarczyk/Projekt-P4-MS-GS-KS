#ifndef OGLOSZENIA_FUNKCJE_H
#define OGLOSZENIA_FUNKCJE_H

#include "ogloszenia.h"

void powiekszTablice(Ogloszenie**& tablica, int& obecnyMax);
void zapiszDoPliku(Ogloszenie** tablica, int licznik);
void wczytajZPliku(Ogloszenie**& tablica, int& licznik, int& maxRozmiar);
void czyszczeniePamieci(Ogloszenie** tablica, int licznik);
string znajdzNazwePoLoginie(string login);
#endif