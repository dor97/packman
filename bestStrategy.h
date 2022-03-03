#pragma once

#include"point.h"
#include"board.h"
#include"objStrategy.h"
#include <queue>
#include"noviceStrategy.h"
#include"Direction.h"

class bestStrategy : virtual public objStrategy {

	int cun = 6;
	Direction prevDir;

public:
	virtual Direction picStrategy(const board& b, Point& ghostPoint, Point& playerPoint, int down, int up, int rigth, int left, char sur[], Direction dir);
	bool isValid(bool** vis, const board& b, int x, int y, int& left, int& rigth, int& up, int& down);
	Direction switchDir(Direction dir, char sur[]);
	Direction stickToDir(char sur[], Direction dir);
	virtual ~bestStrategy() {}
};