#pragma once
#include <vector>
#include "Edge.h"

class LevelGenerator;

struct UnionFind
{
	std::vector<int> parent, rank;
	UnionFind(int n);

	int Find(int x);

	bool Union(int x, int y);
};

