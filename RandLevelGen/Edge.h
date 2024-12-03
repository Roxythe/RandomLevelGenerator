#pragma once
#include "Room.h"
#include <vector>
#include <cmath>
#include <algorithm>

struct Edge
{
	int room1;
	int room2;
	int distance;

	Edge(int r1, int r2, int dist) : room1(r1), room2(r2), distance(dist) {}

	bool operator==(const Edge& other) const
	{
		return (room1 == other.room1 && room2 == other.room2 && distance == other.distance);
	}
};

