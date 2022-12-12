#include "UserRoutes.h"

static const std::optional<User> k_invalidUser;

std::optional<User> existUserName(const std::string& username, Storage& m_db)
{
	for (const auto& quest : m_db.iterate<User>())
	{
		if (quest.getUserName() == username)
		{
			return std::optional<User>(quest);
		}
	}
	return k_invalidUser;
}

void routeForSignIn(crow::SimpleApp& app, Storage& m_db)
{
	auto& user = CROW_ROUTE(app, "/createnewuser")
		.methods(crow::HTTPMethod::POST);
	user(AddNewUserHandler(m_db));
}

//newUser

AddNewUserHandler::AddNewUserHandler(Storage& storage) :
	m_db{ storage }
{}

//crow::response AddNewUserHandler::operator() (const crow::request& req) const
//{
//	auto body = crow::json::load(req.body);
//	if (!body)
//	{
//		return crow::response(400);
//	}
//
//	auto name = body["name"].s();
//	auto password = body["password"].s();
//
//	m_db.insert(User{ name, password });
//
//	return crow::response(200);
//}

crow::response AddNewUserHandler::operator() (const crow::request& req) const
{
	auto bodyArgs = parseUrlArgs(req.body); //id=2&quantity=3&...
	auto end = bodyArgs.end();
	auto nameIter = bodyArgs.find("Name");
	auto passIter = bodyArgs.find("Password");
	if (nameIter != end && passIter != end)
	{
		if (existUserName(nameIter->second, m_db).has_value())
		{
			return crow::response(451); //UserName already exist
		}


		if (!User::checkStrongPassword((passIter->second)))
		{
			return crow::response(416); //Password not strong enough
		}


		m_db.insert(User{ nameIter->second, passIter->second });
		return crow::response(200); //Added to database
	}
	return crow::response(400); //The transmited info was not ok 
}


//login
void routeForLogin(crow::SimpleApp& app, Storage& m_db)
{
	auto& user = CROW_ROUTE(app, "/verifylogin")
		.methods(crow::HTTPMethod::PUT);
	user(VerifyUserLogin(m_db));
}

VerifyUserLogin::VerifyUserLogin(Storage& storage)
	: m_db{storage}
{}

crow::response VerifyUserLogin::operator()(const crow::request& req) const
{
	auto bodyArgs = parseUrlArgs(req.body); 
	auto end = bodyArgs.end();
	auto nameIter = bodyArgs.find("Name");
	auto passIter = bodyArgs.find("Password");
	if (nameIter != end && passIter != end)
	{
		const auto& user = existUserName(nameIter->second, m_db);
		if (user.has_value())
		{
			if (user->getPassword() == passIter->second)
			{
				return crow::response(200); //Ok
			}
			else
			{
				return crow::response(409); //The password is wrong
			}
		}
		return crow::response(404); //User not found
	}
	return crow::response(400); //The transmited info was not ok 
}
