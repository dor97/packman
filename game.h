#pragma once
#include "level.h"
#include <stdlib.h>
#include "packman.h"
#include"ghost.h"
#include"board.h"
#include"utilities.h"
#include <queue>
#include <iostream>
#include"Direction.h"
#include"fruit.h"
#include"goodStrategy.h"
#include<string>
#include<fstream>
#include"Option.h"


void setTextColor(Color colorToSet);


class Game {
	enum { ESC = 27, exit = 'g', Exit = 'G', packmanDie = 'l'};
	packman player;
	ghost** ghostArray;
	board b;
	int numOfGhost = 0;
	Point positionArray[6];
	fruit fru;
	Option gameOption;
	ofstream resultFileOut;
	ifstream resultFileIn;
	ofstream stepsFileOut;
	ifstream stepsFileIn;

	void prepareGame();
	void gameEnd(int boardScore, int& cunFruitChanchStat, int& cunFruitStat, int numOfGhost);
	void checkPlayerWinAllFiles();
	bool checkIsFile(bool flage);
	void checkFruitEatenPlayer(int& cunFruitChanchStat);
	void checkFruitEatenGhost(int& cunFruitChanchStat);
	void checkFuritEaten(int& cunFruitChanchStat);
	void pickRandPosition(int down, int up, int rigth, int left);
	bool moveFruit(int& cunFruitChanchStat, int& cunFruitStat, char sur[], int down, int up, int rigth, int left, int cun);
	void checkCrumbsEating();
	void resetPlayer();
	void checkWinLose(int boardScore);
	int isPuse();
	bool keyToDirection(char key, Direction& dir);
	void movePlayer(char sur[], Direction dir, int down, int up, int rigth, int left);
	void surroundB(int x, int y, char sur[]);
	void checkEatPosion(int& cunFruitChanchStat, int& cunFruitStat, int cun = -1);
	void resetGhost(ghost& g, int x, int y);
	string stepsFileName(string& s);
	void buildGhostArray(int numOfGhost, int strat, Color ghostColo, Color otherColo);
	void move(int numOfGhost, char* sur, int down, int up, int rigth, int left, int cunFruitChanchStat, int cunFruitStat, int cun);
	bool keyPressed();
	void runSaveOption(vector<string> screen_files, int start, Color otherColo, Color ghostColo);
	void runAsNormal(vector<string> screen_files, int strat, Color otherColo, Color ghostColo);
	void runLoadOption(vector<string> screen_files, Color otherColo, Color ghostColo);
	void fileToVectior(vector<int>& loseLife);
	bool checkEatPosion();
	bool checkFruitEatenPlayer();
	void runLoadSilentOption(vector<string> screen_files);
	bool checkFuritEaten();
	bool checkFruitEatenGhost();
	bool fruitDisappear(bool& fruDisAppear, int cun, int fruDir, char* sur);
	void move(int cun, int numOfGhost, char* sur, int* ghostDir);
	bool wasPackmanEaten(vector<int> loseLife, int cun, int& lifeLost, int size);
	void fillFruDir(int cunFruitStat, bool& FruFirstAppear);
	void gameEnd(int boardScore, int numOfGhost);

public:
	Game(Option gameOp, Color packmanColo = Color::WHITE,Color otherColo = Color::WHITE, Color fruitColo = Color::WHITE ) : gameOption(gameOp), player(packmanColo, otherColo), fru(fruitColo, otherColo) {}
	void run(vector<string> screen_files , int start = 4, Color otherColo = Color::WHITE, Color ghostColo = Color::WHITE);
	
};