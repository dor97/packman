#pragma once
#include<iostream>
#include"point.h"
#include<fstream>

using namespace std;

class board
{
	static constexpr int ROW = 25, COL = 80;
	char b[ROW][COL] = { ' ' };//pacman can't go through 177, ghost can't go through 176
	
public:
	bool openFile(string s, Point p[], int& g, int& boardScore, int& left, int& rigth, int& bUp, int& bDown);
	void print();
	void resetBoard();
	char getchar(int x, int y) const;
	void setchar(int x, int y, char c);
	void swithObjectInArray(bool &flage, int left, int rigth, int up, int down, int i, int j, int& ghostCun, int& boardScore, Point positionArray[]);
};