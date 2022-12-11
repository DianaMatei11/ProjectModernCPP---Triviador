#pragma once
#include <fstream>
#include <iostream>

class User
{
private:
	uint16_t m_id;
	std::string user_name, password;
	int m_raspunsIntrebariCorecte;
	int m_raspunsuriTotale;
	int m_meciuriJucate;
	int m_scorMaxim, m_scorMinim;

public:
	User() = default;
	User(std::string userName, std::string pass,int raspunsIntrebariCorecte = 0,int raspunsuriTotale = 0,int meciuriJucate = 0,int scorMaxim = 0, int scorMinim = 0);
	
	uint16_t GetId() const;
	void SetId(const uint16_t& newId);

	std::string getUserName() const ;
	void setUserName(const std::string& username);
	std::string getPassword() const ;
	void setPassword(const std::string& pass);
	void changePassword(const std::string& pass);
	friend std::istream& operator >> (std::istream& in, User& user);
	friend std::ostream& operator << (std::ostream& out, User& user);
	std::string checkStrongPassword();
	void forgotPasswordProtocol(std::ostream& out, std::istream& in);
	~User() = default;

	float getProcentajRaspunsuriCorecte();
	int getMeciuriJucate() const ;
	void setMeciuriJucate(const int meciuriJucate);
	int getScorMinim() const ;
	void setScorMinim(const int scorMinim);
	int getScorMaxim() const ;
	void setScorMaxim(const int scorMaxim);
	int getRaspunsuriCorecte() const ;
	void setRaspunsuriCorecte(const int raspunsuriCorecte);
	int getRaspunsuriTotale() const ;
	void setRaspunsuriTotale(const int raspunsuriTotale);

	void updateRaspunsuriCorecte();
	void updateRaspunsuriTotale();
	void updateMeciuriJucate();
	void updateScorMinim(int scor);
	void updateScorMaxim(int scor);
};

