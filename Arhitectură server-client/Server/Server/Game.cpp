#include "Game.h"
#include "Storage.h"
#include <crow.h>

void Game::addNewPlayer(int id)
{
}

void Game::initNumericalQuest_json()
{
	for (const auto& quest : storage.iterate<IntrebareNumerica>())
	{
		numericalQuest_json.push_back(crow::json::wvalue{
			{"Id", quest.GetId()},
			{"Question", quest.GetEnunt()}
			});
	}
}

void Game::initQuizzes_json()
{
	for (const auto& quest : storage.iterate<IntrebariGrila>())
	{

		quizzes_json.push_back(crow::json::wvalue{
			{"Id", quest.GetId()},
			{"Enunt", quest.GetEnunt()},
			{"Optiune0", quest.GetOption0()},
			{"Optiune1", quest.GetOption1()},
			{"Optiune2", quest.GetOption2()},
			{"Optiune3", quest.GetOption3()},
			});
	}
}

void Game::initNumericalAnswers_json()
{
	for (const auto& quest : storage.iterate<IntrebareNumerica>())
	{
		numericalAnswers_json.push_back(crow::json::wvalue{
			{"CorrectAnswer", quest.GetRaspuns()}
			});
	}
}

void Game::initUsers_json()
{
	for (const auto& user : storage.iterate<User>())
	{
		users_json.push_back(crow::json::wvalue{
			{"Id",user.GetId()},
			{"Name",user.getUserName()},
			{"Pass", user.getPassword()}
			});
	}
}

void Game::addNewPlayer(std::string name, std::string password)
{
	User* newUser = new User(name, password);
	players.push_back(*newUser);
}

void Game::sentANumericalQuestionRoute(std::vector<crow::json::wvalue> numericalQuest_json)
{
	CROW_ROUTE(app, "/numericalQuestion")([&numericalQuest_json]() {
		int index = Intrebare::GetRandomNumber(0, numericalQuest_json.size());
		return numericalQuest_json[index];
		});
}

void Game::sentAGrillQuestionRoute(std::vector<crow::json::wvalue> quizzes_json)
{
	CROW_ROUTE(app, "/numericalQuestion")([&quizzes_json]() {
		int index = Intrebare::GetRandomNumber(0, quizzes_json.size());
		return quizzes_json[index];
		});
}

int Game::verifyCorrectAnswer(std::vector<crow::json::wvalue> numericalAnswers_json, int id, std::vector<int> answers)
{
	CROW_ROUTE(app, "/numericalQuestion")([&numericalAnswers_json,id]() {
		return  numericalAnswers_json[id];
		});
	return 0;
}

void Game::assignAColor(User user, std::vector<User> Players)
{
	int index = 0;
	CROW_ROUTE(app, "/assignAColor")([&Players,&user,&index]() {
		for (int i = 0; i < Players.size(); i++)
			if (Players[i] == user)
				index = i;
		switch (index)
		{
		case 0:
			return red;
			break;
		case 1:
			return yellow;
			break;
		case 2:
			return blue;
			break;
		case 3:
			return green;
			break;
		}
		});
}

