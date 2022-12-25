#ifndef INTREBARINUMERICE_H
#define INTREBARINUMERICE_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class IntrebariNumerice; }
QT_END_NAMESPACE

class IntrebariNumerice : public QMainWindow
{
    Q_OBJECT

public:
    IntrebariNumerice(QWidget *parent = nullptr);
    ~IntrebariNumerice();

private slots:
    void AfisareIntrebare();
    void on_IntrebareNumerica_linkActivated();

private:
    Ui::IntrebariNumerice *ui;
};
#endif // INTREBARINUMERICE_H
