#ifndef DODAJ_H
#define DODAJ_H

#include <QDialog>

namespace Ui {
class dodaj;
}

class dodaj : public QDialog
{
    Q_OBJECT

public:
    explicit dodaj(QWidget *parent = nullptr);
    ~dodaj();

private slots:
    void on_but_zdjecie_clicked();

    void on_pushButton_dodaj_clicked();

private:
    Ui::dodaj *ui;
    QByteArray zdjeciebin;
};

#endif // DODAJ_H
