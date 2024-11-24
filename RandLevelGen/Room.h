#pragma once

struct Room
{
	int x, y, width, height;

	Room(int x, int y, int width, int height)
		: x(x), y(y), width(width), height(height) {}

	bool Intersects(const Room& other) const
	{
		return !(x + width <= other.x || other.x + other.width <= x ||
			y + height <= other.y || other.y + other.height <= y);
	}
};

