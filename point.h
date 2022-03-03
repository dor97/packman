#pragma once

#include"utilities.h"
#include"Direction.h"

class Point {
	int x, y;
public:

	bool operator==(const Point& other);
	Point operator+(const Point& other);
	Point() = default;
	Point(int x, int y) : x(x), y(y){}
	void draw(char ch);
	void move(Direction dir, char sur[], int down, int up, int rigth, int left);
	void setPoint(int x, int y);
	int getx() const;
	int gety() const;
};
