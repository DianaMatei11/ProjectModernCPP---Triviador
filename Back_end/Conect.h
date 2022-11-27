#pragma once
#include "User.h"
#include <vector>
#include <iostream>
#include <regex>
#include <fstream>
#include <unordered_map>

class Conect
{
	std::unordered_map<std::string, User> users;
public:
	std::unordered_map<std::string, User>& getUsers();
	int findUser(const std::string& name);
	void signIn();
	void logIn();
	void meniu();
	void readFile();
	void saveInFile();
	void schimbareParolaCorecta(User& user);

};

