#include "intermediaryscreen.h"
#include "ui_intermediaryscreen.h"

IntermediaryScreen::IntermediaryScreen(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::IntermediaryScreen)
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
}

IntermediaryScreen::~IntermediaryScreen()
{
    delete ui;
}
