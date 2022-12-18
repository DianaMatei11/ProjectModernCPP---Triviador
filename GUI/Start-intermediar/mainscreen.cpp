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
    QPixmap pixmap(":/images/images/logoFinal.png");
    pixmap= pixmap.scaled(this->size(), Qt::IgnoreAspectRatio);
    ui->logo->setPixmap(pixmap);
    ui->logo2->setPixmap(pixmap);

    QPixmap pixmap2(":/images/images/back_icon.png");
    pixmap2= pixmap2.scaled(this->size(), Qt::IgnoreAspectRatio);
    QIcon aux(pixmap2);
    ui->back->setIcon(aux);
    ui->stats->setAlignment(Qt::AlignCenter);
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
    cpr::Response r=cpr::Get(cpr::Url{ "http://localhost:14040/history" });
    if (r.status_code == 200)
    {
        auto history = crow::json::load(r.text);
        for (const auto& performance : history)
        {

           // QString p1 = QStringLiteral("Number of games played: %1\n").arg(performance["meciuri_jucate"]);
           ui->stats->setText("Number of games played " + QString::number(performance["meciuri_jucate"]) +
              "\nTotal number of questions answered: " + QString::number(performance["raspunsuri_totale"]) +
               "\nNumber of correct answers: " + QString::number(performance["raspunsuri_corecte"]) +
                "\nMaximum score " + QString::number(performance["scor_maxim"]) +
                "\nMinimum score: " + QString::number(performance["scor_minim"]));


        }
    }
    else
    {
        ui->stats->setText("\n\nThere are no statistics available!");
        ui->stats->setAlignment(Qt::AlignCenter);
    }
}


void MainScreen::on_back_clicked()
{
    ui->account->setCurrentIndex(0);
}

