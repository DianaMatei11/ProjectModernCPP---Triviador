#include "Conect.h"

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
citireUsername:
	std::cout << "Enter your name: ";
	std::cin >> name0;
	std::string usernamePattern = "([a-zA-Z0-9_]){5,15}";
	std::regex usernameRule(usernamePattern);
	bool usernameValid = regex_match(name0, usernameRule);
	if (usernameValid)
	{
		std::cout << "[INFO] Username-ul respecta regulile de validare!\n";
	}
	else {
		std::cout << "[WARNING] Username-ul trebuie sa contina litere mari, litere mici, cifre, sau '_', si sa aibe intre 5 si 15 caractere!\n\n";
		goto citireUsername;
	}
	while (findName(name0) == true)
	{
		std::cout << "This name already exists. Please enter another name.\n ";
		goto citireUsername;
	}
	if (!findName(name0))
	{
		std::cout << "[INFO] Username-ul este disponibil.\n";
	}
	std::cout << "Enter your password: ";
	std::cin >> pass0;
	User x(name0, pass0);
	while (x.checkStrongPassword() != "Strong\n")
	{
		std::cout<<x.checkStrongPassword();
		std::cout << "[WARNING] Introduceti o parola care sa respecte regulile: ";
		std::string parolaNoua;
		std::cin >> parolaNoua;
		x.changePassword(parolaNoua);
	}
	std::cout << "[INFO] Username-ul si parola au fost salvate!\n";
	users.push_back(x);
}
void Conect::logIn()
{
	std::string name0, pass0;
	//std::vector<User> users=getUsers();
	std::cout << "Enter your name: ";
	std::cin >> name0;
	if (!findName(name0))
		std::cout << "Your account does not exist\n";
	else {
		std::cout << "Enter your password: ";
		std::cin >> pass0;
		while (!findPass(pass0))
		{
			std::cout << "Your password is not correct.\n";
			char parolaUitata;
			std::cout << "Ati uitat parola?(y/n) ";
			std::cin >> parolaUitata;
			if (parolaUitata == 'y')
			{
				for (auto& user : users)
				{
					if (user.getUserName() == name0) {
						std::string parolaNoua;
						std::cout << "Parola noua: ";
						std::cin >> parolaNoua;
						user.changePassword(parolaNoua);
						std::cout << "[INFO] Parola a fost schimbata!\n";
						break;
					}
				}
				std::cout << "Please enter again: ";
				std::cin >> pass0;
			}
			else {
				std::cout << "Please enter again: ";
				std::cin >> pass0;
			}
		}
	}
	std::cout << "[INFO] Sunteti conectat!\n";
}

void Conect::meniu()
{
	int x;
	do {
		std::cout << "Your options are:\n1 for sign in\n2 for login\n0 for exit" << std::endl;
		std::cout << "Alege o optiune din lista: "; std::cin >> x;
		switch (x)
		{
		case 1: signIn();
			break;
		case 2: logIn();
			break;
		case 0:
			std::cout << "[INFO] Ati iesit din program!\n";
			break;
		default:std::cout << "Your option is invalid!\n";
		}
	} while (x != 0);
}
