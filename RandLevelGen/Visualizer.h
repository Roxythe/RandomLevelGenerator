#pragma once
#include <vector>
#include <SFML/Graphics.hpp>

class Visualizer
{
	friend class EventHandler;
private:
	enum class UIState { Main, Settings };
	UIState currentState = UIState::Main;
	sf::Event event;
	int tileSize;
	std::vector<std::vector<int>> grid;
	std::vector<std::vector<int>> decorationGrid;
	int roomCount = 10;
	int enemyDensity = 3;
	sf::Font font;
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
	{sf::Color(170, 170, 30), "Desert Biome"},
	{sf::Color::Transparent, "[R] Remake Level"},
	{sf::Color::Transparent, "[S] Open Settings"}
	};

public:
	bool settingsOpen = false;
	Visualizer(int tileSize, const std::vector<std::vector<int>>& grid, const std::vector<std::vector<int>>& decorationGrid);
	void Render();
	void RenderSettings(sf::RenderWindow& window);
	void LoadFont(sf::Font& font);
	void handleEvents(sf::RenderWindow& window);
	void handleMainEvents(sf::RenderWindow& window, const sf::Event& event);
	void handleSettingsEvents(sf::RenderWindow& window, const sf::Event& event);
	void regenerateLevel();
};

