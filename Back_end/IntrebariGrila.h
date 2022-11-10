#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<array>
class IntrebariGrila
{public:
	std::string enunt;
	std::array <std::string,4> raspunsuri;
	int index_rasp_corect;
public:
	IntrebariGrila() = default;
	IntrebariGrila(std::string enunt, std::array < std::string, 4> raspunsuri, int index_rasp_corect);
	friend std::istream& operator>>(std::istream& IntrebariCuVariante, IntrebariGrila& intrebari);
	friend std::ostream& operator << (std::ostream& out, const IntrebariGrila& intrebari);
	//~IntrebariGrila();
};

