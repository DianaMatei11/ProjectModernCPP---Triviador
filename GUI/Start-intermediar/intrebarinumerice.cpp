#include "intrebarinumerice.h"
#include "ui_intrebarinumerice.h"

IntrebariNumerice::IntrebariNumerice(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::IntrebariNumerice)
{
    ui->setupUi(this);

    ui->av0->hide();
    ui->av1->hide();
    ui->av2->hide();
    ui->av3->hide();

}

void IntrebariNumerice::AfisareIntrebare()
{
    cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:14040/numericalQuestion" });
        auto aux = crow::json::load(response.text);

        
        timer.start();
        ui->IntrebareNumerica->setText(QString::fromLocal8Bit(static_cast<std::string> (aux["Question"])));


}

void IntrebariNumerice::on_IntrebareNumerica_linkActivated()
{
    //ui->raspuns_numeric->setCurrentIndex();
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


void IntrebariNumerice::on_av0_clicked()
{
    double time = timer.elapsed() / 1000.0;
    auto response = cpr::Put(
        cpr::Url{ "http://localhost:14040/Answer" },
        cpr::Payload{
           
            {"0", (ui->av0->text().toLocal8Bit().constData())},
            {"Time", std::to_string(time)}

        });
    ui->av1->setDisabled(false);
    ui->av2->setDisabled(false);
    ui->av3->setDisabled(false);

}


void IntrebariNumerice::on_av1_clicked()
{
    double time = timer.elapsed() / 1000.0;
    auto response = cpr::Put(
        cpr::Url{ "http://localhost:14040/Answer" },
        cpr::Payload{
            
            {"1", (ui->av1->text().toLocal8Bit().constData())},
            {"Time", std::to_string(time)}
        });

    ui->av0->setDisabled(false);
    ui->av2->setDisabled(false);
    ui->av3->setDisabled(false);

}


void IntrebariNumerice::on_av2_clicked()
{
    double time = timer.elapsed() / 1000.0;
    auto response = cpr::Put(
        cpr::Url{ "http://localhost:14040/Answer" },
        cpr::Payload{
           
            {"2", (ui->av2->text().toLocal8Bit().constData())},
            {"Time", std::to_string(time)}
            
        });

    ui->av1->setDisabled(false);
    ui->av0->setDisabled(false);
    ui->av3->setDisabled(false);

}


void IntrebariNumerice::on_av3_clicked()
{
    double time = timer.elapsed() / 1000.0;
    auto response = cpr::Put(
        cpr::Url{ "http://localhost:14040/Answer" },
        cpr::Payload{
            
            {"3", (ui->av3->text().toLocal8Bit().constData())},
            {"Time", std::to_string(time)}
            
        });

    ui->av1->setDisabled(false);
    ui->av2->setDisabled(false);
    ui->av0->setDisabled(false);

}

void IntrebariNumerice::on_sendAnswer_clicked()
{
    double time = timer.elapsed() / 1000.0;
    auto raspuns = ui->raspuns_numeric->text();
    auto response = cpr::Put(
        cpr::Url{ "http://localhost:14040/numericalQuestion/userAnswers" },
        cpr::Payload{
            
            {"username", (raspuns.toLocal8Bit().constData())},
            {"Time", (std::to_string(time))}
        });
}

