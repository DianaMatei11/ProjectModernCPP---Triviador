#include "intrebarinumerice.h"
#include "ui_intrebarinumerice.h"

IntrebariNumerice::IntrebariNumerice(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IntrebariNumerice)
{
    ui->setupUi(this);
}

IntrebariNumerice::~IntrebariNumerice()
{
    delete ui;
}


void IntrebariNumerice::on_IntrebareNumerica_linkActivated()
{

}

