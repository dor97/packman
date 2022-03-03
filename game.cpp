
#include"game.h"
//--------------------------------------------------------------------------------------------------------------------------------
//The function runs the game
void  Game::run(vector<string> screen_files, int strat, Color otherColo, Color ghostColo)
{
	try {
	if (gameOption == Option::normal)
		runAsNormal(screen_files, strat, otherColo, ghostColo);
	else if (gameOption == Option::save)
		runSaveOption(screen_files, strat, otherColo, ghostColo);
	else if (gameOption == Option::lode)
		runLoadOption(screen_files, otherColo, ghostColo);
	else if (gameOption == Option::silentLode)
	{
		try {
			runLoadSilentOption(screen_files);
			cout << "test pass" << endl;
		}
		catch (bool flage)
		{
			if (stepsFileIn.is_open())
				stepsFileIn.close();
			if (resultFileIn.is_open())
				resultFileIn.close();
			system("CLS");
			gotoxy(0, 0);
			cout << "test fail" << endl;
		}
		Sleep(1400);
		system("CLS");
	}
	}
	catch (const char* s)
	{
		system("CLS");
		gotoxy(0, 0);
		cout << s;
		Sleep(1400);
		system("CLS");
		gotoxy(0, 0);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function run the game as normal
void Game::runAsNormal(vector<string> screen_files, int strat, Color otherColo, Color ghostColo)
{
	char key = 0;
	int cun = 0, ghCun = 0, boardScore, left, rigth, up, down, cunFruitChanchStat = 50 + rand() % 15, cunFruitStat = 0; //cunFruitChanchStat - when the fruit chanch status, cunFruitStat - Fruit status(even does'nt exist, odd exist)  
	char sur[5];
	bool flage = false;
	if (otherColo != Color::WHITE)
		setTextColor(otherColo);
	for (auto& i : screen_files)
	{
		flage = b.openFile(i, positionArray, numOfGhost, boardScore, left, rigth, up, down);
		if (player.getLives() == 0 || !flage)
			break;
		prepareGame();
		ghostArray = new ghost * [numOfGhost];
		buildGhostArray(numOfGhost, strat, ghostColo, otherColo);
		while (player.getLives() > 0 && player.getBreadcrumbsScore() < boardScore)
		{
			if (_kbhit())
				if (keyPressed())
					return;

			moveFruit(cunFruitChanchStat, cunFruitStat, sur, down, up, rigth, left, cun);

			movePlayer(sur, player.getDirection(), down, up, rigth, left);
			checkEatPosion(cunFruitChanchStat, cunFruitStat);

			move(numOfGhost, sur, down, up, rigth, left, cunFruitChanchStat, cunFruitStat, cun);
			++cun;
			Sleep(130);
		}
		gameEnd(boardScore, cunFruitChanchStat, cunFruitStat, numOfGhost);
	}
	if (checkIsFile(flage))
		return;

	checkPlayerWinAllFiles();
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function run the game of save mode
void Game::runSaveOption(vector<string> screen_files, int strat, Color otherColo, Color ghostColo)
{
	char key = 0;
	int cun = 0, ghCun = 0, boardScore, left, rigth, up, down, cunFruitChanchStat = 50 + rand() % 15, cunFruitStat = 0; //cunFruitChanchStat - when the fruit chanch status, cunFruitStat - Fruit status(even does'nt exist, odd exist)  
	char sur[5];
	string s;
	bool flage = false;
	bool FruFirstAppear = false;
	if (otherColo != Color::WHITE)
		setTextColor(otherColo);
	for (auto& i : screen_files)
	{
		cun = 0;
		s = stepsFileName(i);
		flage = b.openFile(i, positionArray, numOfGhost, boardScore, left, rigth, up, down);
		if (player.getLives() == 0 || !flage)
			break;
		stepsFileOut.open(s + "steps", ios::out);
		resultFileOut.open(s + "result", ios::out);
		prepareGame();
		buildGhostArray(numOfGhost, strat, ghostColo, otherColo);
		while (player.getLives() > 0 && player.getBreadcrumbsScore() < boardScore)
		{
			if (_kbhit())
				keyPressed();
			
			FruFirstAppear = moveFruit(cunFruitChanchStat, cunFruitStat, sur, down, up, rigth, left, cun);

			movePlayer(sur, player.getDirection(), down, up, rigth, left);

			fillFruDir(cunFruitStat, FruFirstAppear);

			checkEatPosion(cunFruitChanchStat, cunFruitStat, cun);			

			move(numOfGhost, sur, down, up, rigth, left, cunFruitChanchStat, cunFruitStat, cun);

			for (ghCun = 0; ghCun < numOfGhost; ++ghCun)
				stepsFileOut << ' ' <<(int)ghostArray[ghCun]->getDirection();

			stepsFileOut << endl;
			++cun;
			Sleep(130);
		} 
		resultFileOut << 'f' << cun;
		gameEnd(boardScore, cunFruitChanchStat, cunFruitStat, numOfGhost);
		stepsFileOut.close();
		resultFileOut.close();
	}
	if (checkIsFile(flage))
		return;

	checkPlayerWinAllFiles();
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function run the game of lode mode
void Game::runLoadOption(vector<string> screen_files, Color otherColo, Color ghostColo)
{
	char key = 0, fruFig, sur[5];
	int cun = 0, boardScore, left, rigth, up, down, size, lifeLost = 0, runTime = 0, fruDir, playerDir, * ghostDir, fruX, fruY;
	string s;
	bool flage = false, fruAppearDisappear = false;
	if (otherColo != Color::WHITE)
		setTextColor(otherColo);
	for (auto& i : screen_files)
	{
		s = stepsFileName(i);
		stepsFileIn.open(s + "steps", ios::in);
		if(stepsFileIn.is_open())
		{
			cun = 0;
			flage = b.openFile(i, positionArray, numOfGhost, boardScore, left, rigth, up, down);
			prepareGame();
			buildGhostArray(numOfGhost, 4, ghostColo, otherColo);
			ghostDir = new int[numOfGhost];

			while(player.getLives() > 0 && player.getBreadcrumbsScore() < boardScore)
			{
				stepsFileIn >> fruDir;
				
				if (fruDir == 9 && fruAppearDisappear)
				{
					gotoxy(fru.getPosion().getx(), fru.getPosion().gety());
					cout << b.getchar(fru.getPosion().getx(), fru.getPosion().gety());
					fruAppearDisappear = false;
				}

				if (fruDir != 9)
					fruitDisappear(fruAppearDisappear, cun, fruDir, sur);

				stepsFileIn >> playerDir;
				for (int j = 0; j < numOfGhost; ++j)
					stepsFileIn >> ghostDir[j];
				
				player.setDirection((Direction)playerDir);
				movePlayer(sur, (Direction)playerDir, down, up, rigth, left);

				checkEatPosion();

				move(cun, numOfGhost, sur, ghostDir);

				checkEatPosion();

				Sleep(70);
				++cun;
			}
			gameEnd(boardScore, numOfGhost);
		}
		if (stepsFileIn.is_open())
			stepsFileIn.close();
	}
	Sleep(1200);
	system("CLS");
	gotoxy(0, 0);
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function run the game of lode silent mode
void Game::runLoadSilentOption(vector<string> screen_files)
{
	char key = 0, fruFig, sur[5];
	int cun = 0, boardScore, left, rigth, up, down, fruDir, playerDir, * ghostDir, fruX, fruY, size, lifeLost = 0, runTime = 0;
	string s;
	bool flage = false, fruEaten = false, playerEaten1 = true, playerEaten2 = true, fruAppearDisappear = false;
	vector<int> loseLife;
	for (auto& i : screen_files)
	{
		s = stepsFileName(i);
		stepsFileIn.open(s + "steps", ios::in);
		resultFileIn.open(s + "result", ios::in);

		if (resultFileIn.is_open() && stepsFileIn.is_open())
		{
			if (player.getLives() == 0)
				throw false;
			cun = 0;
			flage = b.openFile(i, positionArray, numOfGhost, boardScore, left, rigth, up, down);
			prepareGame();
			buildGhostArray(numOfGhost, 4, Color::WHITE, Color::WHITE);
			ghostDir = new int[numOfGhost];
			fileToVectior(loseLife);
			size = loseLife.size();
			resultFileIn >> runTime;
			resultFileIn.close();

			while (cun <= runTime)
			{
				stepsFileIn >> fruDir;

				if (fruDir == 9 && fruAppearDisappear)
				{
					fruAppearDisappear = false;
					fruEaten = false;
				}

				if (fruDir != 9)
				{
					if (fruEaten)
						throw false;
					fruEaten = fruitDisappear(fruAppearDisappear, cun, fruDir, sur);
				}

				stepsFileIn >> playerDir;
				for (int j = 0; j < numOfGhost; ++j)
					stepsFileIn >> ghostDir[j];

				player.setDirection((Direction)playerDir);
				movePlayer(sur, (Direction)playerDir, down, up, rigth, left);
				playerEaten1 = wasPackmanEaten(loseLife, cun, lifeLost, size);

				move(cun, numOfGhost, sur, ghostDir);

				playerEaten2 = wasPackmanEaten(loseLife, cun, lifeLost, size);

				if (!playerEaten1 && !playerEaten2)
					throw false;
				else
					playerEaten1 = playerEaten2 = true;

				++cun;
			}
			if (player.getLives() > 0 && player.getBreadcrumbsScore() != boardScore)
				throw false;
			gameEnd(boardScore, numOfGhost);
		}
		if (stepsFileIn.is_open())
			stepsFileIn.close();
		if (resultFileIn.is_open())
			resultFileIn.close();
	}
	gotoxy(0, 0);
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function fill the fruit direction in the stpes fill according to the fill format
void Game::fillFruDir(int cunFruitStat, bool &FruFirstAppear)
{
	if (cunFruitStat % 2 == 1)
		if (FruFirstAppear)
		{
			stepsFileOut << (int)fru.getDirection() << ' ' << fru.getPosion().getx() << ' ' << fru.getPosion().gety() << ' ' << fru.getFigure() << ' ' << (int)player.getDirection();
			FruFirstAppear = false;
		}
		else
			stepsFileOut << (int)fru.getDirection() << ' ' << (int)player.getDirection();
	else
		stepsFileOut << 9 << ' ' << (int)player.getDirection();
}
//------------------------------------------------------------------------------------------------------------------------------------
//The function checks if the packman lost (or not) a life and was supposed to lose one(or wasnt supposed to) according to result fill
//if was supposed to lose a life return if so, else(wasnt supposed to) and lost a life throw false(test filed in silent mode).
//if loset life and was supposed to than ++lifeLost( loseLife[lifeLost] - when packman lost a life)
bool Game::wasPackmanEaten(vector<int> loseLife, int cun, int& lifeLost, int size)
{
	bool playerEaten = true;
	if (lifeLost < size && loseLife[lifeLost] == cun)
	{
		if (playerEaten = checkEatPosion())
			++lifeLost;
	}
	else if(gameOption == Option::silentLode)
		if (checkEatPosion())
			throw false;
	return playerEaten;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function moves all the ghost(lode and lode silent mode), if in silent mode and ghost try to go trow wall trow false(test filed).
void Game::move(int cun, int numOfGhost, char *sur, int *ghostDir)
{
	if (cun % 2 == 0)
	{
		for (int j = 0; j < numOfGhost; ++j)
		{
			surroundB(ghostArray[j]->getPosion().getx(), ghostArray[j]->getPosion().gety(), sur);
			if (!ghostArray[j]->move(ghostDir[j], sur, gameOption))
				if (gameOption == Option::silentLode)
					throw false;
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function move the fruit, if fruit appear read it's position and value, the function return if fruit were eaten in a certain period
bool Game::fruitDisappear(bool & fruAppearDisappear, int cun, int fruDir, char *sur)
{
	bool fruEaten1, fruEaten2 = false;
	int fruX, fruY;
	char fruFig;
	if (!fruAppearDisappear)
	{
		stepsFileIn >> fruX;
		stepsFileIn >> fruY;
		fru.setPosion({ fruX, fruY });
		stepsFileIn >> fruFig;
		fru.setFigure(fruFig);
		fru.setLeaveBehindChar(b.getchar(fruX, fruY));
	}
	fruEaten1 = checkFuritEaten();
	fruAppearDisappear = true;
	if (cun % 4 == 0)
	{
		surroundB(fru.getPosion().getx(), fru.getPosion().gety(), sur);
		fru.move(fruDir, sur, gameOption);
		fruEaten2 = checkFuritEaten();
	}
	if (fruEaten1 || fruEaten2)
		return true;
	return false;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function file loseLife vector(when the packman die) from result file
void Game::fileToVectior(vector<int>& loseLife)
{
	char c;
	int i;
	resultFileIn >> c;
	while (!resultFileIn.eof() && c == packmanDie) //packmanDie = 'l'
	{
		resultFileIn >> i;
		resultFileIn >> c;
		loseLife.push_back(i);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function is being called if a key was press, change player direction accordingly
bool Game::keyPressed()
{
	char key;
	Direction dir = Direction::STAY;
	key = _getch();
	if (key == ESC)
		if (!isPuse())
		{
			system("CLS");
			return true;
		}
	if (keyToDirection(key, dir))
		player.setDirection(dir);
	return false;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function move all ghost(normal and save mode)
void Game::move(int numOfGhost, char* sur, int down, int up, int rigth, int left, int cunFruitChanchStat , int cunFruitStat, int cun)
{
	if (cun % 2 == 0)   //move ghost every second move
	{
		for (int ghCun = 0; ghCun < numOfGhost; ++ghCun)
		{
			surroundB(ghostArray[ghCun]->getPosion().getx(), ghostArray[ghCun]->getPosion().gety(), sur);
			ghostArray[ghCun]->move(b, ghostArray[ghCun]->getPosion(), player.getPosion(), down, up, rigth, left, sur);
		}
		checkEatPosion(cunFruitChanchStat, cunFruitStat, cun);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function build an array of poiners to ghost with selected strategy
void Game::buildGhostArray(int numOfGhost, int strat, Color ghostColo, Color otherColo)
{
	ghostArray = new ghost * [numOfGhost];
	for (int ghCun = 0; ghCun < numOfGhost; ++ghCun)
	{
		if (strat == 1)
			ghostArray[ghCun] = new ghost(positionArray[2 + ghCun], ghostColo, otherColo, new bestStrategy, (Direction)(rand() % 4));
		else if (strat == 2)
			ghostArray[ghCun] = new ghost(positionArray[2 + ghCun], ghostColo, otherColo, new goodStrategy, (Direction)(rand() % 4));
		else if (strat == 3)
			ghostArray[ghCun] = new ghost(positionArray[2 + ghCun], ghostColo, otherColo, new noviceStrategy, (Direction)(rand() % 4));
		else
			ghostArray[ghCun] = new ghost(positionArray[2 + ghCun], ghostColo, otherColo, (Direction)(rand() % 4));
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function return a file name (screen file) with out the ending(.screen)
string Game::stepsFileName(string& s)
{
	string newName;
	int i;
	for (i = 0; i < s.length() - 6; ++i)
		newName.push_back(s[i]);
	return newName;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function prints the board, pacman, score and live
void Game::prepareGame()
{
	player.setPosion(positionArray[1]);
	if (gameOption != Option::silentLode)
	{
		b.print();
		gotoxy(positionArray[0].getx(), positionArray[0].gety());
		cout << "Score:" << player.getScore() << "    Lives:" << player.getLives();
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function checks if the player won or loste and reset the game for the next game(narmal or save mode)
void Game::gameEnd(int boardScore, int & cunFruitChanchStat, int& cunFruitStat, int numOfGhost)
{
	for (int ghCun = 0; ghCun < numOfGhost; ++ghCun)
		delete ghostArray[ghCun];
	delete[] ghostArray;

	checkWinLose(boardScore);
	player.resetScore();
	player.setDirection(Direction::STAY);
	b.resetBoard();
	cunFruitChanchStat = 0;
	cunFruitStat = -1;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function checks if the player won or loste and reset the game for the next game(lode or lode silent mode)
void Game::gameEnd(int boardScore, int numOfGhost)
{
	for (int ghCun = 0; ghCun < numOfGhost; ++ghCun)
		delete ghostArray[ghCun];
	delete[] ghostArray;

	player.resetScore();
	b.resetBoard();
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function checks if a file exists and if not prints a message
bool Game::checkIsFile(bool flage)
{
	if (!flage)
	{
		cout << "no more files" << endl;
		system("pause");
		gotoxy(0, 0);
		return true;
	}
	return false;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function checks if the player won or loste
void Game::checkPlayerWinAllFiles()
{
	if (player.getLives() > 0)
	{
		gotoxy(0, 0);
		cout << "no more boards left to play" << endl;
		system("pause");
		gotoxy(0, 0);
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function checks if the fruit got eaten
void Game::checkFuritEaten(int& cunFruitChanchStat)
{
	checkFruitEatenPlayer(cunFruitChanchStat);
	checkFruitEatenGhost(cunFruitChanchStat);
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function checks if the fruit got eaten and return if it did(for lode and lode silent mode)
bool Game::checkFuritEaten()
{
	if (checkFruitEatenPlayer() || checkFruitEatenGhost())
		return true;
	return false;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function checks if the fruit got eaten by the player(for normal and save mode)
void Game::checkFruitEatenPlayer(int& cunFruitChanchStat)
{
	if (fru.getPosion() == player.getPosion())
	{
		player.upByFuritPoints(fru.getFigure() - 48);
		gotoxy(positionArray[0].getx() + 6, positionArray[0].gety());
		cout << player.getScore();
		cunFruitChanchStat = 0;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function checks if the fruit got eaten by the playe and return if it did(for lode and lode silent mode)
bool Game::checkFruitEatenPlayer()
{
	if (fru.getPosion() == player.getPosion())
	{
		player.upByFuritPoints(fru.getFigure() - 48);
		if (gameOption != Option::silentLode)
		{
			gotoxy(positionArray[0].getx() + 6, positionArray[0].gety());
			cout << player.getScore();
		}
		return true;
	}
	return false;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function checks if the fruit got eaten by a ghost(for normal and save mode)
void Game::checkFruitEatenGhost(int& cunFruitChanchStat)
{
	for(int i = 0; i < numOfGhost && cunFruitChanchStat != 1; ++i)
		if (fru.getPosion() == ghostArray[i]->getPosion())
			cunFruitChanchStat = 0;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function checks if the fruit got eaten by a ghost and return if it did(for lode and lode silent mode)
bool Game::checkFruitEatenGhost()
{
	for (int i = 0; i < numOfGhost; ++i)
		if (fru.getPosion() == ghostArray[i]->getPosion())
			return true;
	return false;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function move the fruit(for normal and save mode)
bool Game::moveFruit(int& cunFruitChanchStat, int& cunFruitStat, char sur[], int down, int up, int rigth, int left, int cun)
{
	bool flage = false;
	if (cunFruitChanchStat <= 0)
	{
		++cunFruitStat;
		if (cunFruitStat % 2 == 0)
		{
			gotoxy(fru.getPosion().getx(), fru.getPosion().gety());
			cout << b.getchar(fru.getPosion().getx(), fru.getPosion().gety());
		}
		else
		{
			fru.setFigure(53 + (rand() % 5));
			pickRandPosition(down, up, rigth, left);
			surroundB(fru.getPosion().getx(), fru.getPosion().gety(), sur);
			fru.setDirection((Direction)(rand() % 4));
			fru.move(sur);
			flage = true;
		}
		cunFruitChanchStat = 50 + (rand() % 15);
	}
	if (cunFruitStat % 2 == 1)
	{
		surroundB(fru.getPosion().getx(), fru.getPosion().gety(), sur);
		checkFuritEaten(cunFruitChanchStat);
		if (cun % 4 == 0 && cunFruitChanchStat > 0)
		{
			fru.move(sur);
			checkFuritEaten(cunFruitChanchStat);
		}
	}
	--cunFruitChanchStat;
	return flage;
}
//----------------------------------------------------------------------------------------------------------------------------------
//The function pick a random position for the fruit on the board
void Game::pickRandPosition(int down, int up, int rigth, int left)
{
	int x, y;

	do
	{
		x = left + (rand() % (rigth - left));
		y = up + (rand() % (down - up));

	} while (b.getchar(x, y) != ' ' && b.getchar(x, y) != '*');

	fru.setLeaveBehindChar(b.getchar(x, y));
	fru.setPosion(Point(x, y));
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function check if the player won or lost the game
void Game::checkWinLose(int boardScore)
{
	if (player.getBreadcrumbsScore() == boardScore)
	{
		gotoxy(positionArray[0].getx(), positionArray[0].gety() + 1);
		cout << "You're a winner";
		gotoxy(positionArray[0].getx(), positionArray[0].gety() + 2);
		cout << "BABY!!!";
		gotoxy(positionArray[0].getx(), positionArray[0].gety() + 3);
	}
	else
	{
		gotoxy(positionArray[0].getx(), positionArray[0].gety() + 1);
		cout << "GAME OVER";
		gotoxy(positionArray[0].getx(), positionArray[0].gety() + 2);
		cout << "): you're a loser :(";
		gotoxy(positionArray[0].getx(), positionArray[0].gety() + 3);
	}
	Sleep(1400);
	system("CLS");
}
//--------------------------------------------------------------------------------------------------------------------------------
////The function chacks if the player was eaten by a ghost and return if the player were eaten(for lode and lode silent mode)
bool Game::checkEatPosion()
{
	bool flage = false;
	int i;
	for (i = 0; i < numOfGhost && !flage; ++i)
		if ((player.getPosion().getx() == ghostArray[i]->getPosion().getx() && player.getPosion().gety() == ghostArray[i]->getPosion().gety()))
			flage = true;
	if (flage)
	{
		for (i = 0; i < numOfGhost; ++i)
		{
			resetGhost(*(ghostArray[i]), positionArray[2 + i].getx(), positionArray[2 + i].gety());
		}
		resetPlayer();
	}
	return flage;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function chacks if the player was eaten by a ghost(for normal and save mode)
void Game::checkEatPosion(int& cunFruitChanchStat, int& cunFruitStat, int cun)
{
	bool flage = false;
	int i;
	for(i = 0; i < numOfGhost && !flage; ++i)
		if ((player.getPosion().getx() == ghostArray[i]->getPosion().getx() && player.getPosion().gety() == ghostArray[i]->getPosion().gety()))
			flage = true;
	if (flage)
	{
		for (i = 0; i < numOfGhost; ++i)
		{
			resetGhost(*(ghostArray[i]), positionArray[2 + i].getx(), positionArray[2 + i].gety());
		}
		resetPlayer();
		cunFruitChanchStat = 0;
		cunFruitStat = -1;
		if (gameOption == Option::save)
			resultFileOut << 'l' << cun;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function reset the player position after being eaten and lower lives
void Game::resetPlayer()
{
	player.setPosion(positionArray[1]);
	player.loseLive();
	if (gameOption != Option::silentLode)
	{
		gotoxy(positionArray[0].getx() + 17, positionArray[0].gety());
		cout << player.getLives();
	}
	player.setDirection(Direction::STAY);
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function reset the ghost position after the player was eaten
void Game::resetGhost(ghost& g, int x, int y)
{
	if (gameOption != Option::silentLode)
	{
		gotoxy(g.getPosion().getx(), g.getPosion().gety());
		cout << b.getchar(g.getPosion().getx(), g.getPosion().gety());
	}
	g.setPosion(Point(x, y));
	g.restChar();
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function is being called to pause the game and unpuse or return to menu 
int Game::isPuse()
{
	int i = 1;
	char key;
	gotoxy(positionArray[0].getx(), positionArray[0].gety() + 1);
	cout << "Game paused.";
	if (gameOption == Option::normal)
	{
		gotoxy(positionArray[0].getx(), positionArray[0].gety() + 2);
		cout << "[ESC]continue[G]menu";
	}
	while (i == 1)
	{
		key = _getch();
		if (key == ESC)
			i = 0;
		if ((key == exit || key == Exit) && gameOption == Option::normal)  //exit mid game, exit = 'g' , Exit = 'G' 
			return 0;
	}
	gotoxy(positionArray[0].getx(), positionArray[0].gety() + 1);
	cout << "                    ";
	gotoxy(positionArray[0].getx(), positionArray[0].gety() + 2);
	cout << "                    ";
	return 1;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function gets a key(from the keyboard) and return the direction(of the player) of the key
bool Game::keyToDirection(char key, Direction& dir)
{
	int i;
	char arrowKeys[6] = "wxads";
	for (int i = 0; i < 5; i++)
	{
		if (key == arrowKeys[i] || key == toupper(arrowKeys[i]))
		{
			dir = (Direction)i;
			return true;
		}
	}
	return false;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function fill an array of char that surround an object(player/ghost)
void Game::surroundB(int x, int y, char sur[])
{
	sur[0] = b.getchar(x, y - 1);
	sur[1] = b.getchar(x, y + 1);
	sur[2] = b.getchar(x - 1, y);
	sur[3] = b.getchar(x + 1, y);
	sur[4] = b.getchar(x, y);
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function move the player on the board
void Game::movePlayer(char sur[], Direction dir,int down,int up,int rigth,int left)
{
	surroundB(player.getPosion().getx(), player.getPosion().gety(), sur);
	if (sur[(int)dir] != (char)178)
		player.move(' ', sur, gameOption, down, up, rigth, left);
	checkCrumbsEating();
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function chack if a crumb was eaten by the player, put emtey space and gives player a point
void Game::checkCrumbsEating()
{
	if (b.getchar(player.getPosion().getx(), player.getPosion().gety()) == '*')
	{
		b.setchar(player.getPosion().getx(), player.getPosion().gety(), ' ');
		player.pluseBreadcrumbsScore();
		if (gameOption != Option::silentLode)
		{
			gotoxy(positionArray[0].getx() + 6, positionArray[0].gety());
			cout << player.getScore();
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
