#include "Visualizer.h"
#include <iostream>

Visualizer::Visualizer(int tileSize, const std::vector<std::vector<int>>& grid, const std::vector<std::vector<int>>& decorationGrid)
	: tileSize(tileSize), grid(grid), decorationGrid(decorationGrid) {}

void Visualizer::Render()
{
	sf::RenderWindow window(sf::VideoMode(grid[0].size() * tileSize + 200, grid.size() * tileSize), "Level Visualizer");
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cerr << "Error loading font!\n";
		return;
	}

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
				if (grid.at(y).at(x) == 0) // Empty
					tile.setFillColor(sf::Color::Black);
				else if (grid.at(y).at(x) == 2) // Room
					tile.setFillColor(sf::Color::Blue);
				else if (grid.at(y).at(x) == 3) // Corridor
					tile.setFillColor(sf::Color::Green);
				else if (grid.at(y).at(x) == 7) // Start point
					tile.setFillColor(sf::Color::White);
				else if (grid.at(y).at(x) == 8) // End point
					tile.setFillColor(sf::Color::Magenta);
				// Color room biomes
				else if (grid.at(y).at(x) == 11) // Forest biome
					tile.setFillColor(sf::Color(54, 100, 54)); // Forest green
				else if (grid.at(y).at(x) == 12) // Cave biome
					tile.setFillColor(sf::Color(105, 105, 105)); // Dark Gray
				else if (grid.at(y).at(x) == 13) // Water biome
					tile.setFillColor(sf::Color(70, 130, 180)); // Steel blue
				else if (grid.at(y).at(x) == 14) // Desert biome
					tile.setFillColor(sf::Color(170, 170, 30)); // Sandy Yellow

				window.draw(tile);
			}
		}

		// Draw decorations
		for (size_t y = 0; y < grid.size(); ++y)
		{
			for (size_t x = 0; x < grid[y].size(); ++x)
			{
				// Skip drawing decorations on spawn and end points
				if (grid.at(y).at(x) == 7 || grid.at(y).at(x) == 8)
				{
					continue;
				}

				if (decorationGrid.at(y).at(x) != 0) // Check non-empty tiles to add decorations
				{
					sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
					tile.setPosition(x * tileSize, y * tileSize);
					// Color decoration grid
					if (decorationGrid.at(y).at(x) == 4) // Treasure chest
						tile.setFillColor(sf::Color::Yellow);
					else if (decorationGrid.at(y).at(x) == 5) // Trap
						tile.setFillColor(sf::Color::Cyan);
					else if (decorationGrid.at(y).at(x) == 6) // Enemy
						tile.setFillColor(sf::Color::Red);

					window.draw(tile);
				}
			}
		}

		// Draw Legend
		float legendX = grid[0].size() * tileSize + 20; // Position legend to the right of grid
		float legendY = 20;

		for (const auto& key : legend)
		{
			const sf::Color& color = key.first;
			const std::string& description = key.second;

			// Draw colored tile in legend
			sf::RectangleShape legendTile(sf::Vector2f(tileSize, tileSize));
			legendTile.setFillColor(color);
			legendTile.setPosition(legendX, legendY);
			window.draw(legendTile);

			// Draw description
			sf::Text text(description, font, 16);
			text.setPosition(legendX + tileSize + 10, legendY);
			text.setFillColor(sf::Color::White);
			window.draw(text);

			// Move to next legend item
			legendY += tileSize + 10;
		}

		window.display();
	}
}
