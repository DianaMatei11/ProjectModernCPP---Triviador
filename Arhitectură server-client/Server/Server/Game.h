#include <iostream>
#include <vector>
#include "Storage.h"
#include <crow.h>
#include "User.h"
class Game {
public:
	std::vector<User> players;
	//MAP map;

	const std::string db_file = "Storage.sqlite";
	Storage storage = createStorage(db_file);
	
	std::vector<crow::json::wvalue> numericalQuest_json;
	std::vector<crow::json::wvalue> quizzes_json;
	std::vector<crow::json::wvalue> numericalAnswers_json;
   
	crow::SimpleApp app;
    void initNumericalQuest_json();
	void initQuizzes_json();
	void initNumericalAnswers_json();
	
	int sentANumericalQuestionRoute();
	int sentAGrillQuestionRoute();
	
	int verifyCorrectAnswer(int id, std::vector<int> answers);
	int verifyCorrectGrillAnswer(int id, std::vector<int> answers);
};