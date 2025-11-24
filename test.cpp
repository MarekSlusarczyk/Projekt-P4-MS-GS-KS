#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <iostream>
#include <string>
#include <vector> // Dodane dla bezpiecznego bufora char

using namespace std;

#if _WIN32
#define SYSTEM system("chcp 1250 > null");

#elif _WIN64
#define SYSTEM system("chcp 1250 > null");

#endif

// Funkcja pomocnicza do obsługi błędów
void HandleDiagnosticRecord(SQLHANDLE hHandle, SQLSMALLINT hType, RETCODE RetCode) {
    if (RetCode == SQL_SUCCESS || RetCode == SQL_SUCCESS_WITH_INFO) {
        return;
    }

    SQLSMALLINT iRec = 0;
    SQLINTEGER iError;
    SQLCHAR szMessage[1000];
    // Poprawka: Zwiększono rozmiar o 1, aby bezpiecznie pomieścić znak null
    SQLCHAR szState[SQL_SQLSTATE_SIZE + 1];

    if (RetCode == SQL_INVALID_HANDLE) {
        cout << "Invalid Handle!" << endl;
        return;
    }

    while (SQLGetDiagRecA(hType, hHandle, ++iRec, szState, &iError, szMessage, (SQLSMALLINT)sizeof(szMessage), (SQLSMALLINT*)NULL) == SQL_SUCCESS) {
        cout << "ODBC ERROR [" << szState << "]: " << szMessage << " (" << iError << ")" << endl;
    }
}

int sprawdzLogin(SQLHDBC hDbc, string login, string haslo) {
    SQLHSTMT hStmt = NULL;
    RETCODE RetCode;

    // Inicjalizacja na początku, aby uniknąć ostrzeżenia 'goto Cleanup'
    SQLLEN cbUsername = 0;

    // Maksymalna długość kolumny 'username' (dostosuj, jeśli masz dłuższą kolumnę)
    const int MAX_USERNAME_LEN = 255;
    // Bufor do przechowywania pobranej nazwy użytkownika
    vector<char> usernameBuffer(MAX_USERNAME_LEN);

    cout << endl;
    cout << "--- Weryfikacja logowania ---" << endl;
    cout << "Login: " << login << endl;
    cout << "Hasło: " << haslo << endl;

    // 1. Alokacja uchwytu instrukcji
    RetCode = SQLAllocHandle(SQL_HANDLE_STMT, hDbc, &hStmt);
    if (!SQL_SUCCEEDED(RetCode)) {
        HandleDiagnosticRecord(hDbc, SQL_HANDLE_DBC, RetCode);
        return 0;
    }

    // 2. Zapytanie SQL z parametrami (?)
    // Zapytanie wybiera kolumnę 'username'
    const char* sqlQuery = "SELECT username FROM users WHERE login = ? AND haslo = ?";

    // 3. Przygotowanie zapytania
    RetCode = SQLPrepareA(hStmt, (SQLCHAR*)sqlQuery, SQL_NTS);
    if (!SQL_SUCCEEDED(RetCode)) {
        HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, RetCode);
        SQLFreeHandle(SQL_HANDLE_STMT, hStmt);
        return 0;
    }

    // 4. Powiązanie parametrów wejściowych (Bind Parameters)

    // Parametr 1: LOGIN (VARCHAR)
    RetCode = SQLBindParameter(
        hStmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
        (SQLULEN)login.length(), 0, (SQLPOINTER)login.c_str(), 0, NULL
    );
    if (!SQL_SUCCEEDED(RetCode)) goto Cleanup;

    // Parametr 2: HASŁO (VARCHAR)
    RetCode = SQLBindParameter(
        hStmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_VARCHAR,
        (SQLULEN)haslo.length(), 0, (SQLPOINTER)haslo.c_str(), 0, NULL
    );
    if (!SQL_SUCCEEDED(RetCode)) goto Cleanup;

    // 5. Wykonanie zapytania
    RetCode = SQLExecute(hStmt);
    if (!SQL_SUCCEEDED(RetCode)) {
        HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, RetCode);
        goto Cleanup;
    }

    // 6. Powiązanie kolumny wyjściowej (Bind Column)
    // POWIĄZANIE DANYCH ZNAKOWYCH (SQL_C_CHAR) Z BUFOREM
    RetCode = SQLBindCol(
        hStmt, 1,
        SQL_C_CHAR, // Typ w C++: Znakowy
        usernameBuffer.data(), // Bufor do zapisu
        (SQLSMALLINT)usernameBuffer.size(), // Maksymalny rozmiar bufora
        &cbUsername // Faktyczna długość danych
    );
    if (!SQL_SUCCEEDED(RetCode)) goto Cleanup;

    // 7. Pobranie pierwszego wiersza
    RetCode = SQLFetch(hStmt);

Cleanup:
    // 8. Zwalnianie zasobów i zwrócenie wyniku
    SQLFreeHandle(SQL_HANDLE_STMT, hStmt);

    if (RetCode == SQL_SUCCESS || RetCode == SQL_SUCCESS_WITH_INFO) {
        // Konwersja bufora char na string o poprawnej długości
        string final_username(usernameBuffer.data(), (size_t)cbUsername);
        cout << "Logowanie pomyślne! Znaleziono użytkownika: " << final_username << endl;
        return 1; // Logowanie pomyślne
    }
    else if (RetCode == SQL_NO_DATA) {
        cout << "Błąd: Niepoprawny login lub hasło." << endl;
        return 0; // Nie znaleziono danych (niepoprawne logowanie)
    }
    else {
        // Inny błąd ODBC wystąpił
        HandleDiagnosticRecord(hStmt, SQL_HANDLE_STMT, RetCode);
        return 0;
    }
}

int main() {
    SYSTEM;

    // 1. Zmienne uchwytów
    SQLHENV hEnv = NULL; // Uchwyt Środowiska
    SQLHDBC hDbc = NULL; // Uchwyt Połączenia
    RETCODE RetCode;

    // 2. Alokacja uchwytu środowiska
    RetCode = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv);
    if (!SQL_SUCCEEDED(RetCode)) {
        cout << "Błąd alokacji uchwytu środowiska." << endl;
        return 1;
    }

    // 3. Ustawienie wersji ODBC
    RetCode = SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
    if (!SQL_SUCCEEDED(RetCode)) {
        HandleDiagnosticRecord(hEnv, SQL_HANDLE_ENV, RetCode);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return 1;
    }

    // 4. Alokacja uchwytu połączenia
    RetCode = SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc);
    if (!SQL_SUCCEEDED(RetCode)) {
        HandleDiagnosticRecord(hEnv, SQL_HANDLE_ENV, RetCode);
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
        return 1;
    }

    // 5. Łączenie z bazą danych
    const char* connString = "DRIVER={MySQL ODBC 9.5 Unicode Driver};SERVER=127.0.0.1;PORT=3306;DATABASE=cpp_projekt;UID=root;PWD=;";

    cout << "Próba połączenia..." << endl;
    SQLSMALLINT cbConnStrOut;

    RetCode = SQLDriverConnectA(hDbc,
        NULL,
        (SQLCHAR*)connString,
        (SQLSMALLINT)strlen(connString),
        NULL,
        0,
        &cbConnStrOut,
        SQL_DRIVER_COMPLETE);

    if (SQL_SUCCEEDED(RetCode)) {
        cout << "Połączono pomyślnie z bazą danych!" << endl;

        // Wczytywanie danych logowania po udanym połączeniu
        string login;
        string haslo;
        cout << "Podaj login" << endl;
        getline(cin, login);
        cout << "Podaj hasło" << endl;
        getline(cin, haslo);

        // Użycie hDbc, gdy jest aktywne
        sprawdzLogin(hDbc, login, haslo);
    }
    else {
        cout << "Błąd połączenia z bazą danych." << endl;
        HandleDiagnosticRecord(hDbc, SQL_HANDLE_DBC, RetCode);
    }

    // 6. Zwalnianie zasobów (na końcu, po użyciu hDbc)
    if (hDbc) {
        SQLDisconnect(hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, hDbc);
    }
    if (hEnv) {
        SQLFreeHandle(SQL_HANDLE_ENV, hEnv);
    }

    return 0;
}