#ifndef INTREBARIGRILA_H
#define INTREBARIGRILA_H

#include <QMainWindow>
#include"form.h"
QT_BEGIN_NAMESPACE
namespace Ui { class IntrebariGrila; }
QT_END_NAMESPACE

class IntrebariGrila : public QMainWindow
{
    Q_OBJECT

public:
   explicit IntrebariGrila(QWidget *parent = nullptr);
    ~IntrebariGrila();

private:
    Ui::IntrebariGrila *ui;
    Form f;
private slots:
    void on_pushButton_2_clicked();
};
#endif // INTREBARIGRILA_H
