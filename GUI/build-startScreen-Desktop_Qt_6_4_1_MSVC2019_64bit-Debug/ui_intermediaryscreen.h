/********************************************************************************
** Form generated from reading UI file 'intermediaryscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTERMEDIARYSCREEN_H
#define UI_INTERMEDIARYSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_IntermediaryScreen
{
public:
    QWidget *centralwidget;
    QPushButton *login;
    QPushButton *signup;
    QLabel *logo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *IntermediaryScreen)
    {
        if (IntermediaryScreen->objectName().isEmpty())
            IntermediaryScreen->setObjectName("IntermediaryScreen");
        IntermediaryScreen->resize(800, 600);
        centralwidget = new QWidget(IntermediaryScreen);
        centralwidget->setObjectName("centralwidget");
        login = new QPushButton(centralwidget);
        login->setObjectName("login");
        login->setGeometry(QRect(260, 320, 301, 61));
        login->setStyleSheet(QString::fromUtf8("QPushButton \n"
"{background : rgb(115, 66, 55); color: rgb(245, 242, 220); font-size: 25px; font: Bold; font-family:Georgia; border-radius:15px\n"
"}\n"
"QPushButton:Hover\n"
"{\n"
"background-color: rgb(105,0,16);\n"
"}"));
        signup = new QPushButton(centralwidget);
        signup->setObjectName("signup");
        signup->setGeometry(QRect(260, 390, 301, 61));
        signup->setStyleSheet(QString::fromUtf8("QPushButton \n"
"{background : rgb(115, 66, 55); color: rgb(245, 242, 220); font-size: 25px; font: Bold; font-family:Georgia; border-radius:15px\n"
"}\n"
"QPushButton:Hover\n"
"{\n"
"background-color: rgb(105,0,16);\n"
"}"));
        logo = new QLabel(centralwidget);
        logo->setObjectName("logo");
        logo->setGeometry(QRect(0, 40, 721, 171));
        IntermediaryScreen->setCentralWidget(centralwidget);
        menubar = new QMenuBar(IntermediaryScreen);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        IntermediaryScreen->setMenuBar(menubar);
        statusbar = new QStatusBar(IntermediaryScreen);
        statusbar->setObjectName("statusbar");
        IntermediaryScreen->setStatusBar(statusbar);

        retranslateUi(IntermediaryScreen);

        QMetaObject::connectSlotsByName(IntermediaryScreen);
    } // setupUi

    void retranslateUi(QMainWindow *IntermediaryScreen)
    {
        IntermediaryScreen->setWindowTitle(QCoreApplication::translate("IntermediaryScreen", "MainWindow", nullptr));
        login->setText(QCoreApplication::translate("IntermediaryScreen", "Log in", nullptr));
        signup->setText(QCoreApplication::translate("IntermediaryScreen", "Sign up", nullptr));
        logo->setText(QCoreApplication::translate("IntermediaryScreen", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IntermediaryScreen: public Ui_IntermediaryScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTERMEDIARYSCREEN_H
