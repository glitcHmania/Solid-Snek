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
	food(rng, snek, brd),
	soundFart(L"Sounds\\fart.wav"),
	soundFood(L"Sounds\\arkbrick.wav"),
	soundFail(L"Sounds\\arkpad.wav"),
	soundStart(L"Sounds\\ready.wav")
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
			
			const Location next = snek.GetNextHeadLocation(delta_loc);

			// RESPAWNING FOOD AND SPEEDING THE SNAKE UP
			// ADJUSTING FRAME PER SECOND
			const bool eating = next == food.GetLocation();
			if (eating)
			{
				obstacleCooldownActive = true;
				snek.MoveBy(delta_loc);
				soundFood.Play(1.0f, 0.03f);
				brd.SpawnObstacle(food.GetLocation());
				food.Respawn(rng, snek, brd);
				food.SetIsEaten(true);
				periodCounter = periodCounter + 1;
				SnakeMovePeriod = std::max(SnakeMovePeriod - deltaTime * SnakeMoveMultiplier, SnakeMovePeriodMin);
			}

			if (brd.CheckForObject(next) == Board::Objects::Poison)
			{
				soundFart.Play(1.0f, 0.015f);
				SnakeMovePeriod = std::max(SnakeMovePeriod - deltaTime * SnakeMoveMultiplier, SnakeMovePeriodMin);
				brd.DespwanObject(next);
			}

			float ModifiedSnakeMovePeriod = SnakeMovePeriod;
			if (wnd.kbd.KeyIsPressed(VK_CONTROL))
			{
				ModifiedSnakeMovePeriod = std::min(SnakeMovePeriod, LowSnakeMovePeriod);
			}

			SnakeMoveCounter += deltaTime;
			if (SnakeMoveCounter >= ModifiedSnakeMovePeriod)
			{
				if (!brd.isInside(next) ||
					snek.BodyCollisionTest(next))
				{
					soundFail.Play(1.0f, 0.03f);
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
					SnakeMoveCounter -= ModifiedSnakeMovePeriod;
					obstacleCooldownActive = false;
				}

				// SNAKE MOVEMENT
				if (wnd.kbd.KeyIsPressed(VK_UP) &&
					!(delta_loc.x == 0 && delta_loc.y == 1))
				{
					delta_loc = { 0,-1 };
				}
				else if (wnd.kbd.KeyIsPressed(VK_DOWN) &&
					!(delta_loc.x == 0 && delta_loc.y == -1))
				{
					delta_loc = { 0,1 };
				}
				else if (wnd.kbd.KeyIsPressed(VK_RIGHT) &&
					!(delta_loc.x == -1 && delta_loc.y == 0))
				{
					delta_loc = { 1,0 };
				}
				else if (wnd.kbd.KeyIsPressed(VK_LEFT) &&
					!(delta_loc.x == 1 && delta_loc.y == 0))
				{
					delta_loc = { -1,0 };
				}
			}
			if (brd.CheckForObject(next)== Board::Objects::Obstacle && !obstacleCooldownActive)
				{
					soundFail.Play(1.0f, 0.03f);
					snek.SetIsDead(true);
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
		if (playStartSound)
		{
			soundStart.Play(1.0f, 0.03f);
			playStartSound = false;
		}
	}

}

void Game::ComposeFrame()
{
	if (enterIsPressed && !snek.GetIsDead())
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
