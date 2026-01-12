#ifndef LOGGER_H
#define LOGGER_H

#include <string>

using namespace std;

class Logger {
private:
    static string pobierzCzas();

public:
    static void zapisz(string komunikat);
};

#endif