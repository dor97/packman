
#include"menuFunc.h"
//--------------------------------------------------------------------------------------------------------------------------------
enum{exitGame = '9', play = '1', playOneFile = '2', addColor = '7', gameInstructions = '8' };
//--------------------------------------------------------------------------------------------------------------------------------
//Deafult colors for BW game
Color packmanColo = Color::WHITE;
Color otherColo = Color::WHITE;
Color ghostColo = Color::WHITE;
Color fruitColo = Color::WHITE;
//--------------------------------------------------------------------------------------------------------------------------------
//The function run the game according to the user selection
void gameOption(int argc, char **argv)
{
	bool flage = true;
	set_console_size();
	InputParser input(argc, argv);
	if (argc == 1)
		printMenu(Option::normal);
	else if (argc == 2)
	{
		if (input.cmdOptionExists("-save"))
			printMenu(Option::save);
		else if (input.cmdOptionExists("-lode"))
			playLodeOrSilentMode(Option::lode);
		else
			flage = false;
	}
	else if (argc == 3)
	{
		if (input.getCmdOption("-save") == "-silent")
			printMenu(Option::save);
		else if (input.getCmdOption("-lode") == "-silent")
			playLodeOrSilentMode(Option::silentLode);
		else
			flage = false;
	}
	else
		cout << "USAGE: packman.exe -lode|-save [-silent]";
	if (!flage)
		cout << "USAGE: packman.exe -lode|-save [-silent]";
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function run a game(for lode and lode silent mode)
void playLodeOrSilentMode(Option gameOption)
{
	system("CLS");
	gotoxy(0, 0);
	vector<string> screen_files;
	loadFiles(screen_files);
	Game game(gameOption);
	game.run(screen_files);
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function is responsible of the menu and prints it
void printMenu(Option gameOption)
{
	char key = 0, color[5] = " off";
	int menuCun = 0, level;
	vector<string> screen_files;
	srand(time(NULL));
	system("CLS");
	gotoxy(0, 0);
	cout << "Press [1] to start new game" << endl << "press [2] to select a file to play" << endl << "press [7] for color: off" << endl << "press [8] for instructions and keys" << endl << "press [9] to exit";
	while (key != exitGame)
	{
		if (_kbhit())
			key = _getch();
		if (key == play || key == playOneFile)
		{
			system("CLS");
			oneOrMultiple(screen_files, key);
			cout << "chose ghost level: 1.best  2.good  3.novice" << endl;
			cin >> level;
			system("CLS");
			Game game(gameOption, packmanColo, otherColo, fruitColo);
			game.run(screen_files, level, otherColo, ghostColo);
			screen_files.clear();
			if (otherColo != Color::WHITE)
			{
				packmanColo = otherColo = ghostColo = fruitColo = Color::WHITE; setTextColor(otherColo);
			}
			color[0] = ' '; color[1] = 'o'; color[2] = 'f'; color[3] = 'f';
			cout << "Press [1] to start new game" << endl << "press [2] to select a file to play" << endl << "press [7] for color: off" << endl << "press [8] for instructions and keys" << endl << "press [9] to exit";
			key = 0;
		}
		if (key == addColor && menuCun % 2 == 0)
		{
			swichColor(color);
			key = 0;
		}
		if (key == gameInstructions)
		{
			++menuCun;
			instructions(menuCun % 2, color);
			key = 0;
		}
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function swiches the colors(from BW to color)
void swichColor(char color[])
{
	if (packmanColo == Color::WHITE)
	{
		packmanColo = Color::YELLOW;
		otherColo = Color::LIGHTBLUE;
		ghostColo = Color::LIGHTMAGENTA;
		fruitColo = Color::RED;
		color[0] = ' '; color[1] = 'o'; color[2] = 'n'; color[3] = ' ';
	}
	else
	{
		packmanColo = otherColo = ghostColo = fruitColo = Color::WHITE;
		color[0] = ' '; color[1] = 'o'; color[2] = 'f'; color[3] = 'f';
	}
	gotoxy(20, 2);
	cout << color;
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function prints the instrunctions
void instructions(int instruc, char color[])
{
	system("CLS");
	if (instruc)
		cout << "Pac-Man is an action maze chase video game;" << endl << "The player controls the eponymous character through an enclosed maze." << endl << "The objective of the game is to eat all of the dots placed in the maze while" << endl << "avoiding the two ghosts" << endl << "Press [W] to move up" << endl << "[X] to move down" << endl << "[D] to move right" << endl << "[A] to move left" << endl << "[S] to stay" << endl << "Press 8 to return to the menu";
	else
	{
		cout << "Press [1] to start new game" << endl << "press [2] to select a file to play" << endl << "press [7] for color:" << endl << "press [8] for instructions and keys" << endl << "press [9] to exit";
		gotoxy(20, 2);
		cout << color;
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function opens the files 
void oneOrMultiple(vector<string>& screen_files, char playerSelection)
{
	if (playerSelection == play) //player chose start game
		loadFiles(screen_files);
	else// palyer chose the option to open a specifice file
	{
		string s;
		cout << "enter file name:" << endl;
		cin >> s;
		if(isFileScreen(s))
			screen_files.push_back(s);
	}
	sort(screen_files.begin(), screen_files.end());
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function puts all the suitable files in a vectors of strings
void loadFiles(vector<string>& screen_files)
{
	string s;
	for (const auto& entry : std::filesystem::directory_iterator("."))
	{
		s = entry.path().string();
		if (isFileScreen(s))
			screen_files.push_back(entry.path().string());
	}
}
//--------------------------------------------------------------------------------------------------------------------------------
//The function checks if the file is sceen type file
bool isFileScreen(string& s)
{
	string temp = ".screen";
	int size = s.size();
	if (size < 8)
		return false;

	for (int i = size - 7; i < size; ++i)
	{
		if (s[i] != temp[i - size + 7])
			return false;
	}
	return true;
}
//--------------------------------------------------------------------------------------------------------------------------------