#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>

class FileExporter
{
public:
	static void ExportToText(const std::vector<std::vector<int>>& grid, const std::string& filename);
	static void ExportToJson(const std::vector<std::vector<int>>& grid, const std::string& filename);
};

