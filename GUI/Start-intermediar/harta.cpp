#include "harta.h"
#include "ui_harta.h"
#include<queue>>
#include<QLabel>
//#include <QApplication>
Harta::Harta(QWidget *parent)
    : QMainWindow(parent), 
    ui(new Ui::harta)
{

    ui->setupUi(this);
    ui->game->insertWidget(1,&intrebareNumerica);
    ui->game->insertWidget(2,&intrebareGrila);   
    ui->game->setCurrentIndex(0);
    /*QTimer::singleShot(4000, this, [this]() {
        ui->game->setCurrentIndex(1);
        });*/
    gameManager();
}

void Harta::setUsername(std::string str)
{
    userName = str;
}

void Harta::setColor(QColor color)
{
    userColor = color;
}

Harta::~Harta()
{
    delete ui;
}

void Harta::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton)
       {
            auto response = cpr::Put(
            cpr::Url{ "http://localhost:14040/CoordClickHarta" },
            cpr::Payload{
                
                {"x", "" + static_cast<int>(ev->position().x())},
                {"y", "" + static_cast<int>(ev->position().y())}
                
            });
    }
}

void Harta::coord()
{
    float x, y,  width,height;
    cpr::Response response = cpr::Get(
                    cpr::Url{ "http://localhost:14040/coordinates"}
                );
    auto aux = crow::json::load(response.text);
    for(const auto& a : aux)
    {
            x = a["x"].d();
            y = a["y"].d();
            width = a["width"].d();
            height = a["height"].d();
            patrat.push_back(QRect(x,y,width,height));
    }
    update();

}


void Harta::gameManager()
{
    QEventLoop loop;
    QTimer t;
    t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
    t.start(3000);
    loop.exec();
    ui->game->setCurrentWidget(&intrebareNumerica);   
    //se dicteaza principalele etape ale jocului prin apelarea repetata a getOrder cu parametrii corespunzatori - alegerea bazei, cucerirea (pana nu mai raman regiuni disponibile,
    //duelul - pentru numarul de runde prestabilit, inainte de cucerire, mai trebuie lansata o intrebare numerica
}
void Harta::getOrder(int i) //se poate folosi un parametru 0-pentru alegerea bazei, 1-cucerire, 2-duel
{
    //se obtine ordinea in care jucatorii isi vor efectua actiunile. Se afiseaza pe ecran urmatoarea intructiune. Daca userul care este la rand corespunde cu userul curent,
    // i se permite sa isi aleaga o regiune
    //QApplication::setOverrideCursor(Qt::BlankCursor);
    QWidget::setEnabled(false);
    cpr::Response response = cpr::Get(
        cpr::Url{ "http://localhost:14040/getOrder" });
    auto order = crow::json::load(response.text);
    for (int j = 0;j<order.size();j++) //pentru cucerire se recomanda o parcurgere indexata
    {
        switch (i)
        {
        case 0: //alegerea bazei
        {QString aux = QStringLiteral("%1 este la rand! Alege baza!").arg(QString::fromStdString(std::string(order[j]["player"].s())));
        ui->instructiuni->setText(aux);
        if (std::string(order[j].s()) == userName)
        {
            QWidget::setEnabled(true);
            //actiunea jucatorului - alegerea bazei
            QWidget::setEnabled(false); //dupa ce jucatorul isi termina actiunea

        }
        update();
        break; }
        case 1: //cucerire
        {
            int nr = order.size() - j;
            QString aux = QStringLiteral("%1 este la rand! Alege %2 regiuni").arg(QString::fromStdString(std::string(order[j]["player"].s())),nr);
            ui->instructiuni->setText(aux);
            if (std::string(order[j].s()) == userName)
            {
                QWidget::setEnabled(true);
                for (int index = 0; index < nr; index++)
                { //actiunea jucatorului - cucerire regiuni
                    update(); //poate fi parte din functia de alegere a regiunii
                }
                QWidget::setEnabled(false); //dupa ce jucatorul isi termina actiunea

            }
            
            break;
        }
        case 2: //duel
        {
            QString aux = QStringLiteral("%1 este la rand! Ataca o regiune!").arg(QString::fromStdString(std::string(order[j]["player"].s())));
            ui->instructiuni->setText(aux);
            if (std::string(order[j].s()) == userName)
            {
                QWidget::setEnabled(true);
                //actiunea jucatorului - duel
                QWidget::setEnabled(false); //dupa ce jucatorul isi termina actiunea

            }
            update();
            break;
        }
        }
        
    }
}
void Harta::getScore()
{
    std::queue<QLabel> labels;

    while(true)
    {
        cpr::Response response = cpr::Get(
                        cpr::Url{ "http://localhost:14040/getScore"}
                    );
        auto aux = crow::json::load(response.text);
        int numar_jucatori=aux.size();
        if(numar_jucatori==2)
        {
            ui->player1->hide();
            ui->player4->hide();
            //labels.push(ui->player2);
           // labels.push(ui->player3);

        }
        else if(numar_jucatori==3)
        {
            ui->player4->hide();
          //  labels.push(ui->player1);
          //  labels.push(ui->player2);
          //  labels.push(ui->player3);
        }
        else
        {
           // labels.push(ui->player1);
           // labels.push(ui->player2);
           // labels.push(ui->player3);
           // labels.push(ui->player4);
        }
        for(const auto& player:aux)
        {
            const auto & curent_label= labels.front();

         /*   switch (player["color"])
            {
            case 0:
                curent_label.setStyleSheet("QLabel { background-color : red }");

                break;
            case 1:
                curent_label.setStyleSheet("QLabel { background-color : yellow }");
                break;
            case 2:
                curent_label.setStyleSheet("QLabel { background-color : blue }");
                break;
            case 3:
                curent_label.setStyleSheet("QLabel { background-color : green }");
                break;
            }
            curent_label.setText(player["name"]+" - "+ player["score"]);*/

            labels.pop();

        }


    }
}

void Harta::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    int x, y, width, height;
    QPen pen;
    pen.setWidth(2);
    p.setPen(pen);
    //se apeleaza o ruta care returneaza culoarea regiunilor si daca sunt sau nu baze
    cpr::Response response = cpr::Get(
        cpr::Url{ "http://localhost:14040/getRegionsStatus" });
    auto regions = crow::json::load(response.text);
    
    for(int i=0;i<patrat.size();i++)
    { //se pun conditii in funtie de ownership si de calitatea posibila de baza
        QBrush b;
        switch (regions[i]["color"].i()) //setarea culorii in functie de informatiile date de ruta
        {
        case 0:
        { b.setColor(Qt::red);
        break; }
        case 1:
        {
            b.setColor(Qt::yellow);
            break;
        }
        case 2:
        {
            b.setColor(Qt::blue);
            break;
        }
        case 3:
        {
            b.setColor(Qt::green);
            break;
        }
        default: b.setColor(Qt::white);
        }
        p.setBrush(b);
        //verificare baza si setare pictograma corespunzatoare (base.png)       
        if (regions[i]["isBase"])
        {
            QLabel aux;
            QPixmap image(":/images/images/base.png");
            aux.setPixmap(image);
            aux.setGeometry(patrat[i]);
            aux.show();
        }
        p.drawRect(patrat[i]);
        

    }

}

