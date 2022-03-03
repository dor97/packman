
#include"utilities.h"
//--------------------------------------------------------------------------------------------------------------------------------
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	cout << flush;
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function set the console size
void set_console_size()
{
	HANDLE hOut;
	SMALL_RECT DisplayArea = { 0, 0, 0, 0 };
	int x = 80;
	int y = 25;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DisplayArea.Right = x;
	DisplayArea.Bottom = y;
	SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function set text color
void setTextColor(Color colorToSet)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}
//--------------------------------------------------------------------------------------------------------------------------------