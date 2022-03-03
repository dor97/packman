#pragma once

#include"bestStrategy.h"
#include"objStrategy.h"
#include"noviceStrategy.h"
#include"utilities.h"

class goodStrategy : public noviceStrategy, public bestStrategy {

	int cun = 18 + (rand() % 6);;

public:

	virtual Direction picStrategy(const board& b, Point& ghostPoint, Point& playerPoint, int down, int up, int rigth, int left, char sur[], Direction dir);
	virtual ~goodStrategy() {}
};