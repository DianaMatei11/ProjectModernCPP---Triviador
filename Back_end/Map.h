#pragma once
#include "Region.h"
#include <vector>
#include <iostream>
class Map
{
private:
	std::vector<std::shared_ptr<Region>> m_unusedRegions;
public:
	Map() = default;
	Map(int nrPlayers);
	std::shared_ptr <Region> PickRegion(int id);
	std::vector<std::shared_ptr<Region>>& GetUnusedRegions();
	~Map() = default;
};

