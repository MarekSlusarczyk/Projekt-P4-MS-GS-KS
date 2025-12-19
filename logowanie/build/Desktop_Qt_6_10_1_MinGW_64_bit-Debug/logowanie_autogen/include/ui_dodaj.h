/********************************************************************************
** Form generated from reading UI file 'dodaj.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DODAJ_H
#define UI_DODAJ_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_dodaj
{
public:
    QHBoxLayout *horizontalLayout_6;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_nazwa;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *lineEdit_cena;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_3;
    QComboBox *comboBox_kategoria;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *lineEdit_opis;
    QVBoxLayout *verticalLayout_2;
    QPushButton *but_zdjecie;
    QPushButton *pushButton_dodaj;

    void setupUi(QDialog *dodaj)
    {
        if (dodaj->objectName().isEmpty())
            dodaj->setObjectName("dodaj");
        dodaj->resize(334, 556);
        horizontalLayout_6 = new QHBoxLayout(dodaj);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        groupBox = new QGroupBox(dodaj);
        groupBox->setObjectName("groupBox");
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        horizontalLayout_2->addWidget(label);

        lineEdit_nazwa = new QLineEdit(groupBox);
        lineEdit_nazwa->setObjectName("lineEdit_nazwa");

        horizontalLayout_2->addWidget(lineEdit_nazwa);


        verticalLayout_3->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout_3->addWidget(label_2);

        lineEdit_cena = new QLineEdit(groupBox);
        lineEdit_cena->setObjectName("lineEdit_cena");

        horizontalLayout_3->addWidget(lineEdit_cena);


        verticalLayout_3->addLayout(horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        horizontalLayout_4->addWidget(label_3);

        comboBox_kategoria = new QComboBox(groupBox);
        comboBox_kategoria->addItem(QString());
        comboBox_kategoria->addItem(QString());
        comboBox_kategoria->addItem(QString());
        comboBox_kategoria->addItem(QString());
        comboBox_kategoria->setObjectName("comboBox_kategoria");

        horizontalLayout_4->addWidget(comboBox_kategoria);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        label_4 = new QLabel(groupBox);
        label_4->setObjectName("label_4");

        horizontalLayout_5->addWidget(label_4);

        lineEdit_opis = new QLineEdit(groupBox);
        lineEdit_opis->setObjectName("lineEdit_opis");
        lineEdit_opis->setMinimumSize(QSize(200, 100));

        horizontalLayout_5->addWidget(lineEdit_opis);


        verticalLayout_3->addLayout(horizontalLayout_5);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        but_zdjecie = new QPushButton(groupBox);
        but_zdjecie->setObjectName("but_zdjecie");

        verticalLayout_2->addWidget(but_zdjecie);

        pushButton_dodaj = new QPushButton(groupBox);
        pushButton_dodaj->setObjectName("pushButton_dodaj");

        verticalLayout_2->addWidget(pushButton_dodaj);


        verticalLayout_3->addLayout(verticalLayout_2);


        horizontalLayout_6->addWidget(groupBox);


        retranslateUi(dodaj);

        QMetaObject::connectSlotsByName(dodaj);
    } // setupUi

    void retranslateUi(QDialog *dodaj)
    {
        dodaj->setWindowTitle(QCoreApplication::translate("dodaj", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("dodaj", "Dodaj", nullptr));
        label->setText(QCoreApplication::translate("dodaj", "Nazwa", nullptr));
        label_2->setText(QCoreApplication::translate("dodaj", "Cena(z\305\202)", nullptr));
        label_3->setText(QCoreApplication::translate("dodaj", "Kategoria", nullptr));
        comboBox_kategoria->setItemText(0, QCoreApplication::translate("dodaj", "Motoryzacja", nullptr));
        comboBox_kategoria->setItemText(1, QCoreApplication::translate("dodaj", "Ubrania", nullptr));
        comboBox_kategoria->setItemText(2, QCoreApplication::translate("dodaj", "Elektronika", nullptr));
        comboBox_kategoria->setItemText(3, QCoreApplication::translate("dodaj", "Dom i ogr\303\263d", nullptr));

        label_4->setText(QCoreApplication::translate("dodaj", "Opis", nullptr));
        but_zdjecie->setText(QCoreApplication::translate("dodaj", "Zdj\304\231cia", nullptr));
        pushButton_dodaj->setText(QCoreApplication::translate("dodaj", "Dodaj", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dodaj: public Ui_dodaj {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DODAJ_H
