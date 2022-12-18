#pragma once
#include <iostream>
#include <vector>
#include "Storage.h"
#include <crow.h>

class Game {

private:
	std::vector<std::shared_ptr<User>> players;
	Storage storage;
	//MAP map;

	enum colors {
		red = 0,
		yellow = 1,
		blue = 2,
		green = 3
	};


public:
	Game(Storage& storage);
	
	std::vector<crow::json::wvalue> numericalQuest_json;
	std::vector<crow::json::wvalue> quizzes_json;
	std::vector<crow::json::wvalue> numericalAnswers_json;
	std::vector<crow::json::wvalue> users_json;

	crow::SimpleApp app;
    void initNumericalQuest_json();
	void initQuizzes_json();
	void initNumericalAnswers_json();
	void initUsers_json();
	
	void sentANumericalQuestionRoute();
	void sentAGrillQuestionRoute();
	void addNewPlayer(std::shared_ptr<User> user);

	int verifyCorrectAnswer(int id, const std::vector<int> &answers);
	int verifyCorrectGrillAnswer(int id, const std::vector<int> &answers);
	void assignAColor();
};