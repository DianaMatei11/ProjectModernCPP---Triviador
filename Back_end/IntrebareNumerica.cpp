#include "IntrebareNumerica.h"

IntrebareNumerica::IntrebareNumerica(std::string enunt, int raspuns)
{
	m_enunt = enunt;
	m_raspuns = raspuns;
}

std::string IntrebareNumerica::GetEnunt() const
{
	return m_enunt;
}

int IntrebareNumerica::GetRaspuns() const
{
	return m_raspuns;
}
