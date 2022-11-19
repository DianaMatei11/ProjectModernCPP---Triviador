#pragma once
#include "User.h"
#include <vector>
#include <iostream>
#include <regex>
#include <fstream>

class Conect
{
	std::vector<User> users;
public:
	std::vector<User>& getUsers();
	int findUser(const std::string& name);
	void signIn();
	void logIn();
	void meniu();
	void readFile();
	void saveInFile();
	void schimbareParolaCorecta(User& user);

};

