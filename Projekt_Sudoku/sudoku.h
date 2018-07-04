#include "stdafx.h"

#include <windows.h>
#include <conio.h>

typedef struct {
	char** map;
	char** answer;
	char left;
	unsigned int time;
	char diffLevel;
} game;

void sudokuGame();

void createGame(game* game, char diffLevel);

void deleteMap(game* game);

void createMap(game* game);

void deleteSquares(game* game, unsigned char howMany);

void operateGame(game* game, HANDLE kolor);

void showMap(game game, char selectedX, char selectedY, HANDLE kolor);

char getKey(char* keyPressed);

void enterSquare(game* game, char selectedX, char selectedY, char keyPressed);

void checkCorrectness(game* game, char selectedX, char selectedY, char keyBefore);

void insertScore(game* game, char selectedX, char selectedY, char score);

void moveOnMap(char* selectedX, char* selectedY, char keyPressed);

void showMenu(char** options, char* selectedOption, unsigned char size, HANDLE kolor);

void moveInMenu(char* selectedOption, unsigned char size, char keyPressed);

char saveGame(char* link, game* savedGame);

char saveRecord(char diffLevel,unsigned int time );

char loadGame(char* link, game* game);

void showRecords();