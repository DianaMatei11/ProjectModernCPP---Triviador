#pragma once
#include "User.h"
#include <vector>
#include <iostream>
#include <regex>
class Conect
{
	std::vector<User> users;
public:
	std::vector<User> getUsers();
	bool findName(std::string name);
	bool findPass(std::string pass);
	void signIn();
	void logIn();
	void meniu();
};

