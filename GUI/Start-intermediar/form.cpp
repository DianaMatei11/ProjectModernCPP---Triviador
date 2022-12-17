#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
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
    if (!mode)
        ui->back->setText("If you already have an account, log in");
    else
        ui->back->setText("If you don't have an account, sign up");
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
                    { "Name", (ui->username->text().toLocal8Bit().constData())},
                    { "Password", (ui->password->text().toLocal8Bit().constData())}
                }
            );
            if (response.status_code == 200 || response.status_code == 201) {
                ms.show();
                hide();
            }
            else {
                QMessageBox msg;
                if(response.status_code==409)
                    msg.setText("Wrong password");
                if(response.status_code==404)
                    msg.setText("User not found");
                if(response.status_code==400)
                    msg.setText("There was an error in the transmitted information");
                msg.exec();
            }


        }
        else
        {
            auto response = cpr::Post(
                cpr::Url{ "http://localhost:14040/createnewuser" },
                cpr::Payload{
                    { "Name", ui->username->text().toLocal8Bit().constData()},
                    { "Password", ui->password->text().toLocal8Bit().constData()}
                }
            );
            if (response.status_code == 200 || response.status_code == 201) {
                ms.show();
                hide();
            }
            else {
                QMessageBox msg;
                if(response.status_code==451)
                    msg.setText("Username already exists!");
                if(response.status_code==416)
                    msg.setText("Password is not strong enough");
                if(response.status_code==400)
                    msg.setText("There was an error in the transmitted information");
                msg.exec();

            }

        }


    }
}


void Form::on_back_clicked()
{
    mode=!mode;
    if(mode)
        ui->back->setText("If you don't have an account, sign up");
    else ui->back->setText("If you already have an account, log in");
    update();
}

