
#include"GameObject.h"
//-------------------------------------------------------------------------------------------------------------------------------------------
//The function is responsable for printing and moving game objects(in lode silent mode onle moveing, no printing)
void GameObject::move(char leaveBehindChar, char sur[], Option silentMode, int down, int up, int rigth , int left)
{
	if(silentMode == Option::silentLode)
		_posion.move(_dir, sur, down, up, rigth, left);
	else
	{
		_posion.draw(leaveBehindChar);
		_posion.move(_dir, sur, down, up, rigth, left);
		if (_objColor != Color::WHITE) //colored game
		{
			setTextColor(_objColor);
				_posion.draw(_figure);
			setTextColor(_otheColor);
		}
		else
				_posion.draw(_figure);
	}
}
//-------------------------------------------------------------------------------------------------------------------------------------------

