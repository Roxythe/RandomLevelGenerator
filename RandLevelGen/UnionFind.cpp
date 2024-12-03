#include "UnionFind.h"
#include "LevelGenerator.h"

UnionFind::UnionFind(int n) : parent(n), rank(n, 0)
{
	for (int i = 0; i < n; ++i) parent[i] = i;
}

int UnionFind::Find(int x)
{
	if (parent[x] != x) parent[x] = Find(parent[x]);
	return parent[x];
}

bool UnionFind::Union(int x, int y)
{
	int rootX = Find(x);
	int rootY = Find(y);
	if (rootX == rootY) return false;
	if (rank[rootX] > rank[rootY]) parent[rootY] = rootX;
	else if (rank[rootX] < rank[rootY]) parent[rootX] = rootY;
	else
	{
		parent[rootY] = rootX;
		rank[rootX]++;
	}
	return true;
}

