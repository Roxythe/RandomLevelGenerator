#include "FileExporter.h"

void FileExporter::ExportToText(const std::vector<std::vector<int>>& grid, const std::string& filename)
{
	std::ofstream file(filename);
	for (const auto& row : grid)
	{
		for (int cell : row)
		{
			file << cell << " ";
		}
		file << "\n";
	}
}

void FileExporter::ExportToJson(const std::vector<std::vector<int>>& grid, const std::string& filename)
{
	nlohmann::json j;
	for (const auto& row : grid)
	{
		j.push_back(row);
	}

	std::ofstream file(filename);
	file << j.dump(4); // Pretty print with 4 spaces
}
