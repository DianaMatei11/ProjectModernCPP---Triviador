#include "User.h"

User::User(std::string userName, std::string pass):
	user_name{userName}, password{pass}
{}

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

void User::forgotPasswordProtocol(std::ostream& out, std::istream& in)
{
	std::string pass;
again:
	out << "Type the last password you remember or at least 60% of it: ";
	in >> pass;
	while (pass.size() < (int)(password.size() * 3.0 / 5.0))
	{
		out << "Sorry, it's too short. Try again: ";
		in >> pass;
	}

	if (password.find(pass) != password.npos)
	{
		out << "It's enough to believe is you\n";
		out << "Type a new password: ";
		in >> pass;
		changePassword(pass);
	}
	else
	{
		out << "Sorry, it doesn't mach to your old password\n";
		goto again;
	}
}


std::istream& operator>>(std::istream& in, User& user)
{
	in >> user.user_name >> user.password;
	return in;
}
