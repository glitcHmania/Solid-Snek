/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include <assert.h>
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(rd()),
	brd(gfx),
	xDist(1, 78),
	yDist(1, 58),
	snek({ 1,1 }),
	food(rng, snek, brd)
{
	delta_loc = { 1,0 };
	std::uniform_int_distribution<int> colorDist(90, 180);
	snek.Grow(colorDist(rng));
	snek.MoveBy({ 1,0 });
	snek.Grow(colorDist(rng));
	snek.MoveBy({ 1,0 });
	brd.SpawnPoisons(rng);
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	// CALCULATING DELTATIME
	float deltaTime = ft.Mark();

	std::uniform_int_distribution<int> colorDist(90, 180);
	if (wnd.kbd.KeyIsPressed(VK_RETURN))
	{
		enterIsPressed = true;
	}
	if (enterIsPressed)
	{

		if (!snek.GetIsDead())
		{
			// SNAKE MOVEMENT
			if (wnd.kbd.KeyIsPressed(VK_UP) &&
				!(delta_loc.x == 0 && delta_loc.y == 1))
			{
				delta_loc = { 0,-1 };
			}
			if (wnd.kbd.KeyIsPressed(VK_DOWN) &&
				!(delta_loc.x == 0 && delta_loc.y == -1))
			{
				delta_loc = { 0,1 };
			}
			if (wnd.kbd.KeyIsPressed(VK_RIGHT) &&
				!(delta_loc.x == -1 && delta_loc.y == 0))
			{
				delta_loc = { 1,0 };
			}
			if (wnd.kbd.KeyIsPressed(VK_LEFT) &&
				!(delta_loc.x == 1 && delta_loc.y == 0))
			{
				delta_loc = { -1,0 };
			}
			const Location next = snek.GetNextHeadLocation(delta_loc);


			// RESPAWNING FOOD AND SPEEDING THE SNAKE UP
			// ADJUSTING FRAME PER SECOND
			const bool eating = next == food.GetLocation();
			if (eating)
			{
				brd.SpawnObstacle(food.GetLocation());
				snek.MoveBy(delta_loc);
				food.Respawn(rng, snek, brd);
				food.SetIsEaten(true);
				periodCounter = periodCounter + 1;
				
			}

			if (brd.CheckForPoison(next))
			{
				SnakeMovePeriod = std::max(SnakeMovePeriod - deltaTime * SnakeMoveMultiplier, SnakeMovePeriodMin);
				SnakeMoveCounter += deltaTime;
				brd.DespawnPoison(next);
			}

			SnakeMovePeriod = std::max(SnakeMovePeriod - deltaTime * SnakeMoveMultiplier, SnakeMovePeriodMin);
			SnakeMoveCounter += deltaTime;
			if (SnakeMoveCounter >= SnakeMovePeriod)
			{
				if (brd.CheckForObstacle(next))
				{
					snek.SetIsDead(true);
				}
				if (!brd.isInside(next) ||
					snek.BodyCollisionTest(next))
				{
					snek.SetIsDead(true);
				}
				else
				{
				
					if (food.GetIsEaten())
					{
						snek.Grow(colorDist(rng));
					}
					snek.MoveBy(delta_loc);
					food.SetIsEaten(false);
					SnakeMoveCounter -= SnakeMovePeriod;
				}
			}

		}
		else
		{
			delta_loc = { 0,0 };
			SpriteCodex::DrawGameOver(brd.GetCenterX(), brd.GetCenterY(), gfx);
		}
	}
	else
	{
		SpriteCodex::DrawTitle(brd.GetCenterX() - 52, brd.GetCenterY() - 40, gfx);
	}
}

void Game::ComposeFrame()
{
	if (enterIsPressed)
	{
		brd.DrawPoisons();
	}
	brd.DrawBorder();
	// DRAWING OBJECTS
	if (!food.GetIsEaten())
	{
		food.Draw(brd);
	}
	brd.DrawObstacles();
	snek.Draw(brd);
}
