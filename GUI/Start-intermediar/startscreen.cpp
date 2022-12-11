#include "startscreen.h"
#include "ui_startscreen.h"
#include <QPalette>

StartScreen::StartScreen(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartScreen)
{
    ui->setupUi(this);
   QPixmap bkgnd(":/images/images/MainScreen Triviador.jpg");
   bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
   QPalette palette;
   palette.setBrush(QPalette::Window,bkgnd);
   this->setPalette(palette);

   QPixmap pixmap(":/images/images/logoFinal.png");
   pixmap= pixmap.scaled(this->size(), Qt::IgnoreAspectRatio);
   ui->logo->setPixmap(pixmap);
  // scene->addItem(1, &intscr);

}
void StartScreen::on_START_clicked()
{
    hide();
    //intscr=new IntermediaryScreen(this);
    intscr.show();

}
StartScreen::~StartScreen()
{
    delete ui;
}



