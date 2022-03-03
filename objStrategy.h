#pragma once

#include"board.h"
#include"point.h"

class objStrategy {

public:
	virtual Direction picStrategy(const board& b, Point& ghostPoint, Point& playerPoint, int down, int up, int rigth, int left, char sur[], Direction dir) = 0;
	virtual ~objStrategy(){}
};