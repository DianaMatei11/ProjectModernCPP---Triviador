#include "mainscreen.h"
#include "ui_mainscreen.h"

MainScreen::MainScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainScreen)
{
    ui->setupUi(this);
   QPixmap bkgnd(":/images/images/AccountScreen.jpg");
   bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
   QPalette palette;
   palette.setBrush(QPalette::Window,bkgnd);
   this->setPalette(palette);


    //this->setStyleSheet("background-image:url(:/images/images/AccountScreen.jpg; background-repeat:no-repeat;");
   

    ui->setupUi(this);
    QPixmap pixmap(":/images/images/logoFinal.png");
    pixmap= pixmap.scaled(this->size(), Qt::IgnoreAspectRatio);
    ui->logo->setPixmap(pixmap);
    ui->logo2->setPixmap(pixmap);

    QPixmap pixmap2(":/images/images/back_icon.png");
    pixmap2= pixmap2.scaled(this->size(), Qt::IgnoreAspectRatio);
    QIcon aux(pixmap2);
    ui->back->setIcon(aux);

    ui->account->setCurrentIndex(0);
}

MainScreen::~MainScreen()
{
    delete ui;
}



void MainScreen::on_configuration_clicked()
{
    ui->account->setCurrentIndex(2);
}


void MainScreen::on_statistics_clicked()
{
    ui->account->setCurrentIndex(1);
}


void MainScreen::on_back_clicked()
{
    ui->account->setCurrentIndex(0);
}

