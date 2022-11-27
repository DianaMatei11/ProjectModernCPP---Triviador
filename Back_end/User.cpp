#include "User.h"

User::User(std::string userName, std::string pass) :
	user_name{userName}, password{pass}
{
	m_raspunsIntrebariCorecte = 0;
	m_raspunsuriTotale = 0;
	m_meciuriJucate = 0;
	m_scorMinim = 0;
	m_scorMaxim = 0;
}

User::User(std::string userName, std::string pass, int raspunsIntrebariCorecte, int raspunsuriTotale, int meciuriJucate, int scorMaxim, int scorMinim):
	user_name{ userName }, password{ pass }
{
	m_raspunsIntrebariCorecte = raspunsIntrebariCorecte;
	m_raspunsuriTotale = raspunsuriTotale;
	m_meciuriJucate = meciuriJucate;
	m_scorMinim = scorMaxim;
	m_scorMaxim = scorMinim;
}

std::string User::getUserName() const
{
	return user_name;
}

std::string User::getPassword() const
{
	return password;
}

void User::changePassword(const std::string& pass)
{
	password = pass;
}


std::string User::checkStrongPassword()
{
	if (password.size() < 8)
	{
		return "Your password need to have at least 8 characters\n";
	}

	bool upper = false, specialCh = false, digit = false;
	for (char c : password)
	{
		if (isupper(c))
		{
			upper = true;
		}

		if (!isalnum(c))
		{
			specialCh = true;
		}

		if (isdigit(c))
		{
			digit = true;
		}

		if (upper && specialCh && digit)
		{
			return "Strong\n";
		}
	}

	if (!upper)
	{
		return "Your password need to have at least an uppercase character\n";
	}

	if (!specialCh)
	{
		return "Your password need to have at least a special character like +\n";
	}

	if (!digit)
	{
		return "Your password need to have at least a number\n";
	}
}

void User::forgotPasswordProtocol(std::ostream& out, std::istream& in)
{
	std::string pass;
again:
	out << "Type the last password you remember or at least 60% of it: ";
	in >> pass;
	while (pass.size() < (int)(password.size() * 3.0 / 5.0))
	{
		out << "Sorry, it's too short. Try again: ";
		in >> pass;
	}

	if (password.find(pass) != password.npos)
	{
		out << "It's enough to believe is you\n";
		out << "Type a new password: ";
		in >> pass;
		changePassword(pass);
	}
	else
	{
		out << "Sorry, it doesn't mach to your old password\n";
		goto again;
	}
}

float User::getProcentajRaspunsuriCorecte()
{
	if (m_raspunsuriTotale != 0) {
		return float(m_raspunsIntrebariCorecte) / float(m_raspunsuriTotale);
	}
	else
	{
		std::cerr << "[WARNING] Nu a fost jucat nici un meci!\n";
		exit(0);
	}
}

int User::getMeciuriJucate()
{
	return m_meciuriJucate;
}

int User::getScorMinim()
{
	return m_scorMinim;
}

int User::getScorMaxim()
{
	return m_scorMaxim;
}

int User::getRaspunsuriCorecte()
{
	return m_raspunsIntrebariCorecte;
}

int User::getRaspunsuriTotale()
{
	return m_raspunsuriTotale;
}

void User::updateRaspunsuriCorecte()
{
	m_raspunsIntrebariCorecte++;
}

void User::updateRaspunsuriTotale()
{
	m_raspunsuriTotale++;
}

void User::updateMeciuriJucate()
{
	m_meciuriJucate++;
}

void User::updateScorMinim(int scor)
{
	if (scor < m_scorMinim)
	{
		m_scorMinim = scor;
	}
}

void User::updateScorMaxim(int scor)
{
	if (scor > m_scorMaxim)
	{
		m_scorMaxim = scor;
	}
}


std::istream& operator>>(std::istream& in, User& user)
{
	in >> user.user_name >> user.password;
	in>>user.m_raspunsIntrebariCorecte;
	in>>user.m_raspunsuriTotale;
	in>>user.m_meciuriJucate;
	in>>user.m_scorMinim;
	in>>user.m_scorMaxim;
	return in;
}

std::ostream& operator<<(std::ostream& out, User& user)
{
	out << user.user_name << ' ' << user.password<<' '<<user.m_raspunsIntrebariCorecte<<' '<<user.m_raspunsuriTotale<<' '<<user.m_meciuriJucate<<' ';
	out << user.m_scorMinim << ' ' << user.m_scorMaxim;

	return out;
}
