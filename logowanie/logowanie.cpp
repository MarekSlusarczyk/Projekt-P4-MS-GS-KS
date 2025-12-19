#include "logowanie.h"
#include "./ui_logowanie.h"
#include <QMessageBox>
#include <QSqlQuery>

QString loginglo = "nazwa";
logowanie::logowanie(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::logowanie)
{
    ui->setupUi(this);
}

logowanie::~logowanie()
{
    delete ui;
}

void logowanie::on_pushButton_zaloguj_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Driver={MySQL ODBC 9.5 Unicode Driver};Server=localhost;Database=aplikacja;Uid=root;Pwd=;");
    QString login = ui->lineEdit_login->text();
    loginglo = ui->lineEdit_login->text();
    QString haslo = ui->lineEdit_haslo->text();

    if(db.open()){
        QSqlQuery zapytanie;
        zapytanie.prepare("SELECT * FROM uzytkownicy WHERE login = :login AND haslo = :haslo");
        zapytanie.bindValue(":login", login);
        zapytanie.bindValue(":haslo", haslo);
        if(zapytanie.exec())
        {
            if(zapytanie.next())
            {
                QMessageBox::information(this, "Sukces", "Zalogowano pomyślnie!");
            }
            else
            {
                QMessageBox::warning(this, "Błąd", "Błędny login lub hasło.");
            }
        }
        else
        {
            QMessageBox::critical(this, "Błąd SQL", zapytanie.lastError().text());
        }
    }else{
        QMessageBox::critical(this, "Błąd", db.lastError().text());
    }


}

void logowanie::on_pushButton_dorejestracji_clicked()
{
    hide();
    Rejestracja = new rejestracja(this);
    Rejestracja->exec();
    show();
}

