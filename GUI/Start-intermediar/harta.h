#ifndef HARTA_H
#define HARTA_H

#include<vector>
#include <QMainWindow>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui { class harta; }
QT_END_NAMESPACE

class harta : public QMainWindow
{
    Q_OBJECT

public:

    harta(QWidget* parent = nullptr);
    void mousePressEvent(QMouseEvent* ev);
    void paintEvent(QPaintEvent*);
    void coord();
    ~harta();
private slots:
    void on_showPaths_clicked();
private:
    std::vector<QRect> patrat;
    Ui::harta* ui;
    QPushButton* buton;
};
#endif // HARTA_H