#include "GraphUtils.h"

// Generate the MST with Kruskal's algorithm
std::vector<Edge> GenerateMST(std::vector<Edge>& _edges, int numRooms)
{
	std::vector<Edge> _mst;
	UnionFind uf(numRooms);

	// Sort edges by distance
	std::sort(_edges.begin(), _edges.end(), [](const Edge& a, const Edge& b)

		{
			return a.distance < b.distance;
		});

	// Add edges to MST
	for (const auto& edge : _edges)
	{
		if (uf.Union(edge.room1, edge.room2))
		{
			_mst.push_back(edge);
			if (_mst.size() == numRooms - 1) break; // MST complete
		}
	}
	return _mst;
}

// Calculate Manhattan distance between two rooms
int CalculateDistance(const Room& a, const Room& b)
{
	// Center room a
	int x1 = a.x + a.width / 2;
	int y1 = a.y + a.height / 2;
	// Center room b
	int x2 = b.x + b.width / 2;
	int y2 = b.y + b.height / 2;
	return abs(x1 - x2) + abs(y1 - y2);
}

// Create a list of edges based on room distance
std::vector<Edge> GenerateEdges(const std::vector<Room>& _rooms)
{
	std::vector<Edge> _edges;
	for (size_t i = 0; i < _rooms.size(); ++i)
	{
		for (size_t j = i + 1; j < _rooms.size(); ++j)
		{
			int distance = CalculateDistance(_rooms[i], _rooms[j]);
			_edges.push_back({ static_cast<int>(i), static_cast<int>(j), distance });
		}
	}
	return _edges;
}