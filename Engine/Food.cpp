#include "Food.h"

Food::Food(std::mt19937& rng, Snake& snek, Board& brd)
{
	Respawn(rng, snek, brd);
}

void Food::Respawn(std::mt19937& rng, Snake& snek, Board& brd)
{
	std::uniform_int_distribution<int> xDist(0, brd.GetWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, brd.GetHeight() - 1);

	Location new_loc;
	do
	{
		new_loc.x = xDist(rng);
		new_loc.y = yDist(rng);
	} while (snek.BodyCollisionTest(new_loc));
	loc = new_loc;
}

void Food::Draw(Board& brd)
{
	brd.DrawCell(loc, c);
}

bool Food::GetIsEaten()
{
	return isEaten;
}

void Food::SetIsEaten(bool boolean)
{
	isEaten = boolean;
}

Location Food::GetLocation() const
{
	return loc;
}
