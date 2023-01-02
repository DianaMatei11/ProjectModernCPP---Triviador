#include "intrebarigrila.h"
#include "ui_intrebarigrila.h"
#include<qstring.h>
#include <cpr/cpr.h>
#include <crow.h>

IntrebariGrila::IntrebariGrila(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IntrebariGrila)
{
    ui->setupUi(this);

}
void  IntrebariGrila::AfisareIntrebareGrila() {
    cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:14040/Quiz" });
    auto aux = crow::json::load(response.text);
    
    ui->label->setText(QString::fromLocal8Bit(static_cast<std::string> (aux["Enunt"])));
    ui->varianta_a->setText(QString::fromLocal8Bit(static_cast<std::string> (aux["Optiune0"])));
    ui->varianta_b->setText(QString::fromLocal8Bit(static_cast<std::string> (aux["Optiune1"])));
    ui->varianta_c->setText(QString::fromLocal8Bit(static_cast<std::string> (aux["Optiune2"])));
    ui->varianta_d->setText(QString::fromLocal8Bit(static_cast<std::string> (aux["Optiune3"])));

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
    ui->varianta_b->setDisabled(false);
    ui->varianta_c->setDisabled(false);
    ui->varianta_d->setDisabled(false);

}


void IntrebariGrila::on_varianta_b_clicked()
{
    auto response = cpr::Put(
        cpr::Url{ "http://localhost:14040/Quiz" },
        cpr::Payload{
            {
                "1", (ui->varianta_b->text().toLocal8Bit().constData())}
            });
    ui->varianta_a->setDisabled(false);
    ui->varianta_c->setDisabled(false);
    ui->varianta_d->setDisabled(false);

}


void IntrebariGrila::on_varianta_c_clicked()
{
    auto response = cpr::Put(
        cpr::Url{ "http://localhost:14040/Quiz" },
        cpr::Payload{
            {
                "2", (ui->varianta_c->text().toLocal8Bit().constData())}
            });
    ui->varianta_a->setDisabled(false);
    ui->varianta_b->setDisabled(false);
    ui->varianta_d->setDisabled(false);

}


void IntrebariGrila::on_varianta_d_clicked()
{
    auto response = cpr::Put(
        cpr::Url{ "http://localhost:14040/Quiz" },
        cpr::Payload{
            {
                "3", (ui->varianta_d->text().toLocal8Bit().constData())}
            });
    ui->varianta_a->setDisabled(false);
    ui->varianta_b->setDisabled(false);
    ui->varianta_c->setDisabled(false);

}


void IntrebariGrila::on_pushButton_clicked()
{
    auto response=cpr::Get(
                cpr::Url{ "http://localhost:14040/Avantaj" }
                );
    int index1=response["index1"].i();
    int index2=response["index2"].i();
    if(index1!=0 || index2!=0)
        ui->varianta_a->hide();

    if(index1!=1 || index2!=1)
        ui->varianta_b->hide();

    if(index1!=2 || index2!=2)
        ui->varianta_c->hide();

    if(index1!=3||index2!=3)
        ui->varianta_d->hide();
}

