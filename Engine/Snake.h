#pragma once
#include "Board.h"
#include "Location.h"
class Snake
{
	class Segment
	{
	public:
		void InitHead(const Location& in_loc);
		void InitBody(Color random_c);
		void Draw(Board& brd);
		void Fallow(Segment& next_segment);
		void MoveHead(const Location& delta_loc);
		Location loc;
	private:
		Color c;
	};
public:
	Snake(const Location& loc);
	bool BodyCollisionTest(const Location& target);
	void MoveBy(const Location& delta_loc);
	void Grow(int random_number);
	void Draw(Board& brd);
	Location& GetNextHeadLocation(const Location& delta_loc) const;
	Location& GetTailLocation();
	int GetHeadLocationX() const;
	int GetHeadLocationY() const;
	void SetHeadLocationX(int new_x);
	void SetHeadLocationY(int new_y);
	bool GetIsDead() const;
	void SetIsDead(bool booelan);
private:
	bool isDead = false;
	static constexpr Color HeadColor = Colors::MakeRGB(153, 153, 0);
	static constexpr Color BodyColor = Colors::MakeRGB(0, 102, 0);
	static constexpr int maxSegment = 200;
	Segment segments[maxSegment];
	int usedSegments = 1;
};

