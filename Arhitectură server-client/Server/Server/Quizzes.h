#pragma once
#include <string>
#include <vector>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

//#include "utils.h"

struct Quiz
{
	int id;
	std::string question;
	std::string possibleAnswer0;
	std::string possibleAnswer1;
	std::string possibleAnswer2;
	std::string possibleAnswer3;
	int indexCorrectAnswer;
};



inline auto createOptQuestionsStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Quizzes",
			sql::make_column("id", &Quiz::id, sql::autoincrement(), sql::primary_key()),
			sql::make_column("question", &Quiz::question),
			sql::make_column("possibleAnsewer0", &Quiz::possibleAnswer0),
			sql::make_column("possibleAnsewer0", &Quiz::possibleAnswer1),
			sql::make_column("possibleAnsewer0", &Quiz::possibleAnswer2),
			sql::make_column("possibleAnsewer0", &Quiz::possibleAnswer3),
			sql::make_column("indexCorrectAnsewer", &Quiz::indexCorrectAnswer)
		)
	);
}

using OptQuestionsStorage = decltype(createOptQuestionsStorage(""));


void populateOptQuestionsStorage(OptQuestionsStorage& storage);

