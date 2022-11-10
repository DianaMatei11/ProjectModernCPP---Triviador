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


std::string User::checkStrongPassword()
{
	if (password.size() < 8)
	{
		return "Your password need to have at least 8 characters\n";
	}

	bool upper = false, specialCh = false, digit = false;
	for (char c : password)
	{
		if (isupper(c))
		{
			upper = true;
		}

		if (!isalnum(c))
		{
			specialCh = true;
		}

		if (isdigit(c))
		{
			digit = true;
		}

		if (upper && specialCh && digit)
		{
			return "Strong\n";
		}
	}

	if (!upper)
	{
		return "Your password need to have at least an uppercase character\n";
	}

	if (!specialCh)
	{
		return "Your password need to have at least a special character like +\n";
	}

	if (!digit)
	{
		return "Your password need to have at least a number\n";
	}
}


std::istream& operator>>(std::istream& in, User& user)
{
	in >> user.user_name >> user.password;
	return in;
}
