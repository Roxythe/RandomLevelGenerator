#include "LevelGenerator.h"
#include <iostream>
#include <random>
#include "GraphUtils.h"

void LevelGenerator::GenerateLevel(int width, int height, int roomCount)
{
	// Random engine seeded with current time
	std::mt19937 rng(static_cast<unsigned>(std::time(0)));
	std::uniform_int_distribution<int> biomeDist(1, 4); // Biomes

	// Distributions
	std::uniform_int_distribution<int> widthDist(3, 7); // Room width: 3-7
	std::uniform_int_distribution<int> heightDist(3, 7); // Room height: 3-7
	std::uniform_int_distribution<int> xDist(0, width - 1); // X position
	std::uniform_int_distribution<int> yDist(0, height - 1); // Y position

	grid = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
	decorationGrid = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
	rooms.clear();

	// Generate rooms
	for (int i = 0; i < roomCount; ++i)
	{
		int roomWidth = widthDist(rng);
		int roomHeight = heightDist(rng);
		int roomX = xDist(rng) % (width - roomWidth + 1);
		int roomY = yDist(rng) % (height - roomHeight + 1);
		int roomBiome = biomeDist(rng); // Assign random biome

		Room room(roomX, roomY, roomWidth, roomHeight, roomBiome);
		if (CanPlaceRoom(room))
		{
			PlaceRoom(room);
			DecorateRoom(room);
			rooms.push_back(room);
		}
	}

	std::vector<Edge> _edges = GenerateEdges(rooms); // Generate edges between rooms
	std::vector<Edge> _mst = GenerateMST(_edges, rooms.size()); // Generate MST
	ConnectRooms(_mst); // Connect rooms
	AddExtraConnections(_edges, _mst, 2, rooms); // Add 2 extra connections between rooms
	PlaceSpawnAndEndPoints();
}

const std::vector<std::vector<int>>& LevelGenerator::GetGrid() const
{
	return grid;
}

const std::vector<std::vector<int>>& LevelGenerator::GetDecorationGrid() const
{
	return decorationGrid;
}

const std::pair<int, int>& LevelGenerator::GetSpawnPoint() const
{
	return spawnPoint;
}

const std::pair<int, int>& LevelGenerator::GetEndPoint() const
{
	return endPoint;
}

void LevelGenerator::PlaceSpawnAndEndPoints()
{
	std::mt19937 rng(static_cast<unsigned>(std::time(0)));
	std::uniform_int_distribution<int> roomDist(0, rooms.size() - 1);

	// Randomly chosen spawn room
	int spawnRoomIndex = roomDist(rng);
	const Room& spawnRoom = rooms[spawnRoomIndex];
	
	// Choose a random tile within spawn room
	std::uniform_int_distribution<int> xDist(spawnRoom.x, spawnRoom.x + spawnRoom.width - 1);
	std::uniform_int_distribution<int> yDist(spawnRoom.y, spawnRoom.y + spawnRoom.height - 1);
	spawnPoint = { xDist(rng), yDist(rng) };
	grid[spawnPoint.second][spawnPoint.first] = 7; // Mark as spawn point

	// Choose a different random room for end point
	int endRoomIndex;
	const Room* endRoom = nullptr;
	int minDistance = 30;

	do 
	{
		endRoomIndex = roomDist(rng); 
		
		// Ensure end room is different from spawn room
		if (endRoomIndex != spawnRoomIndex)
		{
			endRoom = &rooms[endRoomIndex];
			xDist = std::uniform_int_distribution<int>(endRoom->x, endRoom->x + endRoom->width - 1);
			yDist = std::uniform_int_distribution<int>(endRoom->y, endRoom->y + endRoom->height - 1);
			endPoint = { xDist(rng), yDist(rng) };
		}
	} 
	while (endRoomIndex == spawnRoomIndex || // Ensure different rooms
		std::abs(spawnPoint.first - endPoint.first) + std::abs(spawnPoint.second - endPoint.second) < minDistance);

	grid[endPoint.second][endPoint.first] = 8; // Mark as end point

	std::cout << "Spawn Point: (" << spawnPoint.first << ", " << spawnPoint.second << ")\n";
	std::cout << "End Point: (" << endPoint.first << ", " << endPoint.second << ")\n";
}

void LevelGenerator::PlaceRoom(const Room& room)
{
	for (int y = room.y; y < room.y + room.height; ++y)
	{
		for (int x = room.x; x < room.x + room.width; ++x)
		{
			grid.at(y).at(x) += room.biome + 10; // Mark as a room
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
	// Check if the room is within grid boundary, account for 1 tile space buffer
	if (room.x < 1 || room.y < 1 ||
		room.x + room.width + 1 > grid[0].size() ||
		room.y + room.height + 1 > grid.size())
	{
		return false; // Out of bounds
	}

	// Check for collisions within room area and its buffer zone
	for (int y = room.y - 1; y < room.y + room.height; ++y)
	{
		for (int x = room.x - 1; x < room.x + room.width; ++x)
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

void LevelGenerator::DecorateRoom(const Room& room)
{
	std::mt19937 rng(static_cast<unsigned>(std::time(0)));
	std::uniform_int_distribution<int> decorationDist(0, 20); // 0-10 scale for density

	int maxDecorations = (room.width * room.height) / 4; // Allow decoration in 1/4 of room tiles
	int decorationCount = 0; // Track decoration count
	bool chestPlaced = false; // Track if room has chest

	for (int y = room.y; y < room.y + room.height; ++y)
	{
		for (int x = room.x; x < room.x + room.width; ++x)
		{
			if (grid.at(y).at(x) >= 11 && grid.at(y).at(x) <= 14 && decorationCount < maxDecorations) // Only decorate inside biomes
			{
				if (!chestPlaced && (x == room.x || x == room.x + room.width - 1 || // Vertical walls
					y == room.y || y == room.y + room.height - 1)) // Horizontal walls
				{
					if (decorationDist(rng) < 2)
					{
						decorationGrid.at(y).at(x) = 4; // Place a chest
						chestPlaced = true;
						decorationCount++;
						continue; // Skip to next tile
					}
				}
				else
				{
					int randomValue = decorationDist(rng);
					if (randomValue < 3)
					{
						decorationGrid.at(y).at(x) = 5; // Place a trap
						decorationCount++;
					}
					else if (randomValue < 15)
					{
						decorationGrid.at(y).at(x) = 6; // Place an enemy
						decorationCount++;
					}
				}
			}
		}
	}
}

void LevelGenerator::ConnectRooms(const std::vector<Edge>& _mst)
{
	for (const auto& edge : _mst)
	{
		const Room& room1 = rooms[edge.room1];
		const Room& room2 = rooms[edge.room2];
		CreateCorridor(room1, room2);
	}
}

void LevelGenerator::AddExtraConnections(std::vector<Edge>& _edges, const std::vector<Edge>& _mst, int extraConnections,
	const std::vector<Room>& _rooms)
{
	std::mt19937 rng(static_cast<unsigned>(std::time(0)));
	std::shuffle(_edges.begin(), _edges.end(), rng);

	int added = 0;
	for (const auto& edge : _edges)
	{
		if (std::find(_mst.begin(), _mst.end(), edge) == _mst.end()) // Skip edges already in MST
		{
			CreateCorridor(rooms[edge.room1], _rooms[edge.room2]);
			added++;
			if (added == extraConnections) break;
		}
	}
}
