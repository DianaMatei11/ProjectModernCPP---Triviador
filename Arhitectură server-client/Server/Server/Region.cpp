#include "Region.h"

Region::Region(int id,coord vectorCoord, int scores, bool isBase, std::string owner)
	:m_id{ id }, m_vectorCoord{ vectorCoord }, m_scores{ scores }, m_isBase{ isBase }, m_owner{ owner }
{
}

//Region::~Region()
//{
//}

int Region::GetID()
{
	return m_id;
}

bool Region::HasOwner()
{
	if (m_owner.empty())return false;
	return true;
}

std::string Region::GetOwner()
{
	return m_owner;
}

void Region::SetOwner(const std::string& user)
{
	m_owner = user;
}

const coord& Region::GetCoord()
{
	return m_vectorCoord;
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
	out << region.m_id<<": ";

	out << region.m_scores;
	return out;
}
