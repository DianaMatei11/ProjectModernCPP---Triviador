#include "Game.h"
#include "Storage.h"
#include <crow.h>

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

void Game::getUsersAnswer()
{
	auto& req = CROW_ROUTE(app, "/numericalQuestion/GetUsersAnswer")
		.methods(crow::HTTPMethod::PUT);
	//Handler- functor
}

//void Game::Winers(std::string id)
//{
//}



int Game::sentANumericalQuestionRoute()
{
	int index = Intrebare::GetRandomNumber(0, numericalQuest_json.size());
	CROW_ROUTE(app, "/numericalQuestion")([this, index]() {
		return numericalQuest_json[index];
		});
	return index;
}

int Game::sentAGrillQuestionRoute()
{
	int index = Intrebare::GetRandomNumber(0, quizzes_json.size());
	CROW_ROUTE(app, "/Quiz")([this, index]() {
		return quizzes_json[index];
		});
	return index;
}

void Game::WinnersNumericalQuestion(std::string id) {
	CROW_ROUTE(app, "/numericalQuestion/winner")([id]() {
		return id;
		});
	
}

void Game::WinnersGrillQuestion(std::string id) {
	CROW_ROUTE(app, "/Quiz/winner")([id]() {
		return id;
		});

}
int Game::SentCorrectAnswer(int id, std::vector<int> answers)
{
	CROW_ROUTE(app, "/numericalQuestion/answer")([this, id]() {
		return  numericalAnswers_json[id];
		});
	return 0;
}

int Game::SentCorrectGrillAnswer(int id, std::vector<int> answers)
{
	CROW_ROUTE(app, "/Quiz/answer")([this, id]() {
		return  quizzes_json[id];
		});
	return 0;
}


