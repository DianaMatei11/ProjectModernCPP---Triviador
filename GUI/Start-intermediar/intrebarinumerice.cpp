#include "intrebarinumerice.h"
#include "ui_intrebarinumerice.h"

IntrebariNumerice::IntrebariNumerice(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IntrebariNumerice)
{
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
