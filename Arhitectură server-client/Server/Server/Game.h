#include <iostream>
#include <vector>
#include "Storage.h"
#include <crow.h>
class Game {
public:

	const std::string db_file = "Storage.sqlite";
	Storage storage = createStorage(db_file);
	int a;
	std::vector<crow::json::wvalue> numericalQuest_json;
	std::vector<crow::json::wvalue> quizzes_json;
    crow::SimpleApp app;
    
	
	void initNumericalQuest_json();
	void initQuizzes_json();
	
	void sentANumericalQuestionRoute(std::vector<crow::json::wvalue> numericalQuest_json);
};