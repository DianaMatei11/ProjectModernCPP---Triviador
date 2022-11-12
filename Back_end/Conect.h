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
	std::vector<User> getUsers();
	bool findName(std::string name);
	bool findPass(std::string pass);
	void signIn();
	void logIn();
	void meniu();
	void readFile();
	void saveInFile();
	void schimbareParolaCorecta(User& user);

};

