#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <cpr/cpr.h>
#include <QErrorMessage>
#include "mainscreen.h"

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr, bool mode=true);
    void setMode(bool m);
    ~Form();

private slots:
    void on_submit_clicked();

private:
    Ui::Form *ui;
    bool mode;
    MainScreen ms;



};

#endif // FORM_H
