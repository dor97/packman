#pragma once

#include"objStrategy.h"
#include"utilities.h"
#include"point.h"
#include"board.h"

class noviceStrategy : virtual public objStrategy {

public:
	virtual Direction picStrategy(const board& b, Point& ghostPoint, Point& playerPoint, int down, int up, int rigth, int left, char sur[], Direction dir);
	virtual ~noviceStrategy() {}
};