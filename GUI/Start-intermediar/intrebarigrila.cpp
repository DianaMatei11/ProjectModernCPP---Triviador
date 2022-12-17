#include "intrebarigrila.h"
#include "ui_intrebarigrila.h"

IntrebariGrila::IntrebariGrila(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IntrebariGrila)
{
    ui->setupUi(this);
    QPixmap bkgnd("background-color: rgb(189, 158, 122)");
    bkgnd=bkgnd.scaled(this->size(),Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window,bkgnd);
    this->setPalette(palette);

    QPixmap pixmap(":/images/images/logoFinal.png");
    pixmap = pixmap.scaled(this->size(), Qt::IgnoreAspectRatio);
    ui->logo->setPixmap(pixmap);
}

IntrebariGrila::~IntrebariGrila()
{
    delete ui;
}

void IntrebariGrila::on_pushButton_2_clicked()
{
    hide();

}

