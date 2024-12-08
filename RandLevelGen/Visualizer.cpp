#include "Visualizer.h"
#include "LevelGenerator.h"
#include <iostream>

Visualizer::Visualizer(int tileSize, const std::vector<std::vector<int>>& grid, const std::vector<std::vector<int>>& decorationGrid)
	: tileSize(tileSize), grid(grid), decorationGrid(decorationGrid) {
}

void Visualizer::Render()
{
	sf::RenderWindow window(sf::VideoMode(grid[0].size() * tileSize + 200, grid.size() * tileSize), "Level Visualizer");
	LoadFont(font);

	while (window.isOpen())
	{
		handleEvents(window);

		window.clear();

		if (currentState == UIState::Settings)
		{
			RenderSettings(window);
		}
		else
		{
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

			if (settingsOpen)
			{
				RenderSettings(window);
			}
		}

		window.display();
	}
}

void Visualizer::RenderSettings(sf::RenderWindow& window)
{
	LoadFont(font);

	// Get main window size
	sf::Vector2u windowSize = window.getSize();

	// Calculate center positions
	float menuWidth = 400;
	float menuHeight = 300;
	float menuX = (windowSize.x - menuWidth) / 2;
	float menuY = (windowSize.y - menuHeight) / 2;

	// Background for the settings menu
	sf::RectangleShape menuBackground(sf::Vector2f(menuWidth, menuHeight));
	menuBackground.setFillColor(sf::Color(50, 50, 50, 200));
	menuBackground.setPosition(menuX, menuY);
	window.draw(menuBackground);

	// Add "Settings" label
	sf::Text settingsLabel("Settings", font, 24); // Text size 24
	settingsLabel.setFillColor(sf::Color::White);
	settingsLabel.setPosition(menuX + (menuWidth - settingsLabel.getLocalBounds().width) / 2, menuY + 10); // Centered at the top
	window.draw(settingsLabel);

	// Room Count Slider
	float sliderX = menuX + 50; // Offset from menu edge
	float sliderBarY = menuY + 80;

	sf::RectangleShape sliderBar(sf::Vector2f(200, 10));
	sliderBar.setFillColor(sf::Color(150, 150, 150));
	sliderBar.setPosition(sliderX, sliderBarY);
	window.draw(sliderBar);

	sf::RectangleShape slider(sf::Vector2f(20, 20));
	slider.setFillColor(sf::Color::White);
	slider.setPosition(sliderX + (roomCount - 5) * 20, sliderBarY - 5); // Map roomCount to slider position
	window.draw(slider);

	// Room Count Label
	sf::Text roomCountLabel("Room Count: " + std::to_string(roomCount), font, 16);
	roomCountLabel.setPosition(sliderX, sliderBarY - 30); // Place above slider
	roomCountLabel.setFillColor(sf::Color::White);
	window.draw(roomCountLabel);

	// Enemy Density Slider
	float densityBarY = sliderBarY + 60;

	sf::RectangleShape densitySliderBar(sf::Vector2f(200, 10));
	densitySliderBar.setFillColor(sf::Color(150, 150, 150));
	densitySliderBar.setPosition(sliderX, densityBarY);
	window.draw(densitySliderBar);

	sf::RectangleShape densitySlider(sf::Vector2f(20, 20));
	densitySlider.setFillColor(sf::Color::White);
	densitySlider.setPosition(sliderX + (enemyDensity - 1) * 20, densityBarY - 5); // Map enemyDensity to slider position
	window.draw(densitySlider);

	sf::Text densityLabel("Enemy Density: " + std::to_string(enemyDensity), font, 16);
	densityLabel.setPosition(sliderX, densityBarY - 30); // Place above slider
	densityLabel.setFillColor(sf::Color::White);
	window.draw(densityLabel);
}

void Visualizer::LoadFont(sf::Font& font)
{
	if (!font.loadFromFile("arial.ttf"))
	{
		std::cerr << "Error loading font!\n";
	}
}

void Visualizer::handleEvents(sf::RenderWindow& window)
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}

		if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::S)
		{
			currentState = (currentState == UIState::Main) ? UIState::Settings : UIState::Main;
		}

		if (currentState == UIState::Main)
		{
			handleMainEvents(window, event);
		}
		else if (currentState == UIState::Settings)
		{
			handleSettingsEvents(window, event);
		}
	}
}

void Visualizer::handleMainEvents(sf::RenderWindow& window, const sf::Event& event)
{
	if (event.type == sf::Event::KeyPressed)
	{
		// Regenerate level when R is pressed
		if (event.key.code == sf::Keyboard::R)
		{
			std::cout << "Regenerate key pressed!" << std::endl;
			regenerateLevel(); // Call the regeneration logic
		}
	}
}

void Visualizer::handleSettingsEvents(sf::RenderWindow& window, const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
	{
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);

		// Get the position and dimensions of the sliders
		float menuWidth = 400;
		float menuHeight = 300;
		float menuX = (window.getSize().x - menuWidth) / 2;
		float menuY = (window.getSize().y - menuHeight) / 2;

		float sliderX = menuX + 50;      // Slider X position
		float roomCountSliderY = menuY + 70; // Room count slider Y position
		float densitySliderY = roomCountSliderY + 80; // Enemy density slider Y position

		// Check for interaction with Room Count Slider
		if (mousePos.x >= sliderX && mousePos.x <= sliderX + 200 &&
			mousePos.y >= roomCountSliderY - 5 && mousePos.y <= roomCountSliderY + 15)
		{
			// Map mouse position to slider value
			roomCount = ((mousePos.x - sliderX) / 20) + 5; // Slider range: 5-15
			roomCount = std::max(5, std::min(15, roomCount)); // Clamp value
			std::cout << "Room count updated: " << roomCount << std::endl;
		}

		// Check for interaction with Enemy Density Slider
		if (mousePos.x >= sliderX && mousePos.x <= sliderX + 200 &&
			mousePos.y >= densitySliderY - 5 && mousePos.y <= densitySliderY + 15)
		{
			// Map mouse position to slider value
			enemyDensity = ((mousePos.x - sliderX) / 20) + 1; // Slider range: 1-10
			enemyDensity = std::max(1, std::min(10, enemyDensity)); // Clamp value
			std::cout << "Enemy density updated: " << enemyDensity << std::endl;
		}
	}
}

void Visualizer::regenerateLevel()
{
	LevelGenerator generator; // Generate new level
	generator.GenerateLevel(grid[0].size(), grid.size(), roomCount, enemyDensity); // Use current room count

	grid = generator.GetGrid();
	decorationGrid = generator.GetDecorationGrid();

	std::cout << "Level regenerated with Room Count: " << roomCount
		<< " and Enemy Density: " << enemyDensity << std::endl;
}
