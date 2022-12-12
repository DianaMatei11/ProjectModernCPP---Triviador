#pragma once
#include <string>
#include <vector>

#include "User.h"
#include "IntrebareNumerica.h"
#include "IntrebariGrila.h"


#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;


inline auto createStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Users",
			sql::make_column("Id", &User::GetId, &User::SetId, sql::autoincrement(), sql::primary_key()),
			sql::make_column("Name", &User::getUserName, &User::setUserName),
			sql::make_column("Password", &User::getPassword, &User::setPassword),
			sql::make_column("TotalGames", &User::getMeciuriJucate, &User::setMeciuriJucate),
			sql::make_column("NumberOfCorrectAnswers", &User::getRaspunsuriCorecte, &User::setRaspunsuriCorecte),
			sql::make_column("NumberOfAnswers", &User::getRaspunsuriTotale, &User::setRaspunsuriTotale),
			sql::make_column("MaxScore", &User::getScorMaxim, &User::setScorMaxim),
			sql::make_column("MinScore", &User::getScorMinim, &User::setScorMinim)
		),
		sql::make_table(
			"NumericalQuestions",
			sql::make_column("Id", &IntrebareNumerica::GetId, &IntrebareNumerica::SetId, sql::autoincrement(), sql::primary_key()),
			sql::make_column("Question", &IntrebareNumerica::GetEnunt, &IntrebareNumerica::SetEnunt),
			sql::make_column("Answer", &IntrebareNumerica::GetRaspuns, &IntrebareNumerica::SetRaspuns)
		),
		sql::make_table(
			"Quizzes",
			sql::make_column("Id", &IntrebariGrila::GetId, &IntrebariGrila::SetId, sql::autoincrement(), sql::primary_key()),
			sql::make_column("Question", &IntrebariGrila::GetEnunt, &IntrebariGrila::SetEnunt),
			sql::make_column("option0", &IntrebariGrila::GetOption0, &IntrebariGrila::SetOption0),
			sql::make_column("option1", &IntrebariGrila::GetOption1, &IntrebariGrila::SetOption1),
			sql::make_column("option2", &IntrebariGrila::GetOption2, &IntrebariGrila::SetOption2),
			sql::make_column("option3", &IntrebariGrila::GetOption3, &IntrebariGrila::SetOption3),
			sql::make_column("IndexCorrectOption", &IntrebariGrila::GetIndex_Rasp_Corect, &IntrebariGrila::SetIndex_Rasp_Corect)
		)
	);
}

using Storage = decltype(createStorage(""));

void populateStorage(Storage& storage);

