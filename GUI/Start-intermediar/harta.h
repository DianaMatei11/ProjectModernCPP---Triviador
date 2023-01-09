#ifndef HARTA_H
#define HARTA_H

#include<vector>
#include <QMainWindow>
#include <QPushButton>
#include <QPen>
#include <QPainter>
#include <QMouseEvent>
#include <cpr/cpr.h>
#include <crow.h>


namespace Ui { class harta; }

class Harta : public QMainWindow
{
    Q_OBJECT

public:

    explicit Harta(QWidget* parent = nullptr);
    void mousePressEvent(QMouseEvent* ev);
    void paintEvent(QPaintEvent*);
    void coord();
    ~Harta();
private slots:

private:
    std::vector<QRect> patrat;
    Ui::harta* ui;
};
#endif // HARTA_H