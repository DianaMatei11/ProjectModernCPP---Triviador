#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>
#include <cpr/cpr.h>
#include <crow.h>
#include <qtimer.h>
#include "harta.h"

namespace Ui {
class MainScreen;
}

class MainScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget* parent = nullptr);
    void setUsername(const std::string& str);
    ~MainScreen();

private:
    void addPlayersOnTheScreen();
    void findOutStartGame();

private slots:
    void on_configuration_clicked();

    void on_statistics_clicked();

    void on_back_clicked();

    void on_logOut_clicked();

    void on_back_2_clicked();

    void on_ready_clicked();

private:
    Ui::MainScreen *ui;
    std::string start;
    std::string userName;
    QColor userColor;

    Harta harta;
};

#endif // MAINSCREEN_H
