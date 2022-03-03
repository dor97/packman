#pragma once

#include"point.h"
#include"utilities.h"
#include"GameObject.h"
#include"Direction.h"
#include"Option.h"

class fruit : public GameObject
{
	char leaveBehindChar;    //The char that the ghost leaves behind after moveing
public:
	fruit(Color fruitColo,Color otherColo) : GameObject('5', fruitColo, otherColo){}
	void setFigure(char f);
	char getFigure() const;
	void move(char sur[]);
	void setLeaveBehindChar(char c);
	bool move(int dir, char sur[], Option silentMode = Option::normal);

};