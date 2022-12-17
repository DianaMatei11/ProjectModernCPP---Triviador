#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>
//#include <cpr/cpr.h>
//#include <crow.h>

namespace Ui {
class MainScreen;
}

class MainScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = nullptr);
    ~MainScreen();

private slots:
    void on_configuration_clicked();

    void on_statistics_clicked();

    void on_back_clicked();

private:
    Ui::MainScreen *ui;
};

#endif // MAINSCREEN_H
