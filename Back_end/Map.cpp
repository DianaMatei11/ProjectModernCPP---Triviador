#include "Map.h"

Map::Map(int nrPlayers)
{
	int nrRegions;
	if (nrPlayers == 2)
		nrRegions = 9;
	if (nrPlayers == 3)
		nrRegions = 15;
	if (nrPlayers == 4)
		nrRegions = 24;
	for (int i = 1; i <= nrRegions; i++)
	{
		m_unusedRegions.emplace_back(std::make_shared<Region>(i));
	}
}

std::shared_ptr<Region> Map::PickRegion(int id)
{
	std::shared_ptr<Region> region = m_unusedRegions[id - 1];
	auto it = std::find(m_unusedRegions.begin(), m_unusedRegions.end(), region);
	if (it != m_unusedRegions.end())
	{
		std::cout << "Regiunea exista!\n";
		m_unusedRegions.erase(it);
		return region;
	}
	else
	{
		throw std::exception{ "The region was not found" };
	}
}


std::vector<std::shared_ptr<Region>>& Map::GetUnusedRegions()
{
	return m_unusedRegions;
}

