
#include"goodStrategy.h"
//-------------------------------------------------------------------------------------------------------------------------------------------
//The function gives the ghost bfs directions and sometimes random directions
Direction goodStrategy::picStrategy(const board& b, Point& ghostPoint, Point& playerPoint, int down, int up, int rigth, int left, char sur[], Direction dir)
{
	--cun;
	if (cun == 0)
		cun = 18 + (rand() % 6);
	if (cun == 5)
		dir = (Direction)(rand() % 4);
	if (cun > 5)
		return bestStrategy::picStrategy(b, ghostPoint, playerPoint, down, up, rigth, left, sur, dir);
	else
		return noviceStrategy::picStrategy(b, ghostPoint, playerPoint, down, up, rigth, left, sur, dir);
}
//-------------------------------------------------------------------------------------------------------------------------------------------