#include "mainscreen.h"
#include "ui_mainscreen.h"

MainScreen::MainScreen(QWidget* parent) :
	QMainWindow(parent),
	ui(new Ui::MainScreen)
{
	ui->setupUi(this);
	QPixmap bkgnd(":/images/images/AccountScreen.jpg");
	bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
	QPalette palette;
	palette.setBrush(QPalette::Window, bkgnd);
	this->setPalette(palette);


	//this->setStyleSheet("background-image:url(:/images/images/AccountScreen.jpg; background-repeat:no-repeat;");
	QPixmap pixmap(":/images/images/logoFinal.png");
	pixmap = pixmap.scaled(this->size(), Qt::IgnoreAspectRatio);
	ui->logo->setPixmap(pixmap);
	ui->logo2->setPixmap(pixmap);
	ui->logo3->setPixmap(pixmap);

	QPixmap pixmap2(":/images/images/back_icon.png");
	pixmap2 = pixmap2.scaled(this->size(), Qt::IgnoreAspectRatio);
	QIcon aux(pixmap2);
	ui->back->setIcon(aux);
	ui->back_2->setIcon(aux);
	ui->stats->setAlignment(Qt::AlignCenter);
	ui->account->setCurrentIndex(0);
}

void MainScreen::setUsername(std::string str)
{
	this->userName = str;
}

void MainScreen::addPlayersOnTheScreen()
{
	ui->listOfPlayers->clear();
	cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:14040/PlayersInGame" });
	auto users = crow::json::load(response.text);
	for (const auto& user : users)
	{
		ui->listOfPlayers->append(QString::fromLocal8Bit(static_cast<std::string> (user["username"])));
	}

}

void MainScreen::findOutStartGame()
{
	bool launchGame = false;
	while (start.size() % 2 == 1 && !launchGame)
	{
		addPlayersOnTheScreen();
		cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:14040/launchGame" });

		auto aux = crow::json::load(response.text);
		if (aux["start"] == "stay")
		{
			QEventLoop loop;
			QTimer t;
			t.connect(&t, &QTimer::timeout, &loop, &QEventLoop::quit);
			t.start(1000);
			loop.exec();
		}
		else
		{
			launchGame = true;
			harta.show();
			harta.setUsername(userName);
			harta.setColor(userColor);
			harta.coord();
			hide();
		}
	}
}

MainScreen::~MainScreen()
{
	delete ui;
}



void MainScreen::on_configuration_clicked()
{
	ui->account->setCurrentIndex(2);
	
	{
		sendUsername:
		auto response = cpr::Put(
			cpr::Url{ "http://localhost:14040/GamePlayerUsername" },
			cpr::Payload{
				{ "Name", (this->userName)}
			}
		);

		if (response.status_code == 400)
		{
			goto sendUsername;
		}
	}

	{
		cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:14040/assignAColor" });
		auto colorId = crow::json::load(response.text);
		switch (colorId["color"].i())
		{
		case 0:
			this->userColor = Qt::red;
			break;
		case 1:
			this->userColor = Qt::yellow;
			break;
		case 2:
			this->userColor = Qt::blue;
			break;
		case 3:
			this->userColor = Qt::green;
			break;
		}
	}

	addPlayersOnTheScreen();
}


void MainScreen::on_statistics_clicked()
{
	ui->account->setCurrentIndex(1);
	auto r = cpr::Put(
		cpr::Url{ "http://localhost:14040/Statistics/username" },
		cpr::Payload{		
			{ "Name", (userName)}
		}
	); 

	if (r.status_code == 200)
	{
		cpr::Response response = cpr::Get(cpr::Url{ "http://localhost:14040/Statistics" });
		auto history = crow::json::load(response.text);

		// auto t = performance["meciuri_jucate"];
		QString p1 = QStringLiteral("Number of games played: %1\n").arg(history["meciuriJucate"].i());
		QString p2 = QStringLiteral("Number of questions answered: %1\n").arg(history["raspunsuriTotale"].i());
		QString p3 = QStringLiteral("Number of correct answerd: %1\n").arg(history["raspunsuri corecte"].i());
		QString p4 = QStringLiteral("Maximum score: %1\n").arg(history["scorMaxim"].i());
		QString p5 = QStringLiteral("Minimum score: %1\n").arg(history["scorMinim"].i());
		ui->stats->setText(p1 + p2 + p3 + p4 + p5);
	}
	else
	{
		ui->stats->setText("\n\nThere are no statistics available!");
		ui->stats->setAlignment(Qt::AlignCenter);
	}
}


void MainScreen::on_back_clicked()
{
	ui->account->setCurrentIndex(0);
}


void MainScreen::on_logOut_clicked()
{
	// hide();
	 //aux.show();
}


void MainScreen::on_back_2_clicked()
{
	ui->account->setCurrentIndex(0);
}

void MainScreen::on_ready_clicked()
{
	start += '1';

	auto response = cpr::Put(
		cpr::Url{ "http://localhost:14040/startGame" },
		cpr::Payload{
			{ "username", (this->userName)},
			{ "ready", (start)}
		}
	);

	findOutStartGame();
}