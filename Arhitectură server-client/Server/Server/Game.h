#pragma once
#include <iostream>
#include <vector>
#include "UserRoutes.h"
#include "Map.h"
#include <crow.h>
#include <queue>
#include <unordered_map>
#include <windows.h>

class Game {

private:
	std::vector<std::shared_ptr<User>> players;
	crow::SimpleApp& app;
	Storage& storage;
	Map map;

	enum colors {
		none = -1,
		red = 0,
		yellow = 1,
		blue = 2,
		green = 3
	};

	std::unordered_map < std::string, std::pair<int, colors>> usersRanking;
	
	int sentANumericalQuestionRoute();
	int sentAGrillQuestionRoute();

	int sendCorrectAnswerNQ(int answer);
	int sendCorrectGrillAnswer(int answer);
	
	void sentUserRanking();
	
	void addPlayerByUsername();
	void assignAColor();
	void sendPlayersUsername();
	void arePlayersReady();
	void getRegionStatus();
	void MapIsFull();

public:
	Game(Storage& storage, crow::SimpleApp& app);

	std::vector<int> attackPriority();
	bool find(int x, std::vector<int> v);
	std::vector<int> generateMUltipleDifferentRandom(int no, int upperBound);
	
	void launchNumericalQuestionAndReturnRanking();
	void getTheLeaderBoard();
	void GetPlayersBases();
	void gameManager();

	void Duel(std::shared_ptr<User>& attacker, std::shared_ptr<User>& defender, std::shared_ptr<Region>& region);

	void clickedCoordinates();
	
};