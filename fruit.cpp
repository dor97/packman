
#include"fruit.h"
//-------------------------------------------------------------------------------------------------------------------------------------------
void fruit::setFigure(char f)
{
	_figure = f;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
char fruit::getFigure() const
{
	return _figure;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
//The function move the fruit on the board(for normal and save mode)
void fruit::move(char sur[])
{
	while (sur[(int)_dir] == (char)178 || sur[(int)_dir] == (char)176)
		_dir =(Direction)(rand() % 4);
	GameObject::move(leaveBehindChar, sur);
	leaveBehindChar = sur[(int)_dir];
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void fruit::setLeaveBehindChar(char c)
{
	leaveBehindChar = c;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
//The function move the fruit on the board(for lode and lode silent mode)
bool fruit::move(int dir, char sur[], Option silentMode)
{
	_dir = (Direction)dir;
	if ((sur[(int)_dir] == (char)178 || sur[(int)_dir] == (char)176))
		return false;
	GameObject::move(leaveBehindChar, sur, silentMode);
	leaveBehindChar = sur[(int)_dir];
	return true;
}
//--------------------------------------------------------------------------------------------------------------------------------------------