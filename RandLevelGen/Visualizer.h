#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Visualizer
{
private:
	int tileSize;
	std::vector<std::vector<int>> grid;
	std::vector<std::vector<int>> decorationGrid;

public:
	Visualizer(int tileSize, const std::vector<std::vector<int>>& grid, const std::vector<std::vector<int>>& decorationGrid);
	void Render();
};

