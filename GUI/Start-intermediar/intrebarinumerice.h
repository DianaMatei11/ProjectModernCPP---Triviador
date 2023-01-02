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

    void on_pushButton_clicked();

    void on_av0_clicked();

    void on_av1_clicked();

    void on_av2_clicked();

    void on_av3_clicked();

private:
    Ui::IntrebariNumerice *ui;
};
#endif // INTREBARINUMERICE_H
