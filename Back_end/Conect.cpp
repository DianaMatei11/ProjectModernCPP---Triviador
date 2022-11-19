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
		User user;
		while (!file.eof())
		{
			file >> user;
			users.emplace_back(user);
		}
	}
	file.close();
}

void Conect::saveInFile()
{
	std::ofstream file{ "users.txt" };
	remove("users.txt");
	for (int i = 0; i < users.size() - 1; i++)
	{
		file << users[i] << '\n';
	}
	file << users[users.size() - 1];
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

std::vector<User>& Conect::getUsers()
{
	return users;
}

int Conect::findUser(const std::string& name)
{
	for (int i = 0; i < users.size(); i++)
	{
		if (users[i].getUserName() == name)
		{
			return i;
		}
	}
	return -1;
}

void Conect::signIn()
{
	std::string name0, pass0;
citireUsername:
	std::cout << "Enter your username: ";
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
	while (findUser(name0) != -1)
	{
		std::cout << "This name already exists. Please enter another name.\n ";
		goto citireUsername;
	}

	std::cout << "[INFO] Username-ul este disponibil.\n";
	std::cout << "Enter your password: ";
	std::cin >> pass0;
	User x(name0, pass0);
	schimbareParolaCorecta(x);
	std::cout << "[INFO] Username-ul si parola au fost salvate!\n";
	users.emplace_back(x);
}

void Conect::logIn()
{
	std::string name0, pass0;
	std::cout << "Enter your name: ";
	std::cin >> name0;
	int userIndex = findUser(name0);
	if (userIndex == -1)
	{
		std::cout << "Your account does not exist\n";
	}
	else {
		std::cout << "Enter your password: ";
		std::cin >> pass0;
		while (users[userIndex].getPassword() != pass0)
		{
			std::cout << "Your password is not correct.\n";
			char parolaUitata;
			std::cout << "Ati uitat parola?(y/n) ";
			std::cin >> parolaUitata;
			if (parolaUitata == 'y')
			{
				users[userIndex].forgotPasswordProtocol(std::cout, std::cin);
				schimbareParolaCorecta(users[userIndex]);
				std::cout << "[INFO] Parola a fost schimbata!\n";
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
	int option;
	readFile();
	do {
		std::cout << "Your options are:\n1 for sign in\n2 for login\n0 for exit" << std::endl;
		std::cout << "Alege o optiune din lista: "; std::cin >> option;
		switch (option)
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
	} while (option != 0);

	saveInFile();
}
