#include "rejestracja.h"
#include "ui_rejestracja.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
rejestracja::rejestracja(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::rejestracja)
{
    ui->setupUi(this);
}

rejestracja::~rejestracja()
{
    delete ui;
}

void rejestracja::on_pushButton_zaloguj_clicked()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Driver={MySQL ODBC 9.5 Unicode Driver};Server=localhost;Database=aplikacja;Uid=root;Pwd=;");
    QString login = ui->lineEdit_login->text();
    QString haslo = ui->lineEdit_haslo->text();
    QString haslo2 = ui->lineEdit_haslo2->text();
    if(haslo == haslo2){
    if(db.open()){
        QSqlQuery zapytanie;
        zapytanie.prepare("INSERT INTO `uzytkownicy` (`id`, `login`, `haslo`) VALUES (NULL, :login, :haslo);");
        zapytanie.bindValue(":login", login);
        zapytanie.bindValue(":haslo", haslo);
        if(zapytanie.exec())
        {
            QMessageBox::information(this, "Sukces", "Zarejestrowano pomyślnie!");
            close();
        }
        else
        {
            QMessageBox::critical(this, "Błąd SQL", zapytanie.lastError().text());
        }
    }else{
        QMessageBox::critical(this, "Błąd", db.lastError().text());
    }
    }else{
    QMessageBox::warning(this,"Bład","Hasła nie są takie sa,e");
    }
}

