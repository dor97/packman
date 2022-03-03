#pragma once


#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include"Color.h"

using namespace std;

void gotoxy(int x, int y);
void set_console_size();
void setTextColor(Color colorToSet);