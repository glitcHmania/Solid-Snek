#pragma once

struct Location
{
	void Add(const Location& delta_loc);
	bool operator==(const Location& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}
	bool operator!=(const Location& rhs) const
	{
		return x != rhs.x || y != rhs.y;
	}
	int x;
	int y;

};