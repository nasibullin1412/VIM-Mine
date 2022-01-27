#include "postion.h"

Position::Position()
{
	this->x = 0;
	this->y = 0;
}

Position::~Position()
{
}

bool Position::operator==(const Position& position)
{
	if (this->x == position.x)
	{
		if (this->y == position.x)
		{
			return true;
		}
	}
	return false;
}

bool Position::operator!=(const Position& position)
{
	return !(*this == position);
}

Position& Position::operator=(const Position& sec_position)
{
	this->x = sec_position.x;
	this->y = sec_position.y;
	return *this;
}

