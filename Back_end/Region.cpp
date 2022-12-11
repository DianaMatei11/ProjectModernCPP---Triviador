#include "Region.h"


Region::Region(int id, int scores, bool isBase, std::shared_ptr<User> owner)
	:m_id{ id }, m_scores{ scores }, m_isBase{ isBase },m_owner{owner}
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
	if (m_owner!=nullptr)
		return true;
	return false;
}

User& Region::GetOwner()
{
	return *m_owner;
}

void Region::SetOwner(const User& user)
{
	m_owner = std::make_shared<User>(user);
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
