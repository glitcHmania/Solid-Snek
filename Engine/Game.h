/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Board.h"
#include "Location.h"
#include <random>
#include "Snake.h"
#include "Food.h"
#include "FrameTimer.h"
#include "Sound.h"
class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */
	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
	bool enterIsPressed = false;
	Board brd;
	std::mt19937 rng;
	std::random_device rd;
	std::uniform_int_distribution<int> xDist;
	std::uniform_int_distribution<int> yDist;
	Snake snek;
	Food food;
	int obstacleIndex = 0;
	Location delta_loc = { 0,0 };
	float SnakeMovePeriod = 0.1f;
	float SnakeMoveCounter = 0.0f;
	int periodCounter = 0;
	float SnakeMoveMultiplier = 0.001f;
	float SnakeMovePeriodMin = 0.03f;
	Sound soundFart, soundFood, soundFail, soundStart;
	FrameTimer ft;
	bool playStartSound = true;
	bool obstacleCooldownActive = false;
	/********************************/
};