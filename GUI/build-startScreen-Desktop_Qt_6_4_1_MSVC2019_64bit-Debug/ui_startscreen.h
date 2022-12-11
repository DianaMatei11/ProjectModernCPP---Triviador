/********************************************************************************
** Form generated from reading UI file 'startscreen.ui'
**
** Created by: Qt User Interface Compiler version 6.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTSCREEN_H
#define UI_STARTSCREEN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StartScreen
{
public:
    QWidget *centralwidget;
    QPushButton *START;
    QLabel *logo;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *StartScreen)
    {
        if (StartScreen->objectName().isEmpty())
            StartScreen->setObjectName("StartScreen");
        StartScreen->resize(800, 600);
        centralwidget = new QWidget(StartScreen);
        centralwidget->setObjectName("centralwidget");
        START = new QPushButton(centralwidget);
        START->setObjectName("START");
        START->setGeometry(QRect(240, 360, 341, 61));
        START->setMouseTracking(true);
        START->setStyleSheet(QString::fromUtf8("QPushButton \n"
"{background : rgb(115, 66, 55); color: rgb(245, 242, 220); font-size: 25px; font: Bold; font-family:Georgia; border-radius:15px\n"
"}\n"
"QPushButton:Hover\n"
"{\n"
"background-color: rgb(105,0,16);\n"
"}"));
        logo = new QLabel(centralwidget);
        logo->setObjectName("logo");
        logo->setGeometry(QRect(0, 30, 691, 201));
        logo->setStyleSheet(QString::fromUtf8("logo.setStyleSheet(\"backgroung-image: url(\"E:/Facultate/Anul II/Semestrul I/Modern C++/logoFinal.png\")\")\n"
""));
        StartScreen->setCentralWidget(centralwidget);
        menubar = new QMenuBar(StartScreen);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 26));
        StartScreen->setMenuBar(menubar);
        statusbar = new QStatusBar(StartScreen);
        statusbar->setObjectName("statusbar");
        StartScreen->setStatusBar(statusbar);

        retranslateUi(StartScreen);

        QMetaObject::connectSlotsByName(StartScreen);
    } // setupUi

    void retranslateUi(QMainWindow *StartScreen)
    {
        StartScreen->setWindowTitle(QCoreApplication::translate("StartScreen", "StartScreen", nullptr));
        START->setText(QCoreApplication::translate("StartScreen", "START", nullptr));
        logo->setText(QCoreApplication::translate("StartScreen", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class StartScreen: public Ui_StartScreen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTSCREEN_H
