#include "Intrebare.h"

Intrebare::Intrebare(const std::string& enunt):
	m_enunt{enunt}
{
}

int Intrebare::GetRandomNumber(const int x, const int y)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(x,y);
	return distr(eng);
}

void Intrebare::SetEnunt(const std::string& enunt)
{
	m_enunt = enunt;
}

std::string Intrebare::GetEnunt() const
{
	return m_enunt;
}

//uint16_t Intrebare::GetId() const
//{
//	return m_id;
//}
//
//void Intrebare::SetId(const uint16_t& newId)
//{
//	m_id = newId;
//}
