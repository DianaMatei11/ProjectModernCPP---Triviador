#pragma once
#include <string>
#include <iostream>
#include <optional>
#include <vector>
#include "User.h"
#include <memory>
#include <tuple>

using coord = std::tuple<float, float,float,float>;

class Region
{
private:
	int m_scores;
	std::string m_owner;
	int m_id;
	bool m_isBase;
	coord m_vectorCoord;

public:
	Region() = default;
	Region(int id,coord vectorCoord, int scores = 100,bool isBase=false, std::string owner="");
	//~Region();
	int GetID();
	bool HasOwner();
	std::string GetOwner();
	void SetOwner(const std::string& user);
	const coord& GetCoord();
	int GetScores();
	void SetScores(int scores);
	bool IsBase();
	void SetBase();
	friend std::ostream& operator <<(std::ostream& out, const Region& region);
	~Region() = default;
};

