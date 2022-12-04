#include <string>
#include <random>
#pragma once
class Intrebare
{
protected:
	std::string m_enunt;
	//uint16_t m_id;
public:
	Intrebare() = default;
	Intrebare(const std::string& enunt);
	static int GetRandomNumber(const int x,const int y);
	void SetEnunt(const std::string& enunt);
	std::string GetEnunt() const;
	//uint16_t GetId() const;
	//void SetId(const uint16_t& newId);
};

