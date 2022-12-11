#include "UserRoutes.h"


std::optional<User> existUserName(const std::string& username, Storage& m_db)
{
	for (const auto& quest : m_db.iterate<User>())
	{
		if (quest.getUserName() == username)
		{
			return std::optional<User>(quest);
		}
	}
	return std::optional<User>();
}

//newUser
void routeForSignin(crow::SimpleApp& app, Storage& m_db)
{
	auto& user = CROW_ROUTE(app, "/createnewuser")
		.methods(crow::HTTPMethod::PUT);
	//user(AddNewUserHandler(m_db));
}




//login
void routeForLogin(crow::SimpleApp& app, Storage& m_db)
{
	auto& user = CROW_ROUTE(app, "/verifylogin")
		.methods(crow::HTTPMethod::PUT);
	//user(VerifyUserLogin(m_db));
}


