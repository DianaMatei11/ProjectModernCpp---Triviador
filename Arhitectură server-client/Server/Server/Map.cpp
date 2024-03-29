#include "Map.h"

void Map::buildMap(int nrPlayers)
{
	if (m_regions.size() != 0)
	{
		return;
	}

	if (nrPlayers == 2)
	{
		m_w = 3;
		m_h = 3;
	}
	if (nrPlayers == 3)
	{
		m_w = 5;
		m_h = 3;
	}
	if (nrPlayers == 4)
	{
		m_w = 6;
		m_h = 4;
	}
	float h = 350 / m_h;
	float w = 600 / m_w;
	float initialh = 0;
	float initialw = 0;
	coord tuplu;
	for (int i = 0; i < m_h; i++)
	{
		initialw = 0;
		for (int j = 0; j < m_w; j++)
		{

			tuplu = std::make_tuple(100 + initialw, 200 + initialh, w, h);
			m_unusedRegions.insert(i * m_w + j + 1);
			m_regions.emplace_back(std::make_shared<Region>(i * m_w + j + 1, tuplu));
			initialw += w;
		}
		initialh += h;
	}
}

bool Map::PickRegion(int id)
{
	if (m_unusedRegions.find(id) != m_unusedRegions.end())
	{
		//std::cout << "Regiunea exista!\n";
		m_unusedRegions.erase(id);
		return true;
	}
	else
	{
		return false;
		//throw std::exception{ "The region was not found" };
		//std::cout << "The region was not found\n";
	}
}

std::shared_ptr<Region> Map::GetRegion(int id)
{
	std::shared_ptr<Region>& region = m_regions[id - 1];
	auto it = std::find(m_regions.begin(), m_regions.end(), region);
	if (it != m_regions.end())
	{
		return (*it);
	}
	else
	{
		//throw std::exception{ "The region was not found" };
		std::cout << "The region was not found.\n";
	}
}


std::unordered_set<int>& Map::GetUnusedRegions()
{
	return m_unusedRegions;
}

std::vector<std::shared_ptr<Region>>& Map::GetRegions()
{
	return m_regions;
}

void Map::GetNeighbours(int id, std::vector<std::shared_ptr<Region>>& neigh)
{
	std::vector<std::shared_ptr<Region>> vecini;
	if (id == 1)
	{
		vecini.emplace_back(GetRegion(2));
		vecini.emplace_back(GetRegion(1 + m_w));
		vecini.emplace_back(GetRegion(1 + m_w + 1));
		neigh = vecini;
		return;
	}
	if (id == m_w)
	{
		vecini.emplace_back(GetRegion(m_w - 1));
		vecini.emplace_back(GetRegion(m_w + m_w));
		vecini.emplace_back(GetRegion(m_w + m_w - 1));
		neigh = vecini;
		return;
	}
	if (id == m_w * m_h - m_w + 1)
	{
		vecini.emplace_back(GetRegion(m_w * m_h - 2 * m_w + 1));
		vecini.emplace_back(GetRegion(m_w * m_h - 2 * m_w + 2));
		vecini.emplace_back(GetRegion(m_w * m_h - m_w + 2));
		neigh = vecini;
		return;
	}
	if (id == m_w * m_h)
	{
		vecini.emplace_back(GetRegion(m_w * m_h - 1));
		vecini.emplace_back(GetRegion(m_w * m_h - m_w));
		vecini.emplace_back(GetRegion(m_w * m_h - m_w - 1));
		neigh = vecini;
		return;
	}

	if ((id - 1) % m_w == 0)
	{
		vecini.emplace_back(GetRegion(id - m_w));
		vecini.emplace_back(GetRegion(id - m_w + 1));
		vecini.emplace_back(GetRegion(id + 1));
		vecini.emplace_back(GetRegion(id + m_w));
		vecini.emplace_back(GetRegion(id + m_w + 1));
		neigh = vecini;
		return;
	}

	if (id % m_w == 0)
	{
		vecini.emplace_back(GetRegion(id - m_w));
		vecini.emplace_back(GetRegion(id - m_w - 1));
		vecini.emplace_back(GetRegion(id - 1));
		vecini.emplace_back(GetRegion(id + m_w));
		vecini.emplace_back(GetRegion(id + m_w - 1));
		neigh = vecini;
		return;
	}

	if (id < m_w)
	{
		vecini.emplace_back(GetRegion(id - 1));
		vecini.emplace_back(GetRegion(id + 1));
		vecini.emplace_back(GetRegion(id + m_w));
		vecini.emplace_back(GetRegion(id + m_w + 1));
		vecini.emplace_back(GetRegion(id + m_w - 1));
		neigh = vecini;
		return;
	}

	if (id > m_w * m_h - m_w)
	{
		vecini.emplace_back(GetRegion(id - 1));
		vecini.emplace_back(GetRegion(id + 1));
		vecini.emplace_back(GetRegion(id - m_w));
		vecini.emplace_back(GetRegion(id - m_w + 1));
		vecini.emplace_back(GetRegion(id - m_w - 1));
		neigh = vecini;
		return;
	}
	else
	{
		vecini.emplace_back(GetRegion(id - 1));
		vecini.emplace_back(GetRegion(id + 1));
		vecini.emplace_back(GetRegion(id - m_w));
		vecini.emplace_back(GetRegion(id - m_w + 1));
		vecini.emplace_back(GetRegion(id - m_w - 1));
		vecini.emplace_back(GetRegion(id + m_w - 1));
		vecini.emplace_back(GetRegion(id + m_w + 1));
		vecini.emplace_back(GetRegion(id + m_w));
		neigh = vecini;
		return;
	}
}

void Map::RouteForCoordinates(crow::SimpleApp& app)
{

	CROW_ROUTE(app, "/coordinates")([&regions = m_regions]() {
		std::vector<crow::json::wvalue> coordinates;
	for (const auto& region : regions) {
		coord coord = (*region).GetCoord();
		coordinates.push_back(crow::json::wvalue{
			{"index", region->GetID()},
			{ "x", std::get<0>(coord)},
			{ "y", std::get<1>(coord) },
			{ "width", std::get<2>(coord) },
			{ "height", std::get<3>(coord) }
			});
	}
	return crow::json::wvalue{ coordinates };
		});
}

