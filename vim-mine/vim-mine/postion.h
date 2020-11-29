#ifndef _POSITION_H_
#define _POSITION_H_
#pragma once

class Position
{
public:
	Position();
	~Position();
	bool operator==(const Position& position);
	bool operator!=(const Position& position);
	int x = 0;
	int y = 0;

};

#endif