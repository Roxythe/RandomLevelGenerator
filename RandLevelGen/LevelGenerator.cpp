#include "LevelGenerator.h"
#include <iostream>

void LevelGenerator::GenerateLevel(int width, int height, int roomCount)
{
	grid = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));

	// Generate rooms
	for (int i = 0; i < roomCount; ++i)
	{
		int roomWidth = std::min(rand() % 5 + 3, width);
		int roomHeight = std::min(rand() % 5 + 3, height);
		int roomX = rand() % (width - roomWidth);
		int roomY = rand() % (height - roomHeight);

		Room room(roomX, roomY, roomWidth, roomHeight);
		if (CanPlaceRoom(room))
		{
			PlaceRoom(room);
			rooms.push_back(room);
		}
	}

	// Connect rooms
	for (size_t i = 1; i < rooms.size(); ++i)
	{
		CreateCorridor(rooms[i - 1], rooms[i]);
	}
}

const std::vector<std::vector<int>>& LevelGenerator::GetGrid() const
{
	return grid;
}

void LevelGenerator::PlaceRoom(const Room& room)
{
	for (int y = room.y; y < room.y + room.height; ++y)
	{
		for (int x = room.x; x < room.x + room.width; ++x)
		{
			grid.at(y).at(x) += 2; // Mark as a room
		}
	}
}

void LevelGenerator::CreateCorridor(const Room& room1, const Room& room2)
{
	int x1 = room1.x + room1.width / 2;
	int y1 = room1.y + room1.height / 2;
	int x2 = room2.x + room2.width / 2;
	int y2 = room2.y + room2.height / 2;

	// Horizontal corridor
	for (int x = std::min(x1, x2); x <= std::max(x1, x2); ++x)
	{
		if (grid.at(y1).at(x) == 0) grid.at(y1).at(x) = 3;
	}

	// Vertical corridor
	for (int y = std::min(y1, y2); y <= std::max(y1, y2); ++y)
	{
		if (grid.at(y).at(x2) == 0) grid.at(y).at(x2) = 3;
	}
}

bool LevelGenerator::CanPlaceRoom(const Room& room)
{
	// Check if the room is within grid boundary
	if (room.x < 0 || room.y < 0 ||
		room.x + room.width > grid[0].size() ||
		room.y + room.height > grid.size())
	{
		return false; // Out of bounds
	}

	for (int y = room.y; y < room.y + room.height; ++y)
	{
		for (int x = room.x; x < room.x + room.width; ++x)
		{
			if (grid.at(y).at(x) != 0)
			{
				return false; // Overlap check
			}
		}	
	}
	return true; // Room is safe to place
}

void LevelGenerator::PrintGrid() const
{
	for (const auto& row : grid)
	{
		for (int cell : row)
		{
			std::cout << cell << " ";
		}
		std::cout << "\n";
	}
}


//// Test Grid
//for (int i = 0; i < roomCount; ++i)
//{
//	int roomX = rand() % (width - 3);
//	int roomY = rand() % (height - 3);
//	int roomWidth = 3;
//	int roomHeight = 3;
//
//	// Create and place room
//	Room room(roomX, roomY, roomWidth, roomHeight);
//	if (CanPlaceRoom(room))
//	{
//		PlaceRoom(room);
//	}
//}