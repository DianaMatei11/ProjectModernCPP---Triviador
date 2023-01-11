#include "harta.h"
#include "ui_harta.h"
#include<queue>>
#include<QLabel>
Harta::Harta(QWidget *parent)
    : QMainWindow(parent), 
    ui(new Ui::harta)
{

    ui->setupUi(this);
    ui->game->insertWidget(1,&intrebareNumerica);
    ui->game->insertWidget(2,&intrebareGrila);   
    ui->game->setCurrentIndex(0);
}

void Harta::setUsername(std::string str)
{
    userName = str;
}

void Harta::setColor(QColor color)
{
    userColor = color;
}

Harta::~Harta()
{
    delete ui;
}

void Harta::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
       {
            auto response = cpr::Put(
            cpr::Url{ "http://localhost:14040/CoordClickHarta" },
            cpr::Payload{
                
                {"x", "" + static_cast<int>(ev->position().x())},
                {"y", "" + static_cast<int>(ev->position().y())}
                
            });
    }
}

void Harta::coord()
{
    float x, y,  width,height;
    cpr::Response response = cpr::Get(
                    cpr::Url{ "http://localhost:14040/coordinates"}
                );
    auto aux = crow::json::load(response.text);
    for(const auto& a : aux)
    {
            x = a["x"].d();
            y = a["y"].d();
            width = a["width"].d();
            height = a["height"].d();
            patrat.push_back(QRect(x,y,width,height));
    }
    update();

}


void Harta::gameManager()
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(3000);
    loop.exec();
    ui->game->setCurrentWidget(&intrebareNumerica);
    //intrebareNumerica.show();
    //hide();
}

void Harta::getScore()
{
    std::queue<QLabel> labels;

    while(true)
    {
        cpr::Response response = cpr::Get(
                        cpr::Url{ "http://localhost:14040/getScore"}
                    );
        auto aux = crow::json::load(response.text);
        int numar_jucatori=aux.size();
        if(numar_jucatori==2)
        {
            ui->player1->hide();
            ui->player4->hide();
            labels.push(ui->player2);
            labels.push(ui->player3);

        }
        else if(numar_jucatori==3)
        {
            ui->player4->hide();
            labels.push(ui->player1);
            labels.push(ui->player2);
            labels.push(ui->player3);
        }
        else
        {
            labels.push(ui->player1);
            labels.push(ui->player2);
            labels.push(ui->player3);
            labels.push(ui->player4);
        }
        for(const auto& player:aux)
        {
            const auto & curent_label= labels.front();

            switch (player["color"])
            {
            case 0:
                curent_label.setStyleSheet("QLabel { background-color : red }");

                break;
            case 1:
                curent_label.setStyleSheet("QLabel { background-color : yellow }");
                break;
            case 2:
                curent_label.setStyleSheet("QLabel { background-color : blue }");
                break;
            case 3:
                curent_label.setStyleSheet("QLabel { background-color : green }");
                break;
            }
            curent_label.setText(player["name"]+" - "+ player["score"]);

            labels.pop();

        }


    }
}

void Harta::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    int x,y,width,height;
    QPen pen;
    pen.setWidth(2);
    p.setPen(pen);
    for(const auto& a:patrat)
    {
        p.drawRect(a);
    }

}

