#pragma once
#include <fstream>
#include <iostream>

class User
{
private:
	std::string user_name, password;
	int m_raspunsIntrebariCorecte;
	int m_raspunsuriTotale;
	int m_meciuriJucate;
	int m_scorMaxim, m_scorMinim;

public:
	User() = default;
	User(std::string userName, std::string pass);

	User(std::string userName, std::string pass,int raspunsIntrebariCorecte,int raspunsuriTotale,int meciuriJucate,int scorMaxim,int scorMinim);
	
	std::string getUserName() const;
	std::string getPassword() const;
	void changePassword(const std::string& pass);
	friend std::istream& operator >> (std::istream& in, User& user);
	friend std::ostream& operator << (std::ostream& out, User& user);
	std::string checkStrongPassword();
	void forgotPasswordProtocol(std::ostream& out, std::istream& in);
	~User() = default;

	float getProcentajRaspunsuriCorecte();
	int getMeciuriJucate();
	int getScorMinim();
	int getScorMaxim();
	int getRaspunsuriCorecte();
	int getRaspunsuriTotale();

	void updateRaspunsuriCorecte();
	void updateRaspunsuriTotale();
	void updateMeciuriJucate();
	void updateScorMinim(int scor);
	void updateScorMaxim(int scor);
};

