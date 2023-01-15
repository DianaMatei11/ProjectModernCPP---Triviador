#include "harta.h"
#include "ui_harta.h"
#include<queue>>
#include<QLabel>
#include <QMessageBox>
//#include <QApplication>
Harta::Harta(QWidget* parent)
	: QMainWindow(parent),
	ui(new Ui::harta)
{

	ui->setupUi(this);
	QPixmap bkgnd(":/images/images/background.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);
	//SetActiveWindow(this);
	//ui->game->insertWidget(1, &intrebareNumerica);
	//ui->game->insertWidget(2, &intrebareGrila);
	//ui->game->setCurrentIndex(0);
	//coord();
	/*QTimer::singleShot(4000, this, [this]() {
		ui->game->setCurrentIndex(1);
		});*/
}

void Harta::setUsername(const std::string& str)
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

void Harta::mousePressEvent(QMouseEvent* ev)
{
	if (ev->button() == Qt::LeftButton)
	{
		auto response = cpr::Put(
			cpr::Url{ "http://localhost:14040/CoordClickHarta" },
			cpr::Payload{

				{"username", userName},
				{"x", std::to_string(ev->x())},
				{"y", std::to_string(ev->y())}

			});
		if (response.status_code == 400)
		{
			ui->instructiuni->setText("Regiune Invalida");
		}
		else
		{
			ui->instructiuni->setText("Regiune valida");
			QWidget::setEnabled(false);
		}
	}
}

void Harta::coord()
{
	float x, y, width, height;
	cpr::Response response = cpr::Get(
		cpr::Url{ "http://localhost:14040/coordinates" }
	);
	auto aux = crow::json::load(response.text);
	for (const auto& a : aux)
	{
		x = a["x"].d();
		y = a["y"].d();
		width = a["width"].d();
		height = a["height"].d();
		patrat.push_back(QRect(x, y, width, height));
	}

}


void Harta::gameManager()
{
	intrebareNumerica.setUsername(userName);
	//ui->game->setCurrentWidget(&intrebareNumerica);
	intrebareNumerica.show();
	hide();
	intrebareNumerica.AfisareIntrebare();
	intrebareNumerica.hide();
	show();
	getOrder(Etapa::AlegereBaza);
	QEventLoop loop;
	QTimer t;
	t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
	t.start(3000);
	loop.exec();

	while (true)
	{
		intrebareNumerica.show();
		hide();
		intrebareNumerica.AfisareIntrebare();
		intrebareNumerica.hide();
		show();
		getOrder(Etapa::Cucerire);
		QEventLoop loop;
		t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
		t.start(3000);
		loop.exec();
		cpr::Response response = cpr::Get(
			cpr::Url{ "http://localhost:14040/MapIsFull" });
		auto aux = crow::json::load(response.text);
		if (aux["map"] == "full")
		{
			break;
		}
	}
	//ui->game->setCurrentWidget(ui->map);

	//se dicteaza principalele etape ale jocului prin apelarea repetata a getOrder cu parametrii corespunzatori - alegerea bazei, cucerirea (pana nu mai raman regiuni disponibile,
	//duelul - pentru numarul de runde prestabilit, inainte de cucerire, mai trebuie lansata o intrebare numerica
}

void Harta::getOrder(Etapa etapa) //se poate folosi un parametru 0-pentru alegerea bazei, 1-cucerire, 2-duel
{
	//se obtine ordinea in care jucatorii isi vor efectua actiunile. Se afiseaza pe ecran urmatoarea intructiune. Daca userul care este la rand corespunde cu userul curent,
	// i se permite sa isi aleaga o regiune
	//QApplication::setOverrideCursor(Qt::BlankCursor);
	QWidget::setEnabled(false);

	cpr::Response response = cpr::Get(
		cpr::Url{ "http://localhost:14040/getOrder" });
	auto order = crow::json::load(response.text);

	if (order.has("wait"))
	{
		QEventLoop loop;
		t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
		t.start(100);
		loop.exec();
		response = cpr::Get(
			cpr::Url{ "http://localhost:14040/getOrder" });
		order = crow::json::load(response.text);
	}
	nrPlayers = order.size();

	int position = 0;
	for (const auto& pers : order)
	{
		switch (etapa)
		{
		case Etapa::AlegereBaza:
		{
			QString aux = QStringLiteral("%1 este la rand! Alege baza!\nAi 8 secunde").arg(QString::fromLocal8Bit(static_cast<std::string>(pers["player"].s())));
			ui->instructiuni->setText(aux);
			if (std::string(pers["player"].s()) == userName)
			{
				QWidget::setEnabled(true);
				QEventLoop loop;
				t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
				t.start(8000);
				loop.exec();

			}
			else
			{
				QEventLoop loop;
				t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
				t.start(8000);
				loop.exec();
			}
			getScore();
			repaint();
			update();
			break;
		}
		case Etapa::Cucerire:
		{
			int nr;
			for (int regionsChosed = position; regionsChosed < order.size() - 1; regionsChosed++)
			{
				nr = order.size() - regionsChosed - 1;
				QString aux = QStringLiteral("%1 este la rand! Alege %2 regiuni\nAi 8 secunde/regiune").arg(QString::fromLocal8Bit(static_cast<std::string>(pers["player"].s()))).arg(nr);
				ui->instructiuni->setText(aux);
				if (std::string(pers["player"].s()) == userName)
				{
					QWidget::setEnabled(true);

					QEventLoop loop;
					t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
					t.start(8000);
					loop.exec();

				}
				else
				{
					QEventLoop loop;
					QTimer t;
					t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
					t.start(8000);
					loop.exec();
				}
				getScore();
				repaint();
				update();
			}
			break;
		}
		case Etapa::Razboi:
		{
			QString aux = QStringLiteral("%1 este la rand! Ataca o regiune!").arg(QString::fromLocal8Bit(static_cast<std::string>(pers["player"].s())));
			ui->instructiuni->setText(aux);
			if (std::string(pers["player"].s()) == userName)
			{
				QWidget::setEnabled(true);
				//actiunea jucatorului - duel
				QWidget::setEnabled(false); //dupa ce jucatorul isi termina actiunea

			}
			update();
			break;
		}
		}
		position++;
	}
}

void Harta::getScore()
{

	std::queue<QLabel*> labels;
	cpr::Response response = cpr::Get(
		cpr::Url{ "http://localhost:14040/UsersRanking" }
	);
	auto aux = crow::json::load(response.text);
	if (nrPlayers == 2)
	{
		labels.push(ui->player2);
		labels.push(ui->player3);

	}
	else if (nrPlayers == 3)
	{
		labels.push(ui->player1);
		labels.push(ui->player2);
		labels.push(ui->player3);
	}
	else
	{
		labels.push(ui->player1);
		labels.push(ui->player2);
		labels.push(ui->player3);
		labels.push(ui->player4);
	}

	for (const auto& player : aux)
	{
		auto& curent_label = labels.front();

		switch (player["color"].i())
		{
		case 0:
			curent_label->setStyleSheet("QLabel { background-color : red }");
			break;
		case 1:
			curent_label->setStyleSheet("QLabel { background-color : yellow }");
			break;
		case 2:
			curent_label->setStyleSheet("QLabel { background-color : blue }");
			break;
		case 3:
			curent_label->setStyleSheet("QLabel { background-color : green }");
			break;
		}
		curent_label->setText(QString::fromLocal8Bit(static_cast<std::string>(player["name"])) + static_cast<QString>('\n') + QString::fromLocal8Bit(static_cast<std::string>(player["score"])));
		
		labels.pop();
	}
}

void Harta::paintEvent(QPaintEvent*)
{
	QPainter p(this);
	QPen pen(Qt::black, 2);
	p.setPen(pen);

	//se apeleaza o ruta care returneaza culoarea regiunilor si daca sunt sau nu baze
	cpr::Response response = cpr::Get(
		cpr::Url{ "http://localhost:14040/getRegionsStatus" });
	if (response.status_code == 200 || response.status_code == 201)
	{
		auto regions = crow::json::load(response.text);

		for (int i = 0; i < patrat.size(); i++)
		{
			QBrush b;
			switch (regions[i]["color"].i()) //setarea culorii in functie de informatiile date de ruta
			{
			case 0:
			{
				b.setColor(Qt::red);
				break;
			}
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

			b.setStyle(Qt::SolidPattern);
			p.setBrush(b);
			p.drawRect(patrat[i]);

			if (regions[i]["isBase"].b())
			{
				p.drawText(patrat[i], Qt::AlignCenter, "B");
			}

		}
	}
}

