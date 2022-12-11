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
    ui->password->setMaxLength(30);
    ui->username->setMaxLength(30);
}

void Form::setMode(bool m)

{
    mode=m;
}

Form::~Form()
{
    delete ui;
}

void Form::on_submit_clicked()
{
    if (ui->username->text().isEmpty() || ui->password->text().isEmpty())
    {
        ui->error->show();
    }
    else
    {
        ui->error->hide();
        if (mode)
        {
            auto response = cpr::Put(
                cpr::Url{ "http://localhost:14040/verifylogin" },
                cpr::Payload{
                    { "Name", ui->username->text().toStdString()},
                    { "Password", ui->password->text().toStdString() }
                }
            );
            if (response.status_code == 200 || response.status_code == 201) {

            }
            else {
                QErrorMessage msg;
                msg.showMessage("Invalid username or password!");
            }


        }
        else
        {
            auto response = cpr::Post(
                cpr::Url{ "http://localhost:14040/createnewuser" },
                cpr::Payload{
                    { "Name", ui->username->text().toStdString()},
                    { "Password", ui->password->text().toStdString() }
                }
            );
            if (response.status_code == 200 || response.status_code == 201) {

            }
            else {
                QErrorMessage msg;
                msg.showMessage("Invalid username or password!");
            }

        }


    }
}

