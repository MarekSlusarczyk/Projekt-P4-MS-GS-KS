/********************************************************************************
** Form generated from reading UI file 'logowanie.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGOWANIE_H
#define UI_LOGOWANIE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_logowanie
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit_login;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_haslo;
    QPushButton *pushButton_zaloguj;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *logowanie)
    {
        if (logowanie->objectName().isEmpty())
            logowanie->setObjectName("logowanie");
        logowanie->resize(800, 600);
        centralwidget = new QWidget(logowanie);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(320, 140, 211, 161));
        widget = new QWidget(groupBox);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(10, 40, 179, 105));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        label = new QLabel(widget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        lineEdit_login = new QLineEdit(widget);
        lineEdit_login->setObjectName("lineEdit_login");

        horizontalLayout->addWidget(lineEdit_login);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        label_2 = new QLabel(widget);
        label_2->setObjectName("label_2");

        horizontalLayout_2->addWidget(label_2);

        lineEdit_haslo = new QLineEdit(widget);
        lineEdit_haslo->setObjectName("lineEdit_haslo");

        horizontalLayout_2->addWidget(lineEdit_haslo);


        verticalLayout->addLayout(horizontalLayout_2);

        pushButton_zaloguj = new QPushButton(widget);
        pushButton_zaloguj->setObjectName("pushButton_zaloguj");

        verticalLayout->addWidget(pushButton_zaloguj);

        logowanie->setCentralWidget(centralwidget);
        menubar = new QMenuBar(logowanie);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        logowanie->setMenuBar(menubar);
        statusbar = new QStatusBar(logowanie);
        statusbar->setObjectName("statusbar");
        logowanie->setStatusBar(statusbar);

        retranslateUi(logowanie);

        QMetaObject::connectSlotsByName(logowanie);
    } // setupUi

    void retranslateUi(QMainWindow *logowanie)
    {
        logowanie->setWindowTitle(QCoreApplication::translate("logowanie", "logowanie", nullptr));
        groupBox->setTitle(QCoreApplication::translate("logowanie", "Logowanie", nullptr));
        label->setText(QCoreApplication::translate("logowanie", "Login", nullptr));
        label_2->setText(QCoreApplication::translate("logowanie", "Has\305\202o", nullptr));
        pushButton_zaloguj->setText(QCoreApplication::translate("logowanie", "Zaloguj", nullptr));
    } // retranslateUi

};

namespace Ui {
    class logowanie: public Ui_logowanie {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGOWANIE_H
