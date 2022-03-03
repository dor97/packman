
#include "Point.h"

//--------------------------------------------------------------------------------------------------------------------------------
//The function draw a given char(player/ghost) on the board
void Point::draw(char ch) {
	gotoxy(x, y);
	cout << ch << endl;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function set point to a new one
void Point::setPoint(int x, int y)
{
	this->x = x;
	this->y = y;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function return the x value of the point
int Point::getx() const
{
	return x;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function return the y value of the point
int Point::gety() const
{
	return y;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function move an object (player/ghost) on the board by changing it's x and y value 
void Point::move(Direction dir, char sur[], int down, int up, int rigth, int left) {   //void Point::move(int dir, char board[][])  
	switch (dir) {
	case Direction::UP:
			--y;
			if (sur[(int)dir] == (char)176)
				y = down - 1;
		break;
	
	case Direction::DOWN: 
			++y;     
			if (sur[(int)dir] == (char)176)
				y = up + 1;

		break;
	
	case Direction::LEFT:
			--x;
			if (sur[(int)dir] == (char)176)
				x = rigth - 1;
		break;
	
	case Direction::RIGHT:
			++x;    
			if (sur[(int)dir] == (char)176)
				x = left + 1;
		break;
	
	case Direction::STAY:
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
bool Point::operator==(const Point& other)
{
	return(x == other.x && y == other.y);
}
//--------------------------------------------------------------------------------------------------------------------------------
Point Point::operator+(const Point& other)
{
		Point p(x + other.x, y + other.y);
		return p;
}
//--------------------------------------------------------------------------------------------------------------------------------