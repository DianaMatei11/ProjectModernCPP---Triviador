#pragma once
#include <fstream>

class User
{
private:
	std::string user_name, password;
	void changePassword(const std::string& pass);

public:
	User() = default;
	User(std::string userName, std::string pass);
	std::string getUserName() const;
	std::string& getPassword();
	friend std::istream& operator >> (std::istream& in, User& user);
	std::string checkStrongPassword();
	void forgotPasswordProtocol(std::ostream& out, std::istream& in);
	~User() = default;
};

