#pragma once
#include "Region.h"
#include <vector>
#include <iostream>
#include <crow.h>

class Map
{
private:
	std::vector<std::shared_ptr<Region>> m_unusedRegions;
	std::vector<std::shared_ptr<Region>> m_regions;
	int m_w,m_h;
public:
	Map() = default;
	Map(int nrPlayers);
	std::shared_ptr <Region> PickRegion(int id);
	std::shared_ptr <Region> GetRegion(int id);
	std::vector<std::shared_ptr<Region>>& GetUnusedRegions();
	std::vector<std::shared_ptr<Region>>& GetRegions();
	void GetNeighbours(int id,std::vector<std::shared_ptr<Region>>& neigh);
	void RouteForCoordinates();
	~Map() = default;
};

