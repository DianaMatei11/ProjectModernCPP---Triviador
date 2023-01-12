#ifndef INTREBARINUMERICE_H
#define INTREBARINUMERICE_H

#include <QMainWindow>
#include <cpr/cpr.h>
#include <crow.h>
#include <qelapsedtimer.h>
#include <qtimer.h>

QT_BEGIN_NAMESPACE
namespace Ui { class IntrebariNumerice; }
QT_END_NAMESPACE

class IntrebariNumerice : public QMainWindow
{
    Q_OBJECT

public:
    IntrebariNumerice(QWidget *parent = nullptr);
    ~IntrebariNumerice();
    void setUsername(const std::string& str);
    void AfisareIntrebare();
    void on_avantaj4_rasp_clicked();

    void on_avantaj1_rasp_clicked();

private slots:

    void on_IntrebareNumerica_linkActivated();

    void on_av0_clicked();

    void on_av1_clicked();

    void on_av2_clicked();

    void on_av3_clicked();

    void on_sendAnswer_clicked();

private:
    Ui::IntrebariNumerice *ui;
    std::string userName;
    bool answered = false;
    QElapsedTimer timer;
};
#endif // INTREBARINUMERICE_H
