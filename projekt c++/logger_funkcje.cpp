#include "Logger.h"
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <ctime>

using namespace std;

string Logger::pobierzCzas() {
    auto teraz = chrono::system_clock::now();
    time_t teraz_time_t = chrono::system_clock::to_time_t(teraz);
    tm teraz_tm;

    localtime_s(&teraz_tm, &teraz_time_t);

    stringstream ss;
    ss << put_time(&teraz_tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void Logger::zapisz(string komunikat) {
    ofstream plik("log.txt", ios::app);
    if (plik.is_open()) {
        plik << "[SYSTEM | " << pobierzCzas() << "] " << komunikat << endl;
        plik.close();
    }
}