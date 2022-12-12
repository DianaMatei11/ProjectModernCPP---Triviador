#include "User.h"

User::User(std::string userName, std::string pass, int raspunsIntrebariCorecte, int raspunsuriTotale, int meciuriJucate, int scorMaxim, int scorMinim) : 
user_name{ userName },
password{ pass },
m_raspunsIntrebariCorecte{ raspunsIntrebariCorecte },
m_raspunsuriTotale{ raspunsuriTotale },
m_meciuriJucate{ meciuriJucate },
m_scorMinim{ scorMaxim },
m_scorMaxim{ scorMinim }
{}

uint16_t User::GetId() const
{
	return m_id;
}

void User::SetId(const uint16_t& newId)
{
	m_id = newId;
}

std::string User::getUserName() const
{
	return user_name;
}

void User::setUserName(const std::string& username)
{
	user_name = username;
}

std::string User::getPassword() const
{
	return password;
}

void User::setPassword(const std::string& pass)
{
	password = pass;
}

void User::changePassword(const std::string& pass)
{
	password = pass;
}


bool User::checkStrongPassword(const std::string& password)
{
	if (password.size() < 8)
	{
		return false;
		//return "Your password need to have at least 8 characters\n";
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
			//return "Strong\n";
			return true;
		}
	}

	if (!upper)
	{
		return false;
		//return "Your password need to have at least an uppercase character\n";
	}

	if (!specialCh)
	{
		return false;
		//return "Your password need to have at least a special character like +\n";
	}

	if (!digit)
	{
		return false;
		//return "Your password need to have at least a number\n";
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

int User::getMeciuriJucate() const
{
	return m_meciuriJucate;
}

void User::setMeciuriJucate(const int meciuriJucate)
{
	m_meciuriJucate = meciuriJucate;
}

int User::getScorMinim() const
{
	return m_scorMinim;
}

void User::setScorMinim(const int scorMinim)
{
	m_scorMinim = scorMinim;
}

int User::getScorMaxim() const
{
	return m_scorMaxim;
}

void User::setScorMaxim(const int scorMaxim)
{
	m_scorMaxim = scorMaxim;
}

int User::getRaspunsuriCorecte() const
{
	return m_raspunsIntrebariCorecte;
}

void User::setRaspunsuriCorecte(const int raspunsuriCorecte)
{
	m_raspunsIntrebariCorecte = raspunsuriCorecte;
}

int User::getRaspunsuriTotale() const
{
	return m_raspunsuriTotale;
}

void User::setRaspunsuriTotale(const int raspunsuriTotale)
{
	m_raspunsuriTotale = raspunsuriTotale;
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
