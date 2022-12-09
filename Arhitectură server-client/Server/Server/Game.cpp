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
void Game::sentANumericalQuestionRoute(std::vector<crow::json::wvalue> numericalQuest_json)
{
	CROW_ROUTE(app, "/numericalQuestion")([&numericalQuest_json]() {
		int index = Intrebare::GetRandomNumber(0, numericalQuest_json.size());
		return numericalQuest_json[index];
		});
}