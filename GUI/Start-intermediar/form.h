#ifndef FORM_H
#define FORM_H

#include <QWidget>
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
private:
    Ui::Form *ui;
    bool mode;
};

#endif // FORM_H
