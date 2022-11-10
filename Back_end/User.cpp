#include "User.h"

std::string User::getUserName() const
{
	return user_name;
}

std::string& User::getPassword()
{
	return password;
}

void User::changePassword(const std::string& pass)
{
	password = pass;
}

std::istream& operator>>(std::istream& in, User& user)
{
	in >> user.user_name >> user.password;
	return in;
}
