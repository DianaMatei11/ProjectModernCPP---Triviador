#pragma once
#include <fstream>

class User
{
private:
	std::string user_name, password;

public:
	User() = default;
	std::string getUserName() const;
	std::string& getPassword();
	friend std::istream& operator >> (std::istream& in, User& user);
	void changePassword(const std::string& pass);
};

