#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent, bool mode) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    this->mode=mode;
    QPixmap bkgnd(":/images/images/MainScreen Triviador.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    //palette.setBrush(QPalette::Background, bkgnd);
    palette.setBrush(QPalette::Window,bkgnd);
    this->setPalette(palette);

    QPixmap pixmap(":/images/images/logoFinal.png");
    pixmap= pixmap.scaled(this->size(), Qt::IgnoreAspectRatio);
    ui->logo->setPixmap(pixmap);

    ui->password->setEchoMode(QLineEdit::Password);
    ui->error->hide();
}

void Form::setMode(bool m)

{
    mode=m;
}

Form::~Form()
{
    delete ui;
}




