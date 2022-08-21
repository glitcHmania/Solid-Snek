#pragma once
#include "Snake.h"
#include "Board.h"
#include "Snake.h"
#include <random>
#include "Obstacle.h"
class Food
{
public:
	Food(std::mt19937& rng, Snake& snek, Board& brd);
	void Respawn(std::mt19937& rng, Snake& snek, Board& brd);
	void Draw(Board& brd);
	bool GetIsEaten();
	void SetIsEaten(bool boolean);
	Location GetLocation() const;
private:
	Location loc;
	static constexpr Color c = Colors::MakeRGB(255, 204, 153);
	bool isEaten = false;
};

