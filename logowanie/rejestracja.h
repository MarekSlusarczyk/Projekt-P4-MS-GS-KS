#ifndef REJESTRACJA_H
#define REJESTRACJA_H

#include <QDialog>


namespace Ui {
class rejestracja;
}

class rejestracja : public QDialog
{
    Q_OBJECT

public:
    explicit rejestracja(QWidget *parent = nullptr);
    ~rejestracja();

private slots:
    void on_pushButton_zaloguj_clicked();

private:
    Ui::rejestracja *ui;
};

#endif // REJESTRACJA_H
