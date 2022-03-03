
#include"ghost.h"
//--------------------------------------------------------------------------------------------------------------------------------
ghost::~ghost()
{
	delete m_stra; 
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function moves the ghost(for normal andsave mode)
void ghost::move(const board& b, Point ghostPoint, Point playerPoint, int down, int up, int rigth, int left, char sur[])
{
	_dir = m_stra->picStrategy(b, ghostPoint, playerPoint, down, up, rigth, left, sur, _dir);
	GameObject::move(leaveBehindChar, sur);
	leaveBehindChar = sur[(int)_dir];
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function rest the leaveBehindChar
void ghost::restChar()
{
	leaveBehindChar = ' ';
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function moves the ghost(for lode and lode silent mode)
bool ghost::move(int dir, char sur[], Option silentMode)
{
	_dir = (Direction)dir;
	if ((sur[(int)_dir] == (char)178 || sur[(int)_dir] == (char)176))
		return false;
	GameObject::move(leaveBehindChar, sur, silentMode);
	leaveBehindChar = sur[(int)_dir];
	return true;
}
//--------------------------------------------------------------------------------------------------------------------------------