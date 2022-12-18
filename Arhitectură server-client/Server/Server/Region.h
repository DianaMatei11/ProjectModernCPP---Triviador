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
	std::shared_ptr<User> m_owner;
	int m_id;
	bool m_isBase;
	coord m_vectorCoord;

public:
	Region() = default;
	Region(int id,coord vectorCoord, int scores = 100,bool isBase=false, std::shared_ptr<User> owner=nullptr);
	//~Region();
	int GetID();
	bool HasOwner();
	User& GetOwner();
	void SetOwner(const User& user);
	const coord& GetCoord();
	int GetScores();
	void SetScores(int scores);
	bool IsBase();
	void SetBase();
	friend std::ostream& operator <<(std::ostream& out, const Region& region);
	~Region() = default;
};

