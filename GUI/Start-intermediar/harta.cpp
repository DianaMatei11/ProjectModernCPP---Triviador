#include "harta.h"
#include "ui_harta.h"

Harta::Harta(QWidget *parent)
    : QMainWindow(parent), 
    ui(new Ui::harta)
{

    ui->setupUi(this);
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

