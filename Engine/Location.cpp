#include "Location.h"
#include <assert.h>
#include <math.h>

void Location::Add(const Location& delta_loc)
{
	assert((abs(delta_loc.x) + abs(delta_loc.y)) <= 1);
	x = x + delta_loc.x;
	y = y + delta_loc.y;
}
