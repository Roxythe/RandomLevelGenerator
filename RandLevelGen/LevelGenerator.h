#pragma once
#include <vector>
#include <random>
#include "Room.h"

class LevelGenerator
{
private:
	std::vector<std::vector<int>> grid;
	std::vector<Room> rooms;

public:
	void GenerateLevel(int width, int height, int roomCount);
	const std::vector<std::vector<int>>& GetGrid() const;
	void PlaceRoom(const Room& room);
	void CreateCorridor(const Room& room1, const Room& room2);
	bool CanPlaceRoom(const Room& room);
	void PrintGrid() const;
	void DecorateRoom(const Room& room);
};

