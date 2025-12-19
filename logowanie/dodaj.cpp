#include "dodaj.h"
#include "ui_dodaj.h"
#include <QFileDialog>
#include <QSqlQuery>
#include <QByteArray>
#include <QMessageBox>

dodaj::dodaj(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::dodaj)
{
    ui->setupUi(this);
}

dodaj::~dodaj()
{
    delete ui;
}



void dodaj::on_but_zdjecie_clicked()
{
    QString sciezka = QFileDialog::getOpenFileName(this,"Wybierz zdjęcie","","Obrazy (*.png *.jpg *.jpeg *.bmp)");
    if (sciezka.isEmpty()) return;
    QFile plik(sciezka);
    if(plik.open(QIODevice::ReadOnly)){
        this->zdjeciebin = plik.readAll();
    }


}


void dodaj::on_pushButton_dodaj_clicked()
{
    QString nazwa = ui->lineEdit_nazwa->text();
    float cena = ui->lineEdit_cena->text().toFloat();
    QString kategoria = ui->comboBox_kategoria->currentText();
    QString opis = ui->lineEdit_opis->text();
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Driver={MySQL ODBC 9.5 Unicode Driver};Server=localhost;Database=aplikacja;Uid=root;Pwd=;");
    if(db.open()){
        QSqlQuery zapytanie;
        zapytanie.prepare("INSERT INTO `aukcje` (`id`, `nazwa`, `cena`, `kategoria`, `opis`, `zdjecie`, `id_uzytkownika`) VALUES (NULL, :nazwa, :cena, :kategoria, :opis, :zdjecie,'1');");
        zapytanie.bindValue(":nazwa",nazwa);
        zapytanie.bindValue(":cena",cena);
        zapytanie.bindValue(":kategoria",kategoria);
        zapytanie.bindValue(":opis",opis);
        zapytanie.bindValue(":zdjecie",this -> zdjeciebin);
        if(zapytanie.exec())
        {
            QMessageBox::information(this, "Sukces", "Dodano twoje ogłoszenie!");
            close();
        }
        else
        {
            QMessageBox::critical(this, "Błąd SQL","Błąd zapytania");
        }
    }else{
        QMessageBox::critical(this,"Błąd z bazą danych","Wystąpił błąd bazy danych");
    }
}

