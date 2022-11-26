#pragma once
#include <string>
#include <vector>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

//#include "utils.h"

struct NumericalQuestion
{
	int id;
	std::string question;
	int indexCorrectAnswer;
};



inline auto createStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"NumericalQuestions",
			sql::make_column("id", &NumericalQuestion::id, sql::autoincrement(), sql::primary_key()),
			sql::make_column("question", &NumericalQuestion::question),
			sql::make_column("intdexCorrectAnswer", &NumericalQuestion::indexCorrectAnswer)
		)
	);
}

using Storage = decltype(createStorage(""));


void populateStorage(Storage& storage);

