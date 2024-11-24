#include <iostream>
#include "LevelGenerator.h"
#include "FileExporter.h"
#include "Visualizer.h"

int main()
{
	levelGenerator generator;

	// Generate a level
	generator.generateLevel(20, 20, 5); // Width 20, Height 20, 5 rooms

	// Export the level
	FileExporter::exportToText(generator.getGrid(), "level.txt");
	FileExporter::exportToJson(generator.getGrid(), "level.json");

	// Visualize level
	Visualizer visualizer(20, generator.getGrid()); // 20x20 grid
	visualizer.render();

	std::cout << "Level generated and exported successfully!" << std::endl;
	return 0;
}