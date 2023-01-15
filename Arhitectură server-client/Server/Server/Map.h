#pragma once
#include "Region.h"
#include <vector>
#include <iostream>
#include <crow.h>
#include <unordered_set>

class Map
{
private:
	std::unordered_set<int> m_unusedRegions;
	std::vector<std::shared_ptr<Region>> m_regions;
	int m_w,m_h;
public:
	//
	Map() = default;
	void buildMap(int nrPlayers);
	
	bool PickRegion(int id);
	std::shared_ptr <Region> GetRegion(int id);
	std::unordered_set<int>& GetUnusedRegions();
	std::vector<std::shared_ptr<Region>>& GetRegions();
	void GetNeighbours(int id,std::vector<std::shared_ptr<Region>>& neigh);
	void RouteForCoordinates(crow::SimpleApp& app);
	~Map() = default;
};

