#include "Conect.h"

void Conect::readFile()
{
	std::ifstream file{ "users.txt" };
	if (!file)
	{
		std::cerr << "File error\n";
		exit(0);
	}
	{
		std::string username, password;
		while (!file.eof())
		{
			file >> username >> password;
			if(!findName(username))
				users.emplace_back(User(username, password));
		}
	}
}

void Conect::saveInFile()
{
	std::ofstream file{ "users.txt" };
	remove("users.txt");
	for (auto& user : users)
	{
		file << user.getUserName() << ' ' << user.getPassword() << '\n';
	}
	file.close();
}

void Conect::schimbareParolaCorecta(User& user)
{
	while (user.checkStrongPassword() != "Strong\n")
	{
		std::cout << user.checkStrongPassword();
		std::cout << "[WARNING] Introduceti o parola care sa respecte regulile: ";
		std::string parolaNoua;
		std::cin >> parolaNoua;
		user.changePassword(parolaNoua);
	}
}


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
	schimbareParolaCorecta(x);
	std::cout << "[INFO] Username-ul si parola au fost salvate!\n";
	users.push_back(x);
}
void Conect::logIn()
{
	std::string name0, pass0;
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
						user.changePassword("0");
						schimbareParolaCorecta(user);
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
	readFile();
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
	saveInFile();
}
