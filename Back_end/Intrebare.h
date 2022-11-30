#include <string>
#include <random>
#pragma once
class Intrebare
{
protected:
	std::string m_enunt;
public:
	Intrebare() = default;
	Intrebare(const std::string& enunt);
	static int GetRandomNumber(const int x,const int y);
	void SetEnunt(const std::string& enunt);
	std::string GetEnunt() const;
};

