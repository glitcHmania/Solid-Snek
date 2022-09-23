#include "Snake.h"
#include <random>

Snake::Snake(const Location& loc)
{
	segments[0].InitHead(loc);
}

bool Snake::BodyCollisionTest(const Location& target)
{
	for (int i = 1; i < usedSegments - 1; ++i)
	{
		if (segments[i].loc == target)
		{
			return true;
		}
	}
	return false;
}

void Snake::MoveBy(const Location& delta_loc)
{
	for (int i = usedSegments - 1; i > 0; --i)
	{
		segments[i].Fallow(segments[i - 1]);
	}
	segments[0].MoveHead(delta_loc);
}

void Snake::Grow(int random_number)
{
	if (usedSegments < maxSegment)
	{
		Color random_c = Colors::MakeRGB(0, random_number, 0);
		segments[usedSegments].InitBody(random_c);
		++usedSegments;
	}
}

void Snake::Draw(Board& brd)
{
	for (int i = 0; i < usedSegments; i++)
	{

		segments[i].Draw(brd);
	}
}

Location& Snake::GetNextHeadLocation(const Location& delta_loc) const
{
	Location l(segments[0].loc);
	l.Add(delta_loc);
	return l;
}

int Snake::GetHeadLocationX() const
{
	return segments[0].loc.x;
}

int Snake::GetHeadLocationY() const
{
	return segments[0].loc.y;
}

void Snake::SetHeadLocationX(int new_x)
{
	segments[0].loc.x = new_x;
}

void Snake::SetHeadLocationY(int new_y)
{
	segments[0].loc.y = new_y;
}

bool Snake::GetIsDead() const
{
	return isDead;
}

void Snake::SetIsDead(bool booelan)
{
	isDead = booelan;
}

void Snake::Segment::InitHead(const Location& in_loc)
{
	loc = in_loc;
	c = Snake::HeadColor;
}

void Snake::Segment::InitBody(Color random_c)
{
	c = random_c;
}

void Snake::Segment::Draw(Board& brd)
{
	brd.DrawCell(loc, c);
}

void Snake::Segment::Fallow(Segment& next_segment)
{
	loc = next_segment.loc;
}

void Snake::Segment::MoveHead(const Location& delta_loc)
{
	loc.Add(delta_loc);
}
