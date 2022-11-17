#include "Region.h"

Region::Region(std::string name, int scores,bool isBase)
	:m_name{ name }, m_scores{ scores },m_isBase{isBase}
{
}

Region::~Region()
{
}

std::string Region::GetName()
{
	return m_name;
}

int Region::GetScores()
{
	return m_scores;
}

void Region::SetScores(int scores)
{
	m_scores = scores;
}

bool Region::IsBase()
{
	return m_isBase;
}

void Region::SetBase()
{
	m_isBase = true;
	m_scores = 300;
}

std::ostream& operator<<(std::ostream& out, const Region& region)
{
	out << region.m_name<<": ";
	out << region.m_scores;
	return out;
}
