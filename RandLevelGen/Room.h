#pragma once

struct Room
{
	int x, y, width, height;
	int biome; // 1 = Forest, 2 = Cave, 3 = Water

	Room(int x, int y, int width, int height, int biome = 1)
		: x(x), y(y), width(width), height(height), biome(biome) {}

	bool Intersects(const Room& other) const
	{
		return !(x + width <= other.x || other.x + other.width <= x ||
			y + height <= other.y || other.y + other.height <= y);
	}
};

