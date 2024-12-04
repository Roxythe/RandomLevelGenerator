#pragma once
#include <vector>
#include <random>
#include "UnionFind.h"

class LevelGenerator
{
private:
	std::vector<std::vector<int>> grid;
	std::vector<Room> rooms;
	std::vector<std::vector<int>> decorationGrid;
	std::pair<int, int> spawnPoint;
	std::pair<int, int> endPoint;

public:
	void GenerateLevel(int width, int height, int roomCount);
	// Getters
	const std::vector<std::vector<int>>& GetGrid() const;
	const std::vector<std::vector<int>>& GetDecorationGrid() const;
	const std::pair<int, int>& GetSpawnPoint() const;
	const std::pair<int, int>& GetEndPoint() const;

	void PlaceSpawnAndEndPoints();
	void PlaceRoom(const Room& room);
	void CreateCorridor(const Room& room1, const Room& room2);
	bool CanPlaceRoom(const Room& room);
	void PrintGrid() const;
	void DecorateRoom(const Room& room);
	void ConnectRooms(const std::vector<Edge>& _mst);
	void AddExtraConnections(std::vector<Edge>& _edges, const std::vector<Edge>& _mst, int extraConnections,
		const std::vector<Room>& _rooms);

};

