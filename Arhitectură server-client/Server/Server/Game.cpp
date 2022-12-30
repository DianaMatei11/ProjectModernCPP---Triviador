#include "Game.h"


Game::Game(Storage& storage, crow::SimpleApp& app) :
	storage{ storage }, app{ app }
{}

int Game::sentANumericalQuestionRoute()
{
	int index = Intrebare::GetRandomNumber(0, storage.count<IntrebareNumerica>());
	auto quest = storage.get<IntrebareNumerica>(index);
	CROW_ROUTE(app, "/numericalQuestion")([&quest]() {
		return crow::json::wvalue{
			{"Id", quest.GetId()},
			{"Question", quest.GetEnunt()}
			};
		});
	return index;
}

int Game::sentAGrillQuestionRoute()
{
	int index = Intrebare::GetRandomNumber(0, storage.count<IntrebariGrila>());
	auto quest = storage.get<IntrebariGrila>(index);
	CROW_ROUTE(app, "/Quiz")([&quest]() {
		return crow::json::wvalue{
			{"Id", quest.GetId()},
			{"Enunt", quest.GetEnunt()},
			{"Optiune0", quest.GetOption0()},
			{"Optiune1", quest.GetOption1()},
			{"Optiune2", quest.GetOption2()},
			{"Optiune3", quest.GetOption3()},
			};
		});
	return index;
}

int Game::sendCorrectAnswerNQ(int answer)
{
	CROW_ROUTE(app, "/numericalQuestion/answer")([answer]() {
		return  crow::json::wvalue{
			{"CorrectAnswer", answer} 
		};
		});
	return 0;
}

int Game::sendCorrectGrillAnswer(int answer)
{
	CROW_ROUTE(app, "/Quiz/answer")([&answer]() {
		return  crow::json::wvalue{
			{"CorrectAnswer", answer}
			};
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

std::array<std::string, 4> Game::launchNumericalQuestionAndReturnRanking()
{
	int idQuest = sentANumericalQuestionRoute();

	auto comp = ([](std::tuple<std::string, int, float> A, std::tuple<std::string, int, float> B)
		{
			return std::get<1>(A) == std::get<1>(B) ? std::get<2>(A) < std::get<2>(B) : std::get<1>(A) < std::get<1>(B);
		});

	std::priority_queue < std::tuple<std::string, int, float>, std::vector<std::tuple<std::string, int, float>>, decltype(comp)> pq(comp);

	int answer = storage.get<IntrebareNumerica>(idQuest).GetRaspuns();
	while (pq.size() != players.size())
	{
		CROW_ROUTE(app, "/numericalQuestion/usersAnswers")
			.methods(crow::HTTPMethod::PUT)
			([&players = players, answer, idQuest, &pq](const crow::request& req) {
			auto bodyArgs = parseUrlArgs(req.body);
			auto end = bodyArgs.end();

			for (auto& user_ptr : players)
			{
				if (bodyArgs.find(user_ptr->getUserName()) == end || bodyArgs.find(user_ptr->getUserName() + "Time") == end)
				{
					continue;
				}
				pq.push(std::make_tuple(user_ptr->getUserName(), std::abs(std::stoi(bodyArgs[user_ptr->getUserName()]) - answer), std::stof(bodyArgs[user_ptr->getUserName() + "Time"])));
			}
			return 200;
				});
	}

	std::array<std::string, 4> ranking;
	int index = 0;
	while (!pq.empty())
	{
		ranking[index] = std::get<0>(pq.top());
		pq.pop();
		index++;
	}

	return ranking;
}

void Game::getTheLeaderBoard(crow::SimpleApp& app)
{
	std::array<std::string, 4> ranking = launchNumericalQuestionAndReturnRanking();
	CROW_ROUTE(app, "/leaderBoard")([&ranking]() {
		std::vector<crow::json::wvalue> leaderBoard;
		int position = 1;
		for (const auto& playerName : ranking) {
			leaderBoard.push_back(crow::json::wvalue{
				{ "Pos", position },
				{ "name", playerName },
				});
			position++;
		}

		return crow::json::wvalue{ leaderBoard };
		});
}

void Game::GetPlayersBases()
{
	std::vector< std::pair<std::string, int>> baze;
	std::vector<std::shared_ptr<Region>> regiuniBaze;
	CROW_ROUTE(app, "/getPlayersBases")
		.methods(crow::HTTPMethod::PUT)
		([&players = players, &map = map, &baze, &regiuniBaze](const crow::request& req) {
		auto bodyArgs = parseUrlArgs(req.body);
		auto end = bodyArgs.end();

		int nrPlayers = 0;
		for (auto& player : players)
		{
			if (bodyArgs.find(player->getUserName()) != end)
			{
				auto indexRegion = bodyArgs.find("index");
				int index = std::stoi(indexRegion->second);
				std::shared_ptr<Region> region = map.GetRegion(index - 1);
				std::vector<std::shared_ptr<Region>>& regions = map.GetUnusedRegions();
				auto it = std::find(regions.begin(), regions.end(), region);
				if (it != regions.end())
				{
					std::pair<std::string, int> baza;
					baza.first = player->getUserName();
					baza.second = index;
					baze.push_back(baza);
					regiuniBaze.push_back(map.PickRegion(index - 1));
					nrPlayers++;
				}
			}
		}



		if (nrPlayers == players.size())
		{
			for (auto& baza : baze)
			{
				const auto& [player, index] = baza;
				std::shared_ptr<Region> region = map.GetRegion(index - 1);
				region->SetBase();
				//region->SetOwner(player);
			}
		}
		else return crow::response(400);

		return crow::response(200);
			});
}
