#pragma once
#include"game.h"
#include"utilities.h"
#include<string>
#include<filesystem>
#include"InputParser.h"
#include"Option.h"

void playLodeOrSilentMode(Option gameOption);
void gameOption(int argc, char** argv);
bool isFileScreen(string& s);
void loadFiles(vector<string>& screen_files);
void swichColor(char color[]);
void instructions(int instruc, char color[]);
void printMenu(Option gameOption);
void oneOrMultiple(vector<string>& screen_files, char playerSelection);