#include "startscreen.h"
#include "ui_startscreen.h"
#include <QPalette>

StartScreen::StartScreen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartScreen)
{
    ui->setupUi(this);
    //this->centralWidget()->setStyleSheet("background-image:url(\"E:/Facultate/Anul II/Semestrul I/Modern C++/MainScreen Triviador.jpg""); background-position: center;");
   QPixmap bkgnd("E:/Facultate/Anul II/Semestrul I/Modern C++/MainScreen Triviador.jpg");
   bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
   QPalette palette;
   //palette.setBrush(QPalette::Background, bkgnd);
   palette.setBrush(QPalette::Window,bkgnd);
   this->setPalette(palette);

   QPixmap pixmap("E:/Facultate/Anul II/Semestrul I/Modern C++/logoFinal.png");
   pixmap= pixmap.scaled(this->size(), Qt::IgnoreAspectRatio);
   ui->logo->setPixmap(pixmap);
  // scene->addItem(1, &intscr);

}

StartScreen::~StartScreen()
{
    delete ui;
}



