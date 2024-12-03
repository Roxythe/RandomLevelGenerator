#include "Visualizer.h"

Visualizer::Visualizer(int tileSize, const std::vector<std::vector<int>>& grid, const std::vector<std::vector<int>>& decorationGrid)
	: tileSize(tileSize), grid(grid), decorationGrid(decorationGrid) {}

void Visualizer::Render()
{
	sf::RenderWindow window(sf::VideoMode(grid[0].size() * tileSize, grid.size() * tileSize), "Level Visualizer");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();

		// Draw Grid
		for (size_t y = 0; y < grid.size(); ++y)
		{
			for (size_t x = 0; x < grid[y].size(); ++x)
			{
				sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
				tile.setPosition(x * tileSize, y * tileSize);

				// Color basic frame based on cell value
				if (grid.at(y).at(x) == 0)
					tile.setFillColor(sf::Color::Black); // Empty
				else if (grid.at(y).at(x) == 2) 
					tile.setFillColor(sf::Color::Blue); // Room
				else if (grid.at(y).at(x) == 3) 
					tile.setFillColor(sf::Color::Green); // Corridor
				// Color room biomes
				else if (grid.at(y).at(x) == 11)
					tile.setFillColor(sf::Color(54, 100, 54)); // Forest biome/Forest green
				else if (grid.at(y).at(x) == 12)
					tile.setFillColor(sf::Color(105, 105, 105)); // Cave biome/Gray
				else if (grid.at(y).at(x) == 13)
					tile.setFillColor(sf::Color(70, 130, 180)); // Water biome/Steel blue

				window.draw(tile);

				// Color decoration grid
				if (decorationGrid.at(y).at(x) == 4)
					tile.setFillColor(sf::Color::Yellow); // Treasure chest
				else if (decorationGrid.at(y).at(x) == 5)
					tile.setFillColor(sf::Color::Cyan); // Trap
				else if (decorationGrid.at(y).at(x) == 6)
					tile.setFillColor(sf::Color::Red); // Enemy

				window.draw(tile);
			}
		}

		window.display();
	}
}
