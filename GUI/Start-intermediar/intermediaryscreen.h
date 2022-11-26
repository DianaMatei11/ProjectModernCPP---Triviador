#ifndef INTERMEDIARYSCREEN_H
#define INTERMEDIARYSCREEN_H

#include <QMainWindow>

namespace Ui {
class IntermediaryScreen;
}

class IntermediaryScreen : public QMainWindow
{
    Q_OBJECT

public:
    explicit IntermediaryScreen(QWidget *parent = nullptr);
    ~IntermediaryScreen();

private:
    Ui::IntermediaryScreen *ui;
};

#endif // INTERMEDIARYSCREEN_H
