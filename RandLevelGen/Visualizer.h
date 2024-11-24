#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Visualizer
{
private:
	int tileSize;
	std::vector<std::vector<int>> grid;

public:
	Visualizer(int tileSize, const std::vector<std::vector<int>>& grid);
	void Render();
};

