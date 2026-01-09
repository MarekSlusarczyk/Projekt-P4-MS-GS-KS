#include <iostream>
#include <string>
#include <fstream>
using namespace std;
class Uzytkownik {
    public:
    string login;
    string haslo;
};


class SystemLogowania {
    public:
    Uzytkownik u;
    void rejestracja() {
        string haslo2=" ";
        cout << "Podaj login: ";
        cin >> u.login;
        cout << endl;
        while (u.haslo != haslo2) {
            cout << "Podaj has³o: ";
            cin >> u.haslo;
            cout << endl;
            cout << "Powtórz has³o: ";
            cin >> haslo2;
            if (u.haslo != haslo2) {
                cout << "B³¹d! Has³a siê nie s¹ takie same" << endl;
            }else {
                ofstream plik("uzytkownicy.txt", ios::app);
                plik << u.login << " " << u.haslo << endl;
                plik.close();
                cout << "Konto zosta³o utworzone!" << endl;
                break;
            }
        }
    }
        bool logowanie(){
            string l,h, plikL, plikH;
            cout << "Podaj login: ";
            cin >> l;
            cout << endl;
            cout << "Podaj has³o: ";
            cin >> h;
            ifstream plik("uzytkownicy.txt");
             while (plik >> plikL >> plikH) {
                 if (plikL == l && plikH == h) {
                     plik.close();
                     return true;
                 }
             }
                    plik.close();
                    return false;
                }

    };

