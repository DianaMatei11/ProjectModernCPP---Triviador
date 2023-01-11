#pragma once
#include <iostream>
#include <vector>
#include "UserRoutes.h"
#include "Map.h"
#include <crow.h>
#include <queue>

class Game {

private:
	std::vector<std::shared_ptr<User>> players;
	crow::SimpleApp& app;
	Storage& storage;
	Map map;

	enum colors {
		red = 0,
		yellow = 1,
		blue = 2,
		green = 3
	};
	
	int sentANumericalQuestionRoute();
	int sentAGrillQuestionRoute();

	int sendCorrectAnswerNQ(int answer);
	int sendCorrectGrillAnswer(int answer);
	
	void addPlayerByUsername();
	void assignAColor();
	void sendPlayersUsername();
	void arePlayersReady();

public:
	Game(Storage& storage, crow::SimpleApp& app);
	
	std::array<std::string, 4> launchNumericalQuestionAndReturnRanking();
	void getTheLeaderBoard(crow::SimpleApp& app);
	void GetPlayersBases();
	void gameManager();

	void Duel(std::shared_ptr<User>& attacker, std::shared_ptr<User>& defender, std::shared_ptr<Region>& region);

	void clickedCoordinates();
	
};