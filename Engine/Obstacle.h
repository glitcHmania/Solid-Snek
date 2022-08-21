#pragma once
#include "Location.h"
#include "Board.h"
#include "Snake.h"
#include <random>

class Obstacle
{
public:
	void Init(std::mt19937& rng, Board& brd, Snake& snek);
	const Location& GetLocation();
	void Draw(Board& brd);
private:
	Location loc;
	Color c = Colors::Red;
};

