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
	CROW_ROUTE(app, "/GamePlayerUsername")
		.methods(crow::HTTPMethod::PUT)([&db = storage, &players = players](const crow::request& req) {
		std::string username;

		auto bodyArgs = parseUrlArgs(req.body);
		auto end = bodyArgs.end();
		auto nameIter = bodyArgs.find("Name");
		if (nameIter != end)
		{
			username = nameIter->second;
			auto user = existUserName(username, db);
			players.emplace_back(std::move(std::make_shared<User>(std::move(user.value()))));
			return crow::response(200);
		}
		return crow::response(400);
			});


}

void Game::sendPlayersUsername()
{
	CROW_ROUTE(app, "/PlayersInGame")([&players = players]() {
		
		std::vector<crow::json::wvalue> playersJson;
		for (const auto& player : players)
		{
			playersJson.push_back(crow::json::wvalue{
				{"username", player->getUserName()}
			});
		}
		return crow::json::wvalue{ playersJson };
		});
}

void Game::assignAColor()
{
	CROW_ROUTE(app, "/assignAColor")([&players = players]() {
		colors color;
		switch (players.size() - 1)
		{
		case 0:
			color = red;
			break;
		case 1:
			color = yellow;
			break;
		case 2:
			color = green;
			break;
		case 3:
			color = blue;
			break;
		}

		return crow::json::wvalue{
				{"color", (color)}
		};

		});

}

void Game::arePlayersReady()
{
	static bool startGame = false;

	CROW_ROUTE(app, "/startGame")
		.methods(crow::HTTPMethod::PUT)([&players = players, &startGame = startGame](const crow::request& req) {
		static std::unordered_map<std::string, bool> playersReady{};
		auto bodyArgs = parseUrlArgs(req.body);
		auto end = bodyArgs.end();
		auto usernameIter = bodyArgs.find("username");
		auto statusIter = bodyArgs.find("ready");
		if (usernameIter != end && statusIter != end)
		{
			if (statusIter->second.size() % 2 == 1)
			{
				playersReady[usernameIter->second] = true;
			}
			else
			{
				playersReady[usernameIter->second] = false;
			}

			if (playersReady.size() >= 2 && playersReady.size() == players.size())
			{
				for (const auto& [username, status] : playersReady)
				{
					if (status == false)
					{
						return 200;
					}
				}
			}
			else
			{
				return 200;
			}

			startGame = true;

			return 200;
		}
		return 400;
			});

	CROW_ROUTE(app, "/launchGame")([&startGame = startGame, &map = map, &players = players]() {
		if (startGame)
		{
			map.buildMap(players.size());
			return crow::json::wvalue{
				{"start", "launch"}
			};
		}

		return crow::json::wvalue{
			{"start", "stay"}
		};
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
		CROW_ROUTE(app, "/numericalQuestion/userAnswers")
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

	sendCorrectAnswerNQ(idQuest);

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
				{ "name", playerName }
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
				region->SetOwner(player);
			}
		}
		else return crow::response(400);

		return crow::response(200);
			});
}

void Game::Duel(std::shared_ptr<User>& attacker, std::shared_ptr<User>& defender, std::shared_ptr<Region>& region)
{
	std::vector<std::shared_ptr<User>> playersOfTheDuel;
	playersOfTheDuel.push_back(attacker);
	playersOfTheDuel.push_back(defender);

	int noLives;
	if ((*region).IsBase())
	{
		noLives = 3;
	}
	else noLives = 1;
	bool defenderLost = false;
	bool attackerLost = false;
	bool defendersAnswerIsRight = false;
	bool attackersAnswerIsRight = false;
	int counter = 0;
	while (!defenderLost && !attackerLost)
	{
		int idGridQuestion;
		idGridQuestion=sentAGrillQuestionRoute();
		sendCorrectGrillAnswer(idGridQuestion);

		int indexAnswerGQ = storage.get<IntrebariGrila>(idGridQuestion).GetIndex_Rasp_Corect();
		std::vector<std::pair<std::shared_ptr<User>, int>> answerOfPlayers;

		while (answerOfPlayers.size() != 2)
		{
			CROW_ROUTE(app, "/gridQuestion/usersAnswers")
				.methods(crow::HTTPMethod::PUT)
				([&playersOfTheDuel, indexAnswerGQ, idGridQuestion, &answerOfPlayers, &defender, &attacker](const crow::request& req) {
				auto bodyArgs = parseUrlArgs(req.body);
			auto end = bodyArgs.end();

			for (auto& user_ptr : playersOfTheDuel)
			{			
				if (bodyArgs.find(user_ptr->getUserName()) == end)
				{
					continue;
				}
				auto answerIter = bodyArgs.find("answer");
				if (answerIter != end)
				{
					int playerAnswer=std::stoi(answerIter->second);
					std::pair < std::shared_ptr<User>, int> pair;
					pair.first = user_ptr;
					pair.second = playerAnswer;
					answerOfPlayers.push_back(pair);
				}
			}
			return 200;
					});
		}

		for (const auto& p : answerOfPlayers)
		{
			if (p.second == indexAnswerGQ)
			{
				if (p.first->getUserName() == attacker->getUserName())
				{
					attackersAnswerIsRight = true;
				}
				else defendersAnswerIsRight = true;
			}
		}
		//de trimis si verificat raspunsurile

		if (!defendersAnswerIsRight && attackersAnswerIsRight)
			counter++;

		if (defendersAnswerIsRight && !attackersAnswerIsRight)
		{
			attackerLost = true;
			break;
		}

		if (!defendersAnswerIsRight && !attackersAnswerIsRight)
		{
			attackerLost = true;
			defenderLost = true;
			break;
		}

		if (counter == noLives)
		{
			defenderLost = true;
			break;
		}

		//if (defendersAnswerIsRight && attackersAnswerIsRight)
		//{
			defendersAnswerIsRight = false;
			attackersAnswerIsRight = false;
		//}

		int idNumericalQuestion=sentANumericalQuestionRoute();
		sendCorrectAnswerNQ(idNumericalQuestion);

		auto comp = ([](std::tuple<std::string, int, float> A, std::tuple<std::string, int, float> B)
			{
				return std::get<1>(A) == std::get<1>(B) ? std::get<2>(A) < std::get<2>(B) : std::get<1>(A) < std::get<1>(B);
			});

		std::priority_queue < std::tuple<std::string, int, float>, std::vector<std::tuple<std::string, int, float>>, decltype(comp)> pq(comp);

		int answer = storage.get<IntrebareNumerica>(idNumericalQuestion).GetRaspuns();
		while (pq.size() != 2)
		{
			CROW_ROUTE(app, "/numericalQuestion/usersAnswers")
				.methods(crow::HTTPMethod::PUT)
				([&playersOfTheDuel, answer, idNumericalQuestion, &pq,&defender,&attacker](const crow::request& req) {
				auto bodyArgs = parseUrlArgs(req.body);
			auto end = bodyArgs.end();

			for (auto& user_ptr : playersOfTheDuel)
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

		if (std::get<0>(pq.top()) == attacker->getUserName())
		{
			attackersAnswerIsRight = true;
			defendersAnswerIsRight = false;
		}
		else
		{
			attackersAnswerIsRight = false;
			defendersAnswerIsRight = true;
		}

		//de trimis si verificat raspunsurile


		if (!defendersAnswerIsRight && attackersAnswerIsRight)
			counter++;

		if (defendersAnswerIsRight && !attackersAnswerIsRight)
		{
			attackerLost = true;
			break;
		}

		if (!defendersAnswerIsRight && !attackersAnswerIsRight)
		{
			attackerLost = true;
			defenderLost = true;
			break;
		}

		if (counter == noLives)
		{
			defenderLost = true;
			break;
		}

		if (counter<noLives)
		{
			defendersAnswerIsRight = false;
			attackersAnswerIsRight = false;
		}
	}

	if (defenderLost && !attackerLost)
	{
		region->SetOwner(attacker->getUserName());
		//(*region).changeColour();
		//attacker.IncreaseScore();
	}

	if (!defenderLost && attackerLost)
	{
		int score = region->GetScores();
		region->SetScores(score + 100);
		//defender.IncreaseScore();
	}
}

void Game::clickedCoordinates()
{
	CROW_ROUTE(app, "/CoordClickHarta")
		.methods(crow::HTTPMethod::PUT)
		([&map = map, &players = players](const crow::request& req) {
		std::vector<std::shared_ptr<Region>> regions = map.GetRegions();
		auto bodyArgs = parseUrlArgs(req.body);
		auto end = bodyArgs.end();
		auto xIter = bodyArgs.find("x");
		auto yIter = bodyArgs.find("y");
		int x = std::stoi(xIter->second);
		int y = std::stoi(yIter->second);
		int id=-1;

		int noRegionsH;
		if (players.size() == 2 || players.size()==3)
		{
			noRegionsH = 3;
		}
		if (players.size() == 4)
		{
			noRegionsH = 4;
		}

		std::vector<std::shared_ptr<Region>> regions = map.GetRegions();
		float h = static_cast<float>(350/noRegionsH);

		for (auto& regiune : regions)
		{
			const auto& [xR, yR, hR, wR] = regiune->GetCoord();
			if (xR <= x && y <= yR+h && yR <= y)
			{
				id = regiune->GetID();
			}
		}

		if (id != -1) 
		{
			std::shared_ptr<Region> region = map.GetRegion(id);
			crow::json::wvalue dateRegiune;
			if (region->HasOwner()) {
				dateRegiune = crow::json::wvalue{
					{ "index", region->GetID()},
					//{ "color", region->GetCoord() }
					{ "score", region->GetScores()}
				};
				return dateRegiune;
			}
			else {
				dateRegiune = crow::json::wvalue{
					{"response", "invalid"}
				};
				return dateRegiune;
				//return crow::response(400);
			}
		}
		else
		{
			crow::json::wvalue answer = {
				{"response", "no region"}
			};
			return answer;
		}
	});
}

void Game::gameManager()
{
	addPlayerByUsername();
	assignAColor();
	sendPlayersUsername();
	arePlayersReady();
	map.RouteForCoordinates(app);
}

