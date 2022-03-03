#pragma once

#include"point.h"
#include"utilities.h"
#include"Color.h"
#include"GameObject.h"

class packman : public GameObject
{
	int lives;
	int score;
	int fruitScore;
	int breadcrumbsScore;

public:

	packman(Color c, Color otherColor):GameObject(233, c, otherColor), score(0), lives(3), fruitScore(0), breadcrumbsScore(0){}
	void pluseBreadcrumbsScore();
	int getBreadcrumbsScore() const;
	int getLives() const;
	void loseLive();
	void resetScore();
	void upByFuritPoints(int x);
	int getFruitScore() const { return fruitScore;}
	int getScore() const;
};