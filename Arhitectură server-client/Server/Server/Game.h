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
		red = 0,
		yellow = 1,
		blue = 2,
		green = 3
	};

	const std::string db_file = "Storage.sqlite";
	Storage storage = createStorage(db_file);
	
	std::vector<crow::json::wvalue> numericalQuest_json;
	std::vector<crow::json::wvalue> quizzes_json;
	std::vector<crow::json::wvalue> numericalAnswers_json;
	std::vector<crow::json::wvalue> users_json;

	void addNewPlayer(int id);
   
	crow::SimpleApp app;
    void initNumericalQuest_json();
	void initQuizzes_json();
	void initNumericalAnswers_json();
	void initUsers_json();
	
	void addNewPlayer(std::string name, std::string password);
	void sentANumericalQuestionRoute(std::vector<crow::json::wvalue> numericalQuest_json);
	void sentAGrillQuestionRoute(std::vector<crow::json::wvalue> quizzes_json);
	void assignAColor(User user,std::vector<User> Players);
	int verifyCorrectAnswer(std::vector<crow::json::wvalue> numericalQuest_json,int id, std::vector<int> answers);
};