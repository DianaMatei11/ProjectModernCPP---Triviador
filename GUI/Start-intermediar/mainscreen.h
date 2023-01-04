#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QMainWindow>
#include <cpr/cpr.h>
#include <crow.h>


namespace Ui {
class MainScreen;
}

class MainScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainScreen(QWidget *parent = nullptr);
    void setUsername(std::string str);
    void addPlayersOnTheScreen();
    ~MainScreen();

private slots:
    void on_configuration_clicked();

    void on_statistics_clicked();

    void on_back_clicked();

    void on_logOut_clicked();

    void on_back_2_clicked();


private:
    Ui::MainScreen *ui;
    std::string userName;
    QColor userColor;
};

#endif // MAINSCREEN_H
