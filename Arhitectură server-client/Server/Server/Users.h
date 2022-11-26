#pragma once
#include <string>
#include <vector>

#include <crow.h>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;

//#include "utils.h"

struct User
{
	int id;
	std::string name;
	std::string pass;
	int totalGames;
	int wonGames;
};



inline auto createUsersStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Users",
			sql::make_column("id", &User::id, sql::autoincrement(), sql::primary_key()),
			sql::make_column("name", &User::name),
			sql::make_column("pass", &User::pass),
			sql::make_column("totalGames", &User::totalGames),
			sql::make_column("wonGames", &User::wonGames)
		)
	);
}

using UsersStorage = decltype(createUsersStorage(""));


void populateUsersStorage(UsersStorage& storage);

