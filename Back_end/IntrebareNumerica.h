#pragma once
#include<string>
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
	~IntrebareNumerica() = default;
};

