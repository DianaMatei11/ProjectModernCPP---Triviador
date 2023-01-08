#include "harta.h"
#include "ui_harta.h"

harta::harta(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::harta)
{


    ui->setupUi(this);
    coord();
}

harta::~harta()
{
    delete ui;
}

void harta::mousePressEvent(QMouseEvent *ev)
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

void harta::coord()
{
    int x, y,  width,height;
    cpr::Response response = cpr::Get(
                    cpr::Url{ "http://localhost:14040/coordinates"}
                );
            auto aux = crow::json::load(response.text);
    for(auto a:aux)
    {
            x = aux["x"].i();
            y = aux["y"].i();
            width = aux["width"].i();
            height = aux["height"].i();
            patrat.push_back(QRect(x,y,width,height));
    }
    update();

}

void harta::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    int x,y,width,height;
    QPen pen;
    pen.setColor(QColorConstants::Svg::pink);
    p.setPen(pen);
    coord();
    QRect r(QPoint(x,y), QSize(width,height));
    p.drawRect(r);

    for(const auto& a:patrat)
    {
        p.drawRect(a);
    }

}

