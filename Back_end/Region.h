#pragma once
#include <string>
#include <iostream>

class Region
{
private:
	int m_scores;
	std::string m_name;
	bool m_isBase;
public:
	Region() = default;
	Region(std::string name="Undefined", int scores = 100,bool isBase=false);
	~Region();
	std::string GetName();
	int GetScores();
	void SetScores(int scores);
	bool IsBase();
	void SetBase();
	friend std::ostream& operator <<(std::ostream& out, const Region& region);
};

