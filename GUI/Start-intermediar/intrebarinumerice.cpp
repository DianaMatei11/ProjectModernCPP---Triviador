#include "intrebarinumerice.h"
#include "ui_intrebarinumerice.h"

IntrebariNumerice::IntrebariNumerice(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IntrebariNumerice)
{
    ui->av0->hide();
    ui->av1->hide();
    ui->av2->hide();
    ui->av3->hide();

    ui->setupUi(this);
}

void IntrebariNumerice::AfisareIntrebare()
{
    cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:14040/numericalQuestion" });
        auto aux = crow::json::load(response.text);

        ui->intrebare_grila->setText(QString::fromLocal8Bit(static_cast<std::string> (aux["Question"])));

}
void IntrebariNumerice::on_IntrebareNumerica_linkActivated()
{
    ui->raspuns_numeric->setCurrentIndex();
}


IntrebariNumerice::~IntrebariNumerice()
{
    delete ui;
}


void IntrebariNumerice::on_avantaj4_rasp_clicked()
{
    ui->av0->show();
    ui->av1->show();
    ui->av2->show();
    ui->av3->show();
    ui->avantaj1_rasp->setDisabled(false);
    ui->raspuns_numeric->setDisabled(false);

    cpr::Response response = cpr::Get(
                cpr::Url{ "http://localhost:14040/NumericalQuestion/Avantaj/4Answer" }
                );
        auto aux = crow::json::load(response.text);
        ui->av0->setText(QString::fromLocal8Bit(static_cast<std::string> (aux["varianta0"])));
        ui->av1->setText(QString::fromLocal8Bit(static_cast<std::string> (aux["varianta1"])));
        ui->av2->setText(QString::fromLocal8Bit(static_cast<std::string> (aux["varianta2"])));
        ui->av3->setText(QString::fromLocal8Bit(static_cast<std::string> (aux["varianta3"])));

}


void IntrebariNumerice::on_avantaj1_rasp_clicked()
{
    ui->avantaj4_rasp->setDisabled(false);
    cpr::Response response = cpr::Get(
                cpr::Url{ "http://localhost:14040//NumericalQuestion/Avantaj/1Answer" }
                );
    auto aux = crow::json::load(response.text);
    ui->raspuns_numeric->setText(QString::fromLocal8Bit(static_cast<std::string> (aux["varianta"])));

}

