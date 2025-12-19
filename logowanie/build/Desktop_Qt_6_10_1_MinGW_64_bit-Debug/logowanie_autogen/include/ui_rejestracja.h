/********************************************************************************
** Form generated from reading UI file 'rejestracja.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REJESTRACJA_H
#define UI_REJESTRACJA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_rejestracja
{
public:
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_login;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_haslo;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_haslo2;
    QPushButton *pushButton_zaloguj;

    void setupUi(QDialog *rejestracja)
    {
        if (rejestracja->objectName().isEmpty())
            rejestracja->setObjectName("rejestracja");
        rejestracja->resize(827, 616);
        groupBox = new QGroupBox(rejestracja);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(240, 130, 256, 193));
        horizontalLayout_4 = new QHBoxLayout(groupBox);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(groupBox);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEdit_login = new QLineEdit(groupBox);
        lineEdit_login->setObjectName("lineEdit_login");

        horizontalLayout->addWidget(lineEdit_login);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        lineEdit_haslo = new QLineEdit(groupBox);
        lineEdit_haslo->setObjectName("lineEdit_haslo");
        lineEdit_haslo->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_2->addWidget(lineEdit_haslo);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(groupBox);
        label_3->setObjectName("label_3");

        horizontalLayout_3->addWidget(label_3);

        lineEdit_haslo2 = new QLineEdit(groupBox);
        lineEdit_haslo2->setObjectName("lineEdit_haslo2");
        lineEdit_haslo2->setEchoMode(QLineEdit::EchoMode::Password);

        horizontalLayout_3->addWidget(lineEdit_haslo2);


        verticalLayout->addLayout(horizontalLayout_3);

        pushButton_zaloguj = new QPushButton(groupBox);
        pushButton_zaloguj->setObjectName("pushButton_zaloguj");

        verticalLayout->addWidget(pushButton_zaloguj);


        horizontalLayout_4->addLayout(verticalLayout);


        retranslateUi(rejestracja);

        QMetaObject::connectSlotsByName(rejestracja);
    } // setupUi

    void retranslateUi(QDialog *rejestracja)
    {
        rejestracja->setWindowTitle(QCoreApplication::translate("rejestracja", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("rejestracja", "Rejestracja", nullptr));
        label->setText(QCoreApplication::translate("rejestracja", "Login", nullptr));
        label_2->setText(QCoreApplication::translate("rejestracja", "Has\305\202o", nullptr));
        label_3->setText(QCoreApplication::translate("rejestracja", "Powt\303\263rz has\305\202o", nullptr));
        pushButton_zaloguj->setText(QCoreApplication::translate("rejestracja", "Zarejestruj", nullptr));
    } // retranslateUi

};

namespace Ui {
    class rejestracja: public Ui_rejestracja {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REJESTRACJA_H
