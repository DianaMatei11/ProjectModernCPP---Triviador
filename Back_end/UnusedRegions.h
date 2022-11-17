#pragma once
#include "Region.h"
#include <unordered_map>
#include <vector>
#include <iostream>
class UnusedRegions
{
private:
	std::vector<Region> m_unusedRegions;
public:
	UnusedRegions();
};

