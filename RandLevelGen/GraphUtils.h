#pragma once
#include <vector>
#include <algorithm>
#include "UnionFind.h"
#include "Edge.h"

// Generate the MST with Kruskal's algorithm
std::vector<Edge> GenerateMST(std::vector<Edge>& _edges, int numRooms);
int CalculateDistance(const Room& a, const Room& b);
std::vector<Edge> GenerateEdges(const std::vector<Room>& _rooms);
