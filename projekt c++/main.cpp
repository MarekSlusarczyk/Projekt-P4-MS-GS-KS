#include <iostream>
#include <string>
#include "logrej.h"
#include <clocale>
using namespace std;

int main() {
setlocale(LC_ALL, "Polish");
    int wybor = 0;
	SystemLogowania system;
	while (true) {
		cout << "MENU" << endl;
    	cout << "--------------" << endl;
    	cout << "1.Logowanie" << endl;
    	cout << "2.Rejestracja" << endl;
		cout << "3.Wyjœcie" << endl;
    	cout << "--------------" << endl;
    	cin >> wybor;
    	switch (wybor) {
			case 1:
				if(system.logowanie() == true) {
				cout << "Witaj w aplikacji!" << endl;
				}else{
				  cout << "Niepoprawny login lub has³o" << endl;
				}
				break;
        	case 2:
            	system.rejestracja();
				break;


			case 3:
				break;

    	}
	}

}