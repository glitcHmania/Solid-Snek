#include "Obstacle.h"



void Obstacle::Init(std::mt19937& rng, Board& brd, Snake& snek)
{
	std::uniform_int_distribution<int> xDist(1, brd.GetWidth() - 2);
	std::uniform_int_distribution<int> yDist(1, brd.GetHeight() - 2);

	Location new_loc;
	do
	{
		new_loc.x = xDist(rng);
		new_loc.y = yDist(rng);
	} while (snek.BodyCollisionTest(new_loc));
	loc = new_loc;
}

const Location& Obstacle::GetLocation()
{
	return loc;
}

void Obstacle::Draw(Board& brd)
{
	brd.DrawCell(loc, c);
}

