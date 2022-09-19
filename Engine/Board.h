#pragma once
#include "Graphics.h"
#include "Colors.h"
#include "Location.h"
#include <assert.h>
#include <random>

class Board
{
public:
	Board(Graphics& in_gfx);
	void DrawCell(const Location& loc, Color c);
	int GetWidth();
	int GetHeight();
	bool isInside(const Location& loc) const;
	void DrawBorder();
	int GetCenterX();
	int GetCenterY();
	bool CheckForObstacle(const Location& loc) const;
	bool CheckForPoison(const Location& loc) const;
	void SpawnObstacle(const Location& loc);
	void SpawnPoisons(std::mt19937& rng);
	void DespawnPoison(const Location& loc);
	void DrawObstacles();
	void DrawPoisons();
private:
	static constexpr Color obstacleColor = Colors::Red;
	static constexpr Color poisonColor = Colors::MakeRGB(20,30,3);
	static constexpr int dimension = 10;
	static constexpr int width = 60;
	static constexpr int height = 45;
	static constexpr int x = 100;
	static constexpr int y = 75;
	bool hasObstacle[width * height] = { false };
	bool hasPoison[width * height] = { false };

	Graphics& gfx;
};

