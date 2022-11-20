#include "UnusedRegions.h"

UnusedRegions::UnusedRegions()
{
	m_unusedRegions.insert({ "Cluj", Region("Cluj") });
	m_unusedRegions.insert({ "Brasov", Region("Brasov") });
	m_unusedRegions.insert({ "Craiova", Region("Craiova") });
	m_unusedRegions.insert({ "Braila", Region("Braila") });
	m_unusedRegions.insert({ "Constanta", Region("Constanta") });
	m_unusedRegions.insert({ "Iasi", Region("Iasi") });
	m_unusedRegions.insert({ "Sibiu", Region("Sibiu") });
	m_unusedRegions.insert({ "Suceava", Region("Suceava") });
	m_unusedRegions.insert({ "Maramures", Region("Maramures") });
}

Region UnusedRegions::PickRegion(std::string name)
{
	auto node = m_unusedRegions.extract(name);
	if (node)
	{
		return std::move(node.mapped());
	}
	else
	{
		throw std::exception{ "The region was not found" };
	}
}


