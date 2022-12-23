#pragma once
#include <iostream>
#include <vector>
#include "UserRoutes.h"
#include "Map.h"
#include <crow.h>

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
	
	std::vector<crow::json::wvalue> numericalQuest_json;
	std::vector<crow::json::wvalue> quizzes_json;
	std::vector<crow::json::wvalue> numericalAnswers_json;
	std::vector<crow::json::wvalue> users_json;

    void initNumericalQuest_json();
	void initQuizzes_json();
	void initNumericalAnswers_json();
	void initUsers_json();
	
	void sentANumericalQuestionRoute();
	void sentAGrillQuestionRoute();

	int verifyCorrectAnswer(int id, const std::vector<int> &answers);
	int verifyCorrectGrillAnswer(int id, const std::vector<int> &answers);
	
	void addPlayerByUsername();
	void assignAColor();

public:
	Game(Storage& storage, crow::SimpleApp& app);
	
	void conqueringRound();
	
};