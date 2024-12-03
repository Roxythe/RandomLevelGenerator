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

public:
	void GenerateLevel(int width, int height, int roomCount);
	const std::vector<std::vector<int>>& GetGrid() const;
	const std::vector<std::vector<int>>& GetDecorationGrid() const;
	void PlaceRoom(const Room& room);
	void CreateCorridor(const Room& room1, const Room& room2);
	bool CanPlaceRoom(const Room& room);
	void PrintGrid() const;
	void DecorateRoom(const Room& room);
	void ConnectRooms(const std::vector<Edge>& _mst);
	void AddExtraConnections(std::vector<Edge>& _edges, const std::vector<Edge>& _mst, int extraConnections,
		const std::vector<Room>& _rooms);
};

