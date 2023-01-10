#pragma once
#include <optional>
#include "utils.h"
#include "Storage.h"
#include <regex>


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

class GetUserbyUserName
{
public: 
	GetUserbyUserName(Storage& storage, std::optional<User>& user);

	crow::response operator() (const crow::request& req) const;
	
private:
	Storage& m_db;
	std::optional<User>& m_user;
};

void routeForStatistics(crow::SimpleApp& app, Storage& m_db);
