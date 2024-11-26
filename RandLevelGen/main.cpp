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
	generator.GenerateLevel(20, 20, 5); // Width 20, Height 20, 5 rooms
	generator.PrintGrid(); // Print grid to verify

	// Export the level
	FileExporter::ExportToText(generator.GetGrid(), "level.txt");
	FileExporter::ExportToJson(generator.GetGrid(), "level.json");

	// Visualize level
	Visualizer visualizer(20, generator.GetGrid()); // 20x20 grid
	visualizer.Render();

	std::cout << "Level generated and exported successfully!" << std::endl;
	return 0;
}