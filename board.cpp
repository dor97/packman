
#include"board.h"
//--------------------------------------------------------------------------------------------------------------------------------
//The function prints the board
void board::print()
{
	int row, col;
	gotoxy(0, 0);
	for (row = 0; row < ROW; ++row)
	{
		for (col = 0; col < COL; ++col)
		{
			cout << b[row][col];
		}
		cout << endl;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function reset the board(puts the char ' ') at the end of a game
void board::resetBoard()
{
	for (int i = 0; i < ROW; ++i)
		for (int j = 0; j < COL; ++j)
			b[i][j] = ' ';
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function open a file and copy it to an array
bool board::openFile(string s, Point positionArray[], int& ghostCun, int& boardScore, int& bLeft, int& bRigth, int& bUp, int& bDown)
{
	int i, j, cun = 0, left = 81, rigth, up, down = 0;
	bool flage = false;
	ghostCun = 0;
	ifstream outfile;
	outfile.open(s, ios::in);
	if (!outfile)
		return false;
	boardScore = 0;
	for (i = 0; i < ROW; ++i)
		outfile.getline(b[i], COL);

	for (i = 0; down == 0 && i < ROW; ++i)   //to find out the board size
	{
		for (left = 0; left < COL && b[i][left] != '#'; ++left)
		{ }
		if (left < COL)
		{
			up = i;
			for (rigth = COL-1; rigth > left && b[i][rigth] != '#'; --rigth)
			{ }
			for (down = ROW-1; b[down][left] != '#'; --down)
			{ }
		}
	}

	bLeft = left;
	bRigth = rigth;
	bDown = down;
	bUp = up;

	for (i = 0; i < COL; ++i)
		for (j = 0; j < ROW; ++j)
		{
			if (b[j][i] == '&')
			{
				positionArray[0].setPoint(i, j);
				b[j][i] = ' ';
			}
			if (i >= left && i <= rigth && j >= up && j <= down)
			{
				swithObjectInArray(flage, left, rigth, up, down, i, j, ghostCun, boardScore, positionArray);
			}
		}
	if (!flage)
		throw "board is not valid";
	outfile.close();
	return true;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function swiths the chars in the board with ther proper ones
void board::swithObjectInArray(bool &flage, int left, int rigth, int up, int down, int i, int j, int &ghostCun, int & boardScore, Point positionArray[])
{
	if (b[j][i] == ' ')
	{
		if (up == j)
		{
			b[down][i] = (char)176;
			b[up][i] = (char)176;
		}
		else if (left == i)
		{
			b[j][left] = (char)176;
			b[j][rigth] = (char)176;
		}
		else
		{
			b[j][i] = '*';
			++boardScore;
		}
	}
	if (b[j][i] == '%')
		b[j][i] = ' ';
	if (b[j][i] == '#')
		b[j][i] = (char)178;
	if (b[j][i] == '@')
	{
		positionArray[1].setPoint(i, j);
		b[j][i] = ' ';
		flage = true;
	}
	if (b[j][i] == '$' && ghostCun < 4)
	{
		positionArray[2 + ghostCun].setPoint(i, j);
		++ghostCun;
		b[j][i] = ' ';
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function return a char in the board
char board::getchar(int x, int y) const
{
	return b[y][x];
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function set a new char in the board
void board::setchar(int x, int y, char c)
{
	b[y][x] = c;
}
//--------------------------------------------------------------------------------------------------------------------------------