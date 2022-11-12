#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<array>
#include<vector>
class IntrebariGrila
{
private:
	std::string enunt;
	std::array <std::string, 4> raspunsuri;
	int index_rasp_corect;
public:
	IntrebariGrila() = default;
	IntrebariGrila(std::string enunt, std::array < std::string, 4> raspunsuri, int index_rasp_corect);

	void SetEnunt(const std::string& enunt);
	void SetRaspunsuri(const std::string& raspunsuri);
	void SetIndex_Rasp_Corect(int index_rasp_corect);

	std::string GetEnunt();
	std::array<std::string, 4> GetRaspunsuri();
	int GetIndex_Rasp_Corect();

	friend std::istream& operator>>(std::istream& in, IntrebariGrila& a);
	friend std::ostream& operator << (std::ostream& out, const IntrebariGrila& a);
	//~IntrebariGrila();
};

