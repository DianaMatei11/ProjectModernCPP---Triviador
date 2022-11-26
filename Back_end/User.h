#pragma once
#include <fstream>

class User
{
private:
	std::string user_name, password;

public:
	User() = default;
	User(std::string userName, std::string pass);
	std::string getUserName() const;
	std::string getPassword() const;
	void changePassword(const std::string& pass);
	friend std::istream& operator >> (std::istream& in, User& user);
	friend std::ostream& operator << (std::ostream& out, User& user);
	std::string checkStrongPassword();
	void forgotPasswordProtocol(std::ostream& out, std::istream& in);
	~User() = default;
};

