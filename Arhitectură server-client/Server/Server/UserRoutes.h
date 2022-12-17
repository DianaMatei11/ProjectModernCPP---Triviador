#pragma once
#include "Storage.h"
#include <optional>
#include "utils.h"

std::optional<User> existUserName(const std::string& username, Storage& m_db);

void routeForSignIn(crow::SimpleApp& app, Storage& m_db);

class AddNewUserHandler {
public:
	AddNewUserHandler(Storage& storage);

	crow::response operator() (const crow::request& req) const;
private:
	Storage& m_db;
};

void routeForLogin(crow::SimpleApp& app, Storage& m_db);

class VerifyUserLogin
{
public:
	VerifyUserLogin(Storage& storage);

	crow::response operator() (const crow::request& req) const;
private:
	Storage& m_db;
};