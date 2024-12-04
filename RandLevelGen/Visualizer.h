#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Visualizer
{
private:
	int tileSize;
	std::vector<std::vector<int>> grid;
	std::vector<std::vector<int>> decorationGrid;
	std::vector<std::pair<sf::Color, std::string>> legend =
	{
	{sf::Color::White, "Spawn Point"},
	{sf::Color::Magenta, "End Point"},
	{sf::Color::Green, "Corridor"},
	{sf::Color::Red, "Enemy"},
	{sf::Color::Cyan, "Trap"},
	{sf::Color::Yellow, "Treasure Chest"},
	{sf::Color(34, 139, 34), "Grassland Biome"},
	{sf::Color(105, 105, 105), "Cave Biome"},
	{sf::Color(70, 130, 180), "Water Biome"},
	{sf::Color(170, 170, 30), "Desert Biome"}
	};

public:
	Visualizer(int tileSize, const std::vector<std::vector<int>>& grid, const std::vector<std::vector<int>>& decorationGrid);
	void Render();
};

