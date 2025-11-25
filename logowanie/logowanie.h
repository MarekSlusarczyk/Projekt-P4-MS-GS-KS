#ifndef LOGOWANIE_H
#define LOGOWANIE_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include "rejestracja.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class logowanie;
}
QT_END_NAMESPACE

class logowanie : public QMainWindow
{
    Q_OBJECT

public:
    logowanie(QWidget *parent = nullptr);
    ~logowanie();

private slots:
    void on_pushButton_zaloguj_clicked();

    void on_pushButton_dorejestracji_clicked();

private:
    Ui::logowanie *ui;
    rejestracja *Rejestracja;
};
#endif // LOGOWANIE_H
