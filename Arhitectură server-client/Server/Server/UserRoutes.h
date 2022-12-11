#pragma once
#include "Storage.h"
#include <optional>

std::optional<User> existUserName(const std::string& username, Storage& m_db);

void routeForSignin(crow::SimpleApp& app, Storage& m_db);
class AddNewUserHandler {
public:
	AddNewUserHandler(Storage& storage);

	crow::response operator() (const crow::request& req) const;
private:
	Storage& m_db;
};

void routeForLogin(crow::SimpleApp& app, Storage& m_db);
