#include "Conect.h"
#include <iostream>
std::vector<User> Conect::getUsers()
{
	return users;
}

bool Conect::findName(std::string name)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].getUserName() == name)return true;
	}
	return false;
}

bool Conect::findPass(std::string pass)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].getPassword() == pass)return true;
	}
	return false;
}

void Conect::signIn()
{
	std::string name0, pass0;
	std::cout << "Enter your name: ";
	std::cin >> name0;
	while (findName(name0) == true)
	{
		std::cout << "This name already exists.Please enter another name: ";
		std::cin >> name0;
	}
	std::cout << "Enter your password: ";
	std::cin >> pass0;
	User x(name0, pass0);
	users.push_back(x);
}
void Conect::logIn()
{

	std::string name0, pass0;
	std::cout << "Enter your name: ";
	std::cin >> name0;
	if (!findName(name0))std::cout << "Your account does not exist";
	else {
		std::cout << "Enter your password: ";
		std::cin >> pass0;
		while (!findPass(pass0))
		{
			std::cout << "Your password is not correct. Please enter again:";
			std::cin >> pass0;
		}
	}

}

void Conect::meniu()
{
	std::cout << "Your options are:\n1 for sign in\n2 for login\n0 for exit" << std::endl;
	int x;
	std::cin >> x;
		switch (x)
		{
		case 1: signIn();
			break;
		case 2: logIn();
			break;
		default:std::cout << "Your option is invalid!";
	    }
}
