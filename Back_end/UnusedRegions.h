#pragma once
#include "Region.h"
#include <unordered_map>
#include <vector>
#include <iostream>

class UnusedRegions
{
private:
	std::unordered_map<std::string ,Region> m_unusedRegions;
public:
	UnusedRegions();
	Region PickRegion(std::string name);
};

