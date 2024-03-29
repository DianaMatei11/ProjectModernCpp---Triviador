#pragma once
#include <string>
#include <iostream>
#include <optional>
#include <vector>
#include "User.h"
#include <memory>

using coord = std::pair<int, int>;

class Region
{
private:
	int m_scores;
	std::shared_ptr<User> m_owner;
	int m_id;
	bool m_isBase;
	std::vector<coord> m_vectorCoord;
public:
	Region() = default;
	Region(int id, int scores = 100,bool isBase=false, std::shared_ptr<User> owner=nullptr);
	//~Region();
	int GetID();
	bool HasOwner();
	User& GetOwner();
	void SetOwner(const User& user);
	void SetCoord(coord& c1, coord& c2, coord& c3, coord& c4, coord& c5);
	const std::vector<coord>& GetCoord();
	int GetScores();
	void SetScores(int scores);
	bool IsBase();
	void SetBase();
	friend std::ostream& operator <<(std::ostream& out, const Region& region);
	~Region() = default;
};

