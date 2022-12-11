#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Attempt1.h"

class Attempt1 : public QMainWindow
{
    Q_OBJECT

public:
    Attempt1(QWidget *parent = nullptr);
    ~Attempt1();

private:
    Ui::Attempt1Class ui;
};
