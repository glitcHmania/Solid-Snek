#include "Board.h"

Board::Board(Graphics& in_gfx)
    :
    gfx(in_gfx)
{
}

void Board::DrawCell(const Location& loc, Color c)
{
    assert(loc.x >= 0);
    assert(loc.x < width);
    assert(loc.y >= 0);
    assert(loc.y < height);
    const int off_x = x;
    const int off_y = y;
    gfx.DrawRectDim(loc.x * dimension + off_x, loc.y * dimension + off_y, dimension, dimension, c);
}

int Board::GetWidth()
{
    return width;
}

int Board::GetHeight()
{
    return height;
}

bool Board::isInside(const Location& loc) const
{
    return loc.x >= 0 && loc.x < width&&
        loc.y >= 0 && loc.y < height;
}

void Board::DrawBorder()
{
    //TOP LINE
    gfx.DrawRect(x - 4, y, x + (width)*dimension + 5, y - 5, Colors::Blue);
    //BOTTOM LINE
    gfx.DrawRect(x - 4, (y + height * dimension), x + (width)*dimension + 5, (y + height * dimension) + 5, Colors::Blue);
    //LEFT LINE
    gfx.DrawRect(x, y - 5, x - 5, y + (height)*dimension + 5, Colors::Blue);
    //RIGHT LINE
    gfx.DrawRect((x + width * dimension), y - 5, (x + width * dimension) + 5, y + (height)*dimension + 5, Colors::Blue);
}

int Board::GetCenterX()
{
    return (x + width * dimension) / 2;
}

int Board::GetCenterY()
{
    return (y + height * dimension) / 2;
}

void Board::SpawnObstacle(const Location& loc)
{
    objects[loc.y * width + loc.x] = Objects::Obstacle;
}

void Board::SpawnPoisons(std::mt19937& rng)
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            std::uniform_int_distribution<int> dist(0, 4);
            const int prob = dist(rng);
            if (prob == 1)
            {
                objects[y * width + x] = Objects::Poison;
            }
        }
    }
}

void Board::DespwanObject(const Location& loc)
{
    objects[loc.y * width + loc.x] = Objects::Empty;
}

void Board::DrawObstacles()
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (CheckForObject({ x, y }) == Objects::Obstacle)
            {
                DrawCell({ x,y }, obstacleColor);
            }
        }
    }
}

void Board::DrawPoisons()
{
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            if (CheckForObject({ x, y }) == Objects::Poison)
            {
                DrawCell({ x,y }, poisonColor);
            }
        }
    }
}

Board::Objects Board::CheckForObject(const Location& loc) const
{
    return objects[loc.y * width + loc.x];
}