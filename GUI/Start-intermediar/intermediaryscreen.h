#ifndef INTERMEDIARYSCREEN_H
#define INTERMEDIARYSCREEN_H

#include <QMainWindow>
#include "form.h"

namespace Ui {
class IntermediaryScreen;
}

class IntermediaryScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit IntermediaryScreen(QWidget *parent = nullptr);
    ~IntermediaryScreen();

private slots:
    void on_login_clicked();

    void on_signup_clicked();

private:
    Ui::IntermediaryScreen *ui;
    Form f;
};

#endif // INTERMEDIARYSCREEN_H
