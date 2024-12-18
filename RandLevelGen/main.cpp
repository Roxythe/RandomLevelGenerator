#include <iostream>
#include "LevelGenerator.h"
#include "FileExporter.h"
#include "Visualizer.h"
#include <ctime>

int main()
{
	srand(static_cast<unsigned>(time(0))); // Seed generator with current time
	LevelGenerator generator;

	// Generate a level
	generator.GenerateLevel(80, 40, 10, 5); // Width 30, Height 30, rooms 10 max, enemy density 5
	generator.PrintGrid(); // Print grid to verify

	// Export the level
	FileExporter::ExportToText(generator.GetGrid(), "level.txt");
	FileExporter::ExportToJson(generator.GetGrid(), "level.json");

	// Visualize level
	Visualizer visualizer(20, generator.GetGrid(), generator.GetDecorationGrid()); // Scale visualizer size and generate grids
	visualizer.Render();

	std::cout << "Level generated and exported successfully!" << std::endl;
	return 0;
}