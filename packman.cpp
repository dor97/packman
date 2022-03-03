
#include "packman.h"
//-------------------------------------------------------------------------------------------------------------------------------------------
//The function reset the player score
void packman::resetScore()
{
	score = 0;
	fruitScore = 0;
	breadcrumbsScore = 0;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
//The function add a point to packman's score
void packman::pluseBreadcrumbsScore()
{
	++breadcrumbsScore;
	++score;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
//The function subtracts a lives from packman
void packman::loseLive()
{
	--lives;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
//The function return the packman's lives
int packman::getLives()const
{
	return lives;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
//The function return the packman's score
int packman::getBreadcrumbsScore()const
{
	return breadcrumbsScore;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
//The function size up the score by fruit value that the pacman ate
void packman::upByFuritPoints(int x)
{
	fruitScore += x;
	score += x;
}
//-------------------------------------------------------------------------------------------------------------------------------------------
int packman::getScore() const
{
	return score;
}
//-------------------------------------------------------------------------------------------------------------------------------------------