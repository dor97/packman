#pragma once

#include"point.h"
#include"utilities.h"
#include"GameObject.h"
#include"Direction.h"
#include"goodStrategy.h"
#include"Option.h"

class ghost : public GameObject
{
objStrategy* m_stra;
char leaveBehindChar;    //The char that the ghost leaves behind after moveing
public:
	bool move(int dir, char sur[], Option silentMode = Option::normal);
	ghost(const Point& p, Color ghostColor, Color otherColor, objStrategy* stra, Direction dir) : GameObject(234, ghostColor, otherColor, p, dir), m_stra(stra), leaveBehindChar(' '){}
	ghost(const Point& p, Color ghostColor, Color otherColor, Direction dir) : GameObject(234, ghostColor, otherColor, p, dir), leaveBehindChar(' ') {}
	void restChar();
	void move(const board& b, Point ghostPoint, Point playerPoint, int down, int up, int rigth, int left, char sur[]);
	~ghost();
};