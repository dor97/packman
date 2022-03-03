#pragma once

#include"point.h"
#include"Color.h"
#include"Direction.h"
#include"Option.h"

class GameObject
{
private:
	Color _objColor, _otheColor;
	Point _posion;
protected:
	unsigned char _figure;
	Direction _dir = Direction::STAY;
public:
	GameObject(unsigned char figure, Color oc, Color otheColor) : _figure(figure), _objColor(oc), _otheColor(otheColor) {}
	GameObject(unsigned char figure, Color oc, Color otheColor,const Point& p, Direction dir) :_dir(dir), _posion(p) ,_figure(figure), _objColor(oc), _otheColor(otheColor) {}
	Direction getDirection() const { return _dir; }
	void setDirection(Direction dir) { _dir = dir; }
	Point getPosion()const { return _posion; }
	void setPosion(const Point& pos) { _posion = pos; }
	void move(char leaveBehindChar, char sur[], Option silentMode = Option::normal, int down = 0, int up = 0, int rigth = 0, int left = 0);
	virtual ~GameObject(){}
};