
#include"noviceStrategy.h"

//--------------------------------------------------------------------------------------------------------------------------------
//The function is give the ghost random directions
Direction noviceStrategy::picStrategy(const board& b, Point& ghostPoint, Point& playerPoint, int down, int up, int rigth, int left, char sur[], Direction dir)
{
		while (sur[(int)dir] == (char)178 || sur[(int)dir] == (char)176)
			dir = (Direction)(rand()% 4);
		return dir;
}
//--------------------------------------------------------------------------------------------------------------------------------
