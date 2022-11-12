#pragma once
#include<string>
#include <iostream>
class IntrebareNumerica
{
private:
	std::string m_enunt;
	int m_raspuns;

public:
	IntrebareNumerica() = default;
	IntrebareNumerica(std::string enunt, int raspuns);
	std::string GetEnunt() const;
	int GetRaspuns() const;
	friend std::istream& operator >> (std::istream& in, IntrebareNumerica& int);
	friend std::ostream& operator <<(std::ostream& out, const IntrebareNumerica& int);
	~IntrebareNumerica() = default;
};

