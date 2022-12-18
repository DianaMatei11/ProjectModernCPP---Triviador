#include "intrebarigrila.h"
#include "ui_intrebarigrila.h"

IntrebariGrila::IntrebariGrila(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IntrebariGrila)
{
    ui->setupUi(this);

}

IntrebariGrila::~IntrebariGrila()
{
    delete ui;
}

void IntrebariGrila::on_varianta_a_clicked()
{
    auto response = cpr::Put(
        cpr::Url{ "http://localhost:14040/Quiz" },
        cpr::Payload{
            {
                "0", (ui->varianta_a->text().toLocal8Bit().constData())}
            });

}


void IntrebariGrila::on_varianta_b_clicked()
{
    auto response = cpr::Put(
        cpr::Url{ "http://localhost:14040/Quiz" },
        cpr::Payload{
            {
                "1", (ui->varianta_b->text().toLocal8Bit().constData())}
            });
}


void IntrebariGrila::on_varianta_c_clicked()
{
    auto response = cpr::Put(
        cpr::Url{ "http://localhost:14040/Quiz" },
        cpr::Payload{
            {
                "2", (ui->varianta_c->text().toLocal8Bit().constData())}
            });
}


void IntrebariGrila::on_varianta_d_clicked()
{
    auto response = cpr::Put(
        cpr::Url{ "http://localhost:14040/Quiz" },
        cpr::Payload{
            {
                "3", (ui->varianta_d->text().toLocal8Bit().constData())}
            });
}

