#include "Game.h"


Game::Game(Storage& storage, crow::SimpleApp& app) :
	storage{ storage }, app{ app }
{}

int Game::sentANumericalQuestionRoute()
{


	return 0;
}

int Game::sentAGrillQuestionRoute()
{
	int index = Intrebare::GetRandomNumber(0, storage.count<IntrebariGrila>());
	auto quest = storage.get<IntrebariGrila>(index);
	CROW_ROUTE (app, "/Quiz")([&quest]() {
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

std::vector<crow::json::wvalue> Game::sentUserRanking(std::string userName)
{
	std::vector<crow::json::wvalue> aux;
	int index = 0;
	
	for (auto it = usersRanking.begin(); it != usersRanking.end(); it++)
	{
		aux[index]["userName"] = it->first;
		aux[index]["points"] = it->second.first;
		aux[index]["colors"] = it->second.second;
		index++;
	}
	CROW_ROUTE(app, "/UsersRanking")([aux]() {
		return aux;
		});
	
	return aux;
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

	CROW_ROUTE(app, "/launchGame")([&usersRanking = usersRanking, &startGame = startGame, &map = map, &players = players]() {
		if (startGame)
		{
			for (int i = 0; i < players.size(); i++)
			{
				std::string playerName = players[i]->getUserName();
				usersRanking[playerName] = { 0, colors(i) };
			}
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

void Game::getRegionStatus()
{
	CROW_ROUTE(app, "/getRegionsStatus") ([&map = map, &usersRanking = usersRanking]() {

		std::vector<crow::json::wvalue> regionsDetils;
		for (const auto& region : map.GetRegions())
		{
			colors regionColor;
			if (region->HasOwner())
			{
				regionColor = usersRanking[region->GetOwner()].second;
			}
			else
			{
				regionColor = none;
			}

			regionsDetils.push_back(
				crow::json::wvalue{
					{"color", regionColor},
					{"isBase", region->IsBase()}
				});
		}

		return crow::json::wvalue{ regionsDetils };
		});
}

void Game::launchNumericalQuestionAndReturnRanking()
{
	static int index = Intrebare::GetRandomNumber(0, storage.count<IntrebareNumerica>());
	static auto quest = storage.get<IntrebareNumerica>(index).GetEnunt();
	static bool newQuest = false;
	CROW_ROUTE(app, "/numericalQuestion")([&newQuest = newQuest, &index = index, &quest = quest, this]() {
		if (newQuest)
		{
			index = Intrebare::GetRandomNumber(0, storage.count<IntrebareNumerica>());
			quest = storage.get<IntrebareNumerica>(index).GetEnunt();
		}

		return crow::json::wvalue{
			{"Question", quest}
		};
		});

	auto comp = ([](std::tuple<std::string, int, float> A, std::tuple<std::string, int, float> B)
		{
			return std::get<1>(A) == std::get<1>(B) ? std::get<2>(A) < std::get<2>(B) : std::get<1>(A) < std::get<1>(B);
		});

	static std::priority_queue < std::tuple<std::string, int, float>, std::vector<std::tuple<std::string, int, float>>, decltype(comp)> pq(comp);

	CROW_ROUTE(app, "/numericalQuestion/userAnswers")
		.methods(crow::HTTPMethod::PUT)
		([&players = players, &index = index, &pq = pq, &storage = storage](const crow::request& req) {
		int answer = storage.get<IntrebareNumerica>(index).GetRaspuns();
		
		auto bodyArgs = parseUrlArgs(req.body);
		auto end = bodyArgs.end();

		for (auto& user_ptr : players)
		{
			if (bodyArgs.find(user_ptr->getUserName()) == end || bodyArgs.find(user_ptr->getUserName() + "Time") == end)
			{
				continue;
			}
			pq.push({ user_ptr->getUserName(), std::abs(std::stoi(bodyArgs[user_ptr->getUserName()]) - answer), std::stof(bodyArgs[user_ptr->getUserName() + "Time"])});
		}
		return 200;
			});


	CROW_ROUTE(app, "/getOrder")([&newQuest = newQuest, &pq = pq, &players = players]() {
		if (pq.size() != players.size())
		{
			return crow::json::wvalue{
				{ "wait", 0 }
			};
		}
		newQuest = true;
		std::vector<crow::json::wvalue> leaderBoard;
		while (!pq.empty()) {
			const auto& [playerName, diffrenceOfAnswer, time] = pq.top();
			leaderBoard.push_back(crow::json::wvalue{
				{ "player", playerName }
				});
			pq.pop();
		}

		return crow::json::wvalue{ leaderBoard };
		});
}

void Game::getTheLeaderBoard()
{


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
		idGridQuestion = sentAGrillQuestionRoute();
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
						int playerAnswer = std::stoi(answerIter->second);
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

		int idNumericalQuestion = sentANumericalQuestionRoute();
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
				([&playersOfTheDuel, answer, idNumericalQuestion, &pq, &defender, &attacker](const crow::request& req) {
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

		if (counter < noLives)
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
		auto nameIter = bodyArgs.find("userName");

		if (xIter == end || yIter == end)
		{
			return 400;
		}

		int x = std::stoi(xIter->second);
		int y = std::stoi(yIter->second);
		int id = -1;

		for (auto& regiune : regions)
		{
			const auto& [xR, yR, hR, wR] = regiune->GetCoord();
			if (xR <= x && x <= xR + wR && y <= yR + hR && yR <= y)
			{
				id = regiune->GetID();
				if (!regiune->HasOwner())
				{
					map.PickRegion(id);
					regiune->SetOwner(nameIter->second);
					if (map.GetUnusedRegions().size() <= map.GetUnusedRegions().size() - players.size())
					{
						regiune->SetBase();
					}
				}
				break;
			}
		}

		//if (id != -1) 
		//{
		//	std::shared_ptr<Region> region = map.GetRegion(id);
		//	crow::json::wvalue dateRegiune;
		//	if (region->HasOwner()) {
		//		dateRegiune = crow::json::wvalue{
		//			{ "index", region->GetID()},
		//			//{ "color", region->GetCoord() }
		//			{ "score", region->GetScores()}
		//		};
		//		return dateRegiune;
		//	}
		//	else {
		//		dateRegiune = crow::json::wvalue{
		//			{"response", "invalid"}
		//		};
		//		return dateRegiune;
		//		//return crow::response(400);
		//	}
		//}
		//else
		//{
		//	crow::json::wvalue answer = {
		//		{"response", "no region"}
		//	};
		//	return answer;
		//}
			});
}

void Game::gameManager()
{
	addPlayerByUsername();
	assignAColor();
	sendPlayersUsername();
	arePlayersReady();
	map.RouteForCoordinates(app);
	launchNumericalQuestionAndReturnRanking();
	getRegionStatus();
}

