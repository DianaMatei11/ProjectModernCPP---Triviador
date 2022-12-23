#include "Game.h"


Game::Game(Storage& storage, crow::SimpleApp& app) :
	storage{ storage }, app { app }
{}

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


void Game::sentANumericalQuestionRoute()
{
	int index = Intrebare::GetRandomNumber(0, numericalQuest_json.size());
	CROW_ROUTE(app, "/numericalQuestion")([&numericalQuest_json = numericalQuest_json, &index]() {
		return numericalQuest_json[index];
		});

}

void Game::sentAGrillQuestionRoute()
{
	CROW_ROUTE(app, "/Quiz")([&quizzes_json = quizzes_json]() {
		int index = Intrebare::GetRandomNumber(0, quizzes_json.size());
		return quizzes_json[index];
		});
}

int Game::verifyCorrectAnswer(int id, const std::vector<int> &answers)
{
	CROW_ROUTE(app, "/numericalQuestion/answer")([&numericalAnswers_json = numericalAnswers_json,id]() {
		return  numericalAnswers_json[id];
		});
	return 0;
}

int Game::verifyCorrectGrillAnswer(int id, const std::vector<int> &answers)
{
	CROW_ROUTE(app, "/Quiz/answer")([&quizzes_json = quizzes_json, id]() {
		return  quizzes_json[id];
		});
	return 0;
}

void Game::addPlayerByUsername()
{
	auto& usernameJson = CROW_ROUTE(app, "/GamePlayerUsername")
		.methods(crow::HTTPMethod::PUT);

	std::optional<User> user;
	usernameJson(GetUserbyUserName(storage, user));
	if (user.has_value())
	{
		players.emplace_back(std::move(std::make_shared<User>(std::move(user.value()))));
		assignAColor();
	}
}

void Game::assignAColor()
{
	CROW_ROUTE(app, "/assignAColor")([&players = players]() {
		switch (players.size() - 1)
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

