#pragma once
#include <fstream>
#include <sqlite_orm/sqlite_orm.h>
namespace sql = sqlite_orm;
class User
{
private:
	std::string user_name, password;

public:
	User() = default;
	User(std::string userName, std::string pass);
	std::string getUserName() const;
	std::string getPassword() const;
	void setUserName(std::string a);
	void setPassword(std::string a);
	void changePassword(const std::string& pass);
	friend std::istream& operator >> (std::istream& in, User& user);
	friend std::ostream& operator << (std::ostream& out, User& user);
	std::string checkStrongPassword();
	void forgotPasswordProtocol(std::ostream& out, std::istream& in);
	~User() = default;
};

inline auto createStorage(const std::string& filename)
{
	return sql::make_storage(
		filename,
		sql::make_table(
			"Products",
			sql::make_column("USER_NAME", &User::getUserName,&User::setUserName, sql::autoincrement(), sql::primary_key()),
			sql::make_column("PASSWORD", &User::getPassword,&User::setPassword)
		)
	);
}