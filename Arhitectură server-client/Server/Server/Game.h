#include <iostream>
#include <vector>
#include "Storage.h"
#include <crow.h>
#include "User.h"
class Game {
public:
	std::vector<User> players;
	//MAP map;
	enum colors {
		red,
		yellow,
		blue,
		green
	};

	const std::string db_file = "Storage.sqlite";
	Storage storage = createStorage(db_file);
	
	std::vector<crow::json::wvalue> numericalQuest_json;
	std::vector<crow::json::wvalue> quizzes_json;
	std::vector<crow::json::wvalue> numericalAnswers_json;
   
	crow::SimpleApp app;
    void initNumericalQuest_json();
	void initQuizzes_json();
	void initNumericalAnswers_json();
	
	void getUsersAnswer();
	void WinnersNumericalQuestion(std::string id);
	void WinnersGrillQuestion(std::string id);

	int sentANumericalQuestionRoute();
	int sentAGrillQuestionRoute();
	
	int SentCorrectAnswer(int id, std::vector<int> answers);
	int SentCorrectGrillAnswer(int id, std::vector<int> answers);

};