#include "Visualizer.h"

Visualizer::Visualizer(int tileSize, const std::vector<std::vector<int>>& grid)
	: tileSize(tileSize), grid(grid) {}

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

				// Color based on cell value
				if (grid.at(y).at(x) == 0)
					tile.setFillColor(sf::Color::Black); // Empty
				else if (grid.at(y).at(x) == 2) 
					tile.setFillColor(sf::Color::Blue); // Room
				else if (grid.at(y).at(x) == 3) 
					tile.setFillColor(sf::Color::Green); // Corridor

				window.draw(tile);
			}
		}

		window.display();
	}
}
