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

void MainScreen::setUsername(std::string str)
{
    this->userName = str;
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
    cpr::Response r = cpr::Get(cpr::Url{ "http://localhost:14040/Statistics" }, cpr::Parameters{ {"username", userName} });
    if (r.status_code == 200)
    {
        auto history = crow::json::load(r.text);
        for (const auto& performance : history)
        {
           // auto t = performance["meciuri_jucate"];
          QString p1 = QStringLiteral("Number of games played: %1\n").arg(performance["meciuri_jucate"].i());
          QString p2= QStringLiteral("Number of questions answered: %1\n").arg(performance["raspunsuri_totale"].i());
          QString p3= QStringLiteral("Number of correct answerd: %1\n").arg(performance["raspunsuri_corecte"].i());
          QString p4= QStringLiteral("Maximum score: %1\n").arg(performance["scor_maxim"].i());
          QString p5= QStringLiteral("Minimum score: %1\n").arg(performance["scor_minim"].i());
          ui->stats->setText(p1+p2+p3+p4+p5);


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

