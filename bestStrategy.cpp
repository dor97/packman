
#include"bestStrategy.h"
//-------------------------------------------------------------------------------------------------------------------------------------------
//The function returns a direction for a ghost(useing a bfs algorithm)
Direction bestStrategy::picStrategy(const board& b, Point& ghostPoint, Point& playerPoint, int down, int up, int rigth, int left, char sur[], Direction dir)
{
	queue <Point> q;
	//Point ghostPoint = g.getPoint();
	Point array[4] = { {0, 1}, {0 , -1}, {1 , 0}, {-1 , 0} };
	bool** vis = new bool* [down - up + 1];
	for (int i = 0; i < (down - up + 1); ++i)
	{
		vis[i] = new bool[rigth - left + 1];
		for (int j = 0; j < (rigth - left + 1); ++j)
			vis[i][j] = false;
	}

	q.push({ playerPoint });
	vis[playerPoint.gety()][playerPoint.getx()] = true;

	while (!q.empty())
	{
		Point point = q.front();
		q.pop();

		for (int i = 0; i < 4; ++i)
		{
			int x = point.getx() + array[i].getx();
			int y = point.gety() + array[i].gety();
			if (isValid(vis, b, x, y, left, rigth, up, down))
			{
				if (ghostPoint == (point + array[i]))
				{
					for (int i = 0; i < (down - up + 1); ++i)
						delete vis[i];
					delete vis;
					if ((rand() % 6 != 5 && cun == 5) || cun == 6)
					{
						cun = 5;
						prevDir = (Direction)i;
						return (Direction )i;
					}
					else
						return switchDir((Direction)i, sur);     //so ghost wont stick togethr(switch direction)
				}

				q.push({ x , y });
				vis[y][x] = true;
			}

		}
	}
	for (int i = 0; i < (down - up + 1); ++i)
		delete vis[i];
	delete vis;
	return Direction::STAY;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
//The function swith a ghost current direction with a new one for a few steps
Direction bestStrategy::switchDir(Direction dir, char sur[])
{
	if (cun >= 5)
	{
		if (dir == Direction::UP || dir == Direction::DOWN)
		{
			if (sur[(int)Direction::LEFT] != (char)178 && sur[(int)Direction::LEFT] != (char)176)
				dir = Direction::LEFT;
			else if (sur[(int)Direction::RIGHT] != (char)178 && sur[(int)Direction::RIGHT] != (char)176)
				dir = Direction::RIGHT;
			else
				cun = 6;
		}
		else
		{
			if (sur[(int)Direction::DOWN] != (char)178 && sur[(int)Direction::DOWN] != (char)176)
				dir = Direction::DOWN;
			else if (sur[(int)Direction::UP] != (char)178 && sur[(int)Direction::UP] != (char)176)
				dir = Direction::UP;
			else
				cun = 6;
		}
	}
	else
		dir = stickToDir(sur, prevDir);
	prevDir = dir;
	--cun;
	if (cun == 0)
		cun = 5;
	return dir;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
//The function makeing sure the ghost will keep to its random direction
Direction bestStrategy::stickToDir(char sur [], Direction dir)
{
	while (sur[(int)dir] == (char)178 || sur[(int)dir] == (char)176)
		dir = (Direction)(rand() % 4);
	return dir;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
//The function check if a position on the board is valid to find out a route(in the array limits, not a wall and have'nt been there before)
bool bestStrategy::isValid(bool** vis, const board& b, int x, int y, int& left, int& rigth, int& up, int& down)
{
	if (x < left || x > rigth || y < up || y > down)
		return false;

	if (vis[y - up][x - left])
		return false;

	if (b.getchar(x, y) != ' ' && b.getchar(x, y) != '*')
		return false;

	return true;

}
//-------------------------------------------------------------------------------------------------------------------------------------------
