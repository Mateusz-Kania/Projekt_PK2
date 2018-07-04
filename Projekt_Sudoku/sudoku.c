#include "stdafx.h"
#include "sudoku.h"

#include <windows.h>
#include <conio.h>
#include <time.h>

#define ROZMIAR_PLANSZY 9
#define ROZMIAR_KWADRATU 3
#define ROZMIAR_KWADRATU2 6
#define ZERO_ASCII 48
#define B_ESC 27
#define B_ENTER 13
#define B_OTHER 224
#define B_UP 72
#define B_RIGHT 77
#define B_DOWN 80
#define B_LEFT 75
#define B_0 48
#define RECORDS_FILE "records.sv"
#define EASY_LEVEL_MISSING 10
#define MEDIUM_LEVEL_MISSING 20
#define HARD_LEVEL_MISSING 30

typedef long long int time_t;

#pragma warning(disable:4996)


void createMap(game* game) {
	char mapa[ROZMIAR_PLANSZY][ROZMIAR_PLANSZY];

	//wypelnienie kwadratu 1.1 / do zmiany
	char liczba = 0;
	char liczba2;
	for (char i = 0; i < ROZMIAR_KWADRATU; i++) {
		for (char j = 0; j < ROZMIAR_KWADRATU; j++) {
			mapa[i][j] = liczba++;
		}
	}
	//tworzenie kwadratów 1.2, 1.3
	for (char i = 0; i < ROZMIAR_KWADRATU; i++) {
		mapa[0][ROZMIAR_KWADRATU + i] = mapa[1][i];
	}
	for (char i = 0; i < ROZMIAR_KWADRATU; i++) {
		mapa[1][ROZMIAR_KWADRATU + i] = mapa[2][i];
	}
	for (char i = 0; i < ROZMIAR_KWADRATU; i++) {
		mapa[2][ROZMIAR_KWADRATU + i] = mapa[0][i];
	}

	for (char i = 0; i < ROZMIAR_KWADRATU; i++) {
		mapa[0][ROZMIAR_KWADRATU2 + i] = mapa[2][i];
	}
	for (char i = 0; i < ROZMIAR_KWADRATU; i++) {
		mapa[1][ROZMIAR_KWADRATU2 + i] = mapa[0][i];
	}
	for (char i = 0; i < ROZMIAR_KWADRATU; i++) {
		mapa[2][ROZMIAR_KWADRATU2 + i] = mapa[1][i];
	}
	//ustalenie zamiany po ukosie
	liczba = rand() % 3;
	if (rand() % 2 == 0) {
		if (liczba == 0) {
			liczba2 = 2;
		}
		else {
			liczba2 = liczba - 1;
		}
	}
	else {
		if (liczba == 2) {
			liczba2 = 0;
		}
		else {
			liczba2 = liczba + 1;
		}
	}
	char strona = rand() % 2;
	if (strona == 0) {
		strona--;
	}
	char liczby[ROZMIAR_KWADRATU + 1];
	for (int i = 0; i < ROZMIAR_KWADRATU; i++) {
		liczby[i] = mapa[i][liczba + ROZMIAR_KWADRATU];
		liczba += strona;
		if (liczba > 2) {
			liczba -= ROZMIAR_KWADRATU;
		}
		else if (liczba < 0) {
			liczba += ROZMIAR_KWADRATU;
		}
	}

	liczby[ROZMIAR_KWADRATU] = liczby[0];
	//wykonanie zmian po ukosie w kwadracie 1.2
	for (char i = 0; i < ROZMIAR_KWADRATU; i++) {
		for (char j = 0; j < ROZMIAR_KWADRATU; j++) {
			for (char k = 0; k < ROZMIAR_KWADRATU; k++) {
				if (mapa[i][j + ROZMIAR_KWADRATU] == liczby[k]) {
					mapa[i][j + ROZMIAR_KWADRATU] = liczby[k + 1];
					break;
				}
			}
		}
	}
	//wykonanie zmian po ukosie w kwadracie 1.3
	for (char i = 0; i < ROZMIAR_KWADRATU; i++) {
		for (char j = 0; j < ROZMIAR_KWADRATU; j++) {
			for (char k = 1; k < ROZMIAR_KWADRATU + 1; k++) {
				if (mapa[i][j + ROZMIAR_KWADRATU2] == liczby[k]) {
					mapa[i][j + ROZMIAR_KWADRATU2] = liczby[k - 1];
					break;
				}
			}
		}
	}

	//tworzenie reszty kwadratow 2.1 2.2 2.3 3.1 3.2 3.3
	for (char j = 0; j < ROZMIAR_KWADRATU; j++) {
		for (char i = 0; i < ROZMIAR_KWADRATU; i++) {
			mapa[ROZMIAR_KWADRATU + i][0 + j * 3] = mapa[i][1 + j * 3];
		}
		for (char i = 0; i < ROZMIAR_KWADRATU; i++) {
			mapa[ROZMIAR_KWADRATU + i][1 + j * 3] = mapa[i][2 + j * 3];
		}
		for (char i = 0; i < ROZMIAR_KWADRATU; i++) {
			mapa[ROZMIAR_KWADRATU + i][2 + j * 3] = mapa[i][0 + j * 3];
		}
	}

	for (char j = 0; j < ROZMIAR_KWADRATU; j++) {
		for (char i = 0; i < ROZMIAR_KWADRATU; i++) {
			mapa[ROZMIAR_KWADRATU2 + i][0 + j * 3] = mapa[i][2 + j * 3];
		}
		for (char i = 0; i < ROZMIAR_KWADRATU; i++) {
			mapa[ROZMIAR_KWADRATU2 + i][1 + j * 3] = mapa[i][0 + j * 3];
		}
		for (char i = 0; i < ROZMIAR_KWADRATU; i++) {
			mapa[ROZMIAR_KWADRATU2 + i][2 + j * 3] = mapa[i][1 + j * 3];
		}
	}
	//ustalenie zamiany po ukosie
	liczba = liczba2;
	for (int i = 0; i < ROZMIAR_KWADRATU; i++) {
		liczby[i] = mapa[liczba + ROZMIAR_KWADRATU][i];
		liczba += strona;
		if (liczba > 2) {
			liczba -= ROZMIAR_KWADRATU;
		}
		else if (liczba < 0) {
			liczba += ROZMIAR_KWADRATU;
		}
	}
	liczby[ROZMIAR_KWADRATU] = liczby[0];


	
	//wykonanie zmian po ukosie w kwadratach 2.1 2.2 2.3
	for (char i = 0; i < ROZMIAR_KWADRATU; i++) {
		for (char j = 0; j < ROZMIAR_PLANSZY; j++) {
			for (char k = 0; k < ROZMIAR_KWADRATU; k++) {
				if (mapa[i + ROZMIAR_KWADRATU][j] == liczby[k]) {
					mapa[i + ROZMIAR_KWADRATU][j] = liczby[k + 1];
					break;
				}
			}
		}
	}

	//wykonanie zmian po ukosie w kwadratach 3.1 3.2 3.3
	for (char i = 0; i < ROZMIAR_KWADRATU; i++) {
		for (char j = 0; j < ROZMIAR_PLANSZY; j++) {
			for (char k = 1; k < ROZMIAR_KWADRATU + 1; k++) {
				if (mapa[i + ROZMIAR_KWADRATU2][j] == liczby[k]) {
					mapa[i + ROZMIAR_KWADRATU2][j] = liczby[k - 1];
					break;
				}
			}
		}
	}
	//ustalenie cyfr
	char indeksTabeli;
	char znaki[ROZMIAR_PLANSZY];
	for (char i = 0; i < ROZMIAR_PLANSZY; i++) {
		znaki[i] = 0;
	}
	for (char i = ROZMIAR_PLANSZY; i > 0; i--) {
		liczba = rand() % i;
		indeksTabeli = 0;
		for (char j = 0; j < liczba; j++) {
			while (!(znaki[indeksTabeli] == 0)) {
				indeksTabeli++;
			}
			indeksTabeli++;
		}
		while (!(znaki[indeksTabeli] == 0)) {
			indeksTabeli++;
		}
		znaki[indeksTabeli] = i;
	}
	//ustalenie kolumn
	char kolumny[ROZMIAR_KWADRATU2];
	liczba = rand() % 2;
	if (liczba == 0) {
		strona = 0;
	}
	else {
		strona = ROZMIAR_KWADRATU;
	}
	liczba = rand() % 3;
	switch (liczba) {
	case 0:
		kolumny[0] = ROZMIAR_KWADRATU + 0 + strona;
		liczba = rand() % 2;
		switch (liczba) {
		case 0:
			kolumny[1] = ROZMIAR_KWADRATU + 1 + strona;
			kolumny[2] = ROZMIAR_KWADRATU + 2 + strona;
			break;
		default:
			kolumny[1] = ROZMIAR_KWADRATU + 2 + strona;
			kolumny[2] = ROZMIAR_KWADRATU + 1 + strona;
			break;
		}
		break;
	case 1:
		kolumny[0] = ROZMIAR_KWADRATU + 1 + strona;
		liczba = rand() % 2;
		switch (liczba) {
		case 0:
			kolumny[1] = ROZMIAR_KWADRATU + 0 + strona;
			kolumny[2] = ROZMIAR_KWADRATU + 2 + strona;
			break;
		default:
			kolumny[1] = ROZMIAR_KWADRATU + 2 + strona;
			kolumny[2] = ROZMIAR_KWADRATU + 0 + strona;
			break;
		}
		break;
	default:
		kolumny[0] = ROZMIAR_KWADRATU + 2 + strona;
		liczba = rand() % 2;
		switch (liczba) {
		case 0:
			kolumny[1] = ROZMIAR_KWADRATU + 0 + strona;
			kolumny[2] = ROZMIAR_KWADRATU + 1 + strona;
			break;
		default:
			kolumny[1] = ROZMIAR_KWADRATU + 1 + strona;
			kolumny[2] = ROZMIAR_KWADRATU + 0 + strona;
			break;
		}
		break;

	}

	switch (liczba) {
	case 0:
		kolumny[3] = ROZMIAR_KWADRATU2 + 0 - strona;
		liczba = rand() % 2;
		switch (liczba) {
		case 0:
			kolumny[4] = ROZMIAR_KWADRATU2 + 1 - strona;
			kolumny[5] = ROZMIAR_KWADRATU2 + 2 - strona;
			break;
		default:
			kolumny[4] = ROZMIAR_KWADRATU2 + 2 - strona;
			kolumny[5] = ROZMIAR_KWADRATU2 + 1 - strona;
			break;
		}
		break;
	case 1:
		kolumny[3] = ROZMIAR_KWADRATU2 + 1 - strona;
		liczba = rand() % 2;
		switch (liczba) {
		case 0:
			kolumny[4] = ROZMIAR_KWADRATU2 + 0 - strona;
			kolumny[5] = ROZMIAR_KWADRATU2 + 2 - strona;
			break;
		default:
			kolumny[4] = ROZMIAR_KWADRATU2 + 2 - strona;
			kolumny[5] = ROZMIAR_KWADRATU2 + 0 - strona;
			break;
		}
		break;
	default:
		kolumny[3] = ROZMIAR_KWADRATU2 + 2 - strona;
		liczba = rand() % 2;
		switch (liczba) {
		case 0:
			kolumny[4] = ROZMIAR_KWADRATU2 + 0 - strona;
			kolumny[5] = ROZMIAR_KWADRATU2 + 1 - strona;
			break;
		default:
			kolumny[4] = ROZMIAR_KWADRATU2 + 1 - strona;
			kolumny[5] = ROZMIAR_KWADRATU2 + 0 - strona;
			break;
		}
		break;
	}


	//ustalenie wierszy
	char wiersze[ROZMIAR_KWADRATU2];
	liczba = rand() % 2;
	if (liczba == 0) {
		strona = 0;
	}
	else {
		strona = ROZMIAR_KWADRATU;
	}
	liczba = rand() % 3;
	switch (liczba) {
	case 0:
		wiersze[0] = ROZMIAR_KWADRATU + 0 + strona;
		liczba = rand() % 2;
		switch (liczba) {
		case 0:
			wiersze[1] = ROZMIAR_KWADRATU + 1 + strona;
			wiersze[2] = ROZMIAR_KWADRATU + 2 + strona;
			break;
		default:
			wiersze[1] = ROZMIAR_KWADRATU + 2 + strona;
			wiersze[2] = ROZMIAR_KWADRATU + 1 + strona;
			break;
		}
		break;
	case 1:
		wiersze[0] = ROZMIAR_KWADRATU + 1 + strona;
		liczba = rand() % 2;
		switch (liczba) {
		case 0:
			wiersze[1] = ROZMIAR_KWADRATU + 0 + strona;
			wiersze[2] = ROZMIAR_KWADRATU + 2 + strona;
			break;
		default:
			wiersze[1] = ROZMIAR_KWADRATU + 2 + strona;
			wiersze[2] = ROZMIAR_KWADRATU + 0 + strona;
			break;
		}
		break;
	default:
		wiersze[0] = ROZMIAR_KWADRATU + 2 + strona;
		liczba = rand() % 2;
		switch (liczba) {
		case 0:
			wiersze[1] = ROZMIAR_KWADRATU + 0 + strona;
			wiersze[2] = ROZMIAR_KWADRATU + 1 + strona;
			break;
		default:
			wiersze[1] = ROZMIAR_KWADRATU + 1 + strona;
			wiersze[2] = ROZMIAR_KWADRATU + 0 + strona;
			break;
		}
		break;

	}

	switch (liczba) {
	case 0:
		wiersze[3] = ROZMIAR_KWADRATU2 + 0 - strona;
		liczba = rand() % 2;
		switch (liczba) {
		case 0:
			wiersze[4] = ROZMIAR_KWADRATU2 + 1 - strona;
			wiersze[5] = ROZMIAR_KWADRATU2 + 2 - strona;
			break;
		default:
			wiersze[4] = ROZMIAR_KWADRATU2 + 2 - strona;
			wiersze[5] = ROZMIAR_KWADRATU2 + 1 - strona;
			break;
		}
		break;
	case 1:
		wiersze[3] = ROZMIAR_KWADRATU2 + 1 - strona;
		liczba = rand() % 2;
		switch (liczba) {
		case 0:
			wiersze[4] = ROZMIAR_KWADRATU2 + 0 - strona;
			wiersze[5] = ROZMIAR_KWADRATU2 + 2 - strona;
			break;
		default:
			wiersze[4] = ROZMIAR_KWADRATU2 + 2 - strona;
			wiersze[5] = ROZMIAR_KWADRATU2 + 0 - strona;
			break;
		}
		break;
	default:
		wiersze[3] = ROZMIAR_KWADRATU2 + 2 - strona;
		liczba = rand() % 2;
		switch (liczba) {
		case 0:
			wiersze[4] = ROZMIAR_KWADRATU2 + 0 - strona;
			wiersze[5] = ROZMIAR_KWADRATU2 + 1 - strona;
			break;
		default:
			wiersze[4] = ROZMIAR_KWADRATU2 + 1 - strona;
			wiersze[5] = ROZMIAR_KWADRATU2 + 0 - strona;
			break;
		}
		break;
	}

	//utworzenie w³aœciwej mapy
	game->time = 0;
	game->map = malloc(ROZMIAR_PLANSZY*sizeof(char*));
	game->answer = malloc(ROZMIAR_PLANSZY * sizeof(char*));
	for (int i = 0; i < ROZMIAR_PLANSZY; i++) {
		game->map[i]=malloc(ROZMIAR_PLANSZY * sizeof(char));
		game->answer[i] = malloc(ROZMIAR_PLANSZY * sizeof(char));
	}
	for (int i = 0; i < ROZMIAR_KWADRATU; i++) {
		for (int j = 0; j < ROZMIAR_KWADRATU; j++) {
			char x = znaki[mapa[i][j]];
			game->map[i][j] = znaki[(mapa[i][j])];
			game->answer[i][j] = 0;
		}
		for (int j = ROZMIAR_KWADRATU; j < ROZMIAR_PLANSZY; j++) {
			char x = znaki[(mapa[i][kolumny[j - 3]])];
			game->map[i][j] = znaki[(mapa[i][kolumny[j-3]])];
			game->answer[i][j] = 0;
		}
	}
	for (int i = ROZMIAR_KWADRATU; i < ROZMIAR_PLANSZY; i++) {
		for (int j = 0; j < ROZMIAR_KWADRATU; j++) {
			char x = znaki[(mapa[wiersze[i - 3]][j])];
			game->map[i][j] = znaki[(mapa[wiersze[i - 3]][j])];
			game->answer[i][j] = 0;
		}
		for (int j = ROZMIAR_KWADRATU; j < ROZMIAR_PLANSZY; j++) {
			char x = znaki[(mapa[wiersze[i - 3]][kolumny[j - 3]])];
			game->map[i][j] = znaki[(mapa[wiersze[i - 3]][kolumny[j - 3]])];
			game->answer[i][j] = 0;
		}
	}

}

void showMap(game game, char selectedX, char selectedY,HANDLE kolor) {

	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			switch (game.answer[i][j]) {
			case 0:
				if (i == selectedY&&j == selectedX) {
					SetConsoleTextAttribute(kolor, 96);
				}
				else {
					SetConsoleTextAttribute(kolor, 112);
				}
				printf("%i", (game.map[i][j]));
				break;
			case 1:
				if (i == selectedY&&j == selectedX) {
					SetConsoleTextAttribute(kolor, 224);
				}
				else {
					SetConsoleTextAttribute(kolor, 240);
				}
				printf(" ", game.map[i][j]);
				break;
			case 2:
				if (i == selectedY&&j == selectedX) {
					SetConsoleTextAttribute(kolor, 224);
				}
				else {
					SetConsoleTextAttribute(kolor, 240);
				}
				printf("%i", (game.map[i][j]));
				break;
			case 3://zmiana koloru soon
				if (i == selectedY&&j == selectedX) {
					SetConsoleTextAttribute(kolor, 192);
				}
				else {
					SetConsoleTextAttribute(kolor, 64);
				}
				printf("%i", (game.map[i][j]));
				break;
			}

			if (j % 3 == 2) {
				SetConsoleTextAttribute(kolor, 7);
				printf(" ");
			}
		}

		printf("\n");
		if (i % 3 == 2) {
			SetConsoleTextAttribute(kolor, 7);
			printf("\n");
		}
	}
	printf("Zosta³o %i pól.\n", game.left);
}

void deleteSquares(game* game, unsigned char howMany) {
	char squareNumber[ROZMIAR_PLANSZY*ROZMIAR_PLANSZY];
	char przesuniecie;
	char przesunieciePrev;
	for (char i = 0; i < howMany; i++) {
		przesuniecie = 0;
		squareNumber[i] = rand() % (81-i);
		for (char j = 0; j < i; j++) {
			if (squareNumber[i] >= squareNumber[j]) {
				przesuniecie++;
			}
		}
		squareNumber[i] += przesuniecie;
		do {
			przesunieciePrev = przesuniecie;
			przesuniecie = 0;
			for (char j = 0; j < i; j++) {
				if (squareNumber[i] >= squareNumber[j]) {
					przesuniecie++;
				}
			}
			squareNumber[i] += (przesuniecie-przesunieciePrev);
		} while (!(przesuniecie==przesunieciePrev));
	}
	for (char i = 0; i < howMany; i++) {
		
		game->map[squareNumber[i] / 9][squareNumber[i] % 9] = 0;
		game->answer[squareNumber[i] / 9][squareNumber[i] % 9] = 1;
	}
	game->left = howMany;
}

void deleteMap(game* game){
	for (int i = 0; i < ROZMIAR_PLANSZY; i++) {
		free(game->map[i]);
		free(game->answer[i]);
	}
	free(game->map);
	free(game->answer);

}

void operateGame(game* game, HANDLE kolor) {
	time_t timeStart;
	time_t timeFinish;
	time(&timeStart);
	char keyPressed;
	char mode = 1;
	char menuOption = 0;
	char selectedX = 0;
	char selectedY = 0;
	char** menuOptions[3];
	menuOptions[0] = "Kontynuuj";
	menuOptions[1] = "Zapisz";
	menuOptions[2] = "Wyjdz";
	while (mode>0) {
		system("cls");
		showMap(*game, selectedX, selectedY,kolor);
		if (mode == 2) {
			showMenu(menuOptions, menuOption, 3, kolor);
		}
		switch (getKey(&keyPressed)) {
		case 1:
			if (mode == 1) {
				mode = 2;
			}
			else {
				mode = 1;
			}
			break;
		case 2:
			if (mode == 2) {
				switch (menuOption) {
				case 0:
					mode = 1;
					break;
				case 1:
					time(&timeFinish);
					game->time += (timeFinish - timeStart);
					char sciezka[128];
					printf("\nPodaj sciezke pliku do którego zostanie zapisana gra.\n\n");
					scanf("%126s", &sciezka);
					switch (
						saveGame(&sciezka, game)) {
					case 0:
						return;
					default:
						printf("Nie uda³o siê zapisaæ gry.");
						break;
					}
					break;
				default:
					return;
				}
			}
			break;
		case 3:
			if (mode == 1) {
				moveOnMap(&selectedX, &selectedY, keyPressed);
			}
			else {
				moveInMenu(&menuOption, 3, keyPressed);
				
			}
			break;
		case 4:
			enterSquare(game, selectedX, selectedY, keyPressed);
			break;
		}
		if (game->left == 0) {
			system("cls");
			showMap(*game, selectedX, selectedY, kolor);
			time(&timeFinish);
			game->time += (timeFinish - timeStart);
			printf("Gra ukonczona w %i minut, %i sekund.\n", (game->time) /60 , (game->time) % 60);
			switch (saveRecord(game->diffLevel, game->time)) {
			case 0:
				break;
			case 1:
				printf("Nowy Rekord!\n");
				break;
			default:
				printf("B³¹d pliku rekordów.\n");
				break;
			}

			getch();
			return;
		}
	}


}

char getKey(char* keyPressed) {
	unsigned char key;
	unsigned char key2;
	do {
		key = getch();
		while (kbhit())
		{
			key2 = getch();
		}
	} while (key == 0);
	if (key == B_ESC) {
		*keyPressed = 0;
		return 1;
	}
	if (key == B_ENTER) {
		*keyPressed = 0;
		return 2;
	}
	if (key == B_OTHER) {
		switch (key2) {
		case B_UP:
			*keyPressed = 0;
			break;
		case B_RIGHT:
			*keyPressed = 1;
			break;
		case B_DOWN:
			*keyPressed = 2;
			break;
		case B_LEFT:
			*keyPressed = 3;
			break;
		default:
			return 0;
		}
		return 3;
	}
	if (key > B_0&&key <= B_0+9) {
		*keyPressed = key - B_0;
		return 4;
	}
	return 0;
}

void enterSquare(game* game, char selectedX, char selectedY,char keyPressed) {
	if (game->answer[selectedY][selectedX] == 0) {
		return;
	}
	char keyBefore = game->map[selectedY][selectedX];

	game->map[selectedY][selectedX] = keyPressed;
	checkCorrectness(game, selectedX, selectedY, keyBefore);

}

void checkCorrectness(game* game, char selectedX, char selectedY,char keyBefore) {
	char correct = 1;
	char keyPressed = game->map[selectedY][selectedX];
	if (keyPressed == 0) {
		return;
	}
	//sprawdzenie wiersza
	for (char i = 0; i < ROZMIAR_PLANSZY; i++) {
		if (game->map[i][selectedX] == keyPressed) {
			if (!(i == selectedY)) {
				insertScore(game, selectedX, selectedY, 3);
				if (game->answer[i][selectedX] != 0) {
					insertScore(game, selectedX, i, 3);
				}
				correct=0;
			}
		}
		else if (game->map[i][selectedX] == keyBefore && !(game->answer[i][selectedX] == 0)) {
			checkCorrectness(game, selectedX, i, -1);
		}
	}
	//sprawdzenie kolumny
	for (char i = 0; i < ROZMIAR_PLANSZY; i++) {
		if (game->map[selectedY][i] == keyPressed) {
			if (!(i == selectedX)) {
				insertScore(game, selectedX, selectedY, 3);
				if (game->answer[selectedY][i] != 0) {
					insertScore(game, i, selectedY, 3);
				}
				correct = 0;
			}
		}
		else if (game->map[selectedY][i] == keyBefore && !(game->answer[selectedY][i] == 0)) {
			checkCorrectness(game, i, selectedY, -1);
		}
	}
	//sprawdzenie kwadratu
	char testedX = selectedX;
	char testedY = selectedY;

	for (char i = 0; i < ROZMIAR_KWADRATU; i++) {
		for (char j = 0; j < ROZMIAR_KWADRATU; j++) {

			if (game->map[testedY][testedX] == keyPressed) {
				if (!(testedY == selectedY&&testedX == selectedX)) {
					insertScore(game, selectedX, selectedY, 3);
					if (game->answer[testedY][testedX] != 0) {
						insertScore(game, testedX, testedY, 3);
					}
					correct = 0;
				}
			}
			else if (game->map[testedY][testedX] == keyBefore&&!(game->answer[testedY][testedX]==0)) {
				checkCorrectness(game, testedX, testedY, -1);
			}
			testedX++;
			if (testedX%ROZMIAR_KWADRATU == 0) {
				testedX -= ROZMIAR_KWADRATU;
			}

		}
		testedY++;
		if (testedY%ROZMIAR_KWADRATU == 0) {
			testedY -= ROZMIAR_KWADRATU;
		}

	}
	if (correct == 1) {
		insertScore(game, selectedX, selectedY, 2);
	}
	return;
}

void moveOnMap(char* selectedX, char* selectedY, char keyPressed) {

	switch (keyPressed) {
	case 0:
		if (!((*selectedY) == 0)) {
			(*selectedY)--;
		}
		return;
	case 1:
		if (!((*selectedX) == ROZMIAR_PLANSZY - 1)) {
			(*selectedX)++;
		}
		return;
	case 2:
		if (!((*selectedY) == ROZMIAR_PLANSZY - 1)) {
			(*selectedY)++;
		}
		return;
	default:
		if (!((*selectedX) == 0)) {
			(*selectedX)--;
		}
		return;
	}
}

void insertScore(game* game, char selectedX, char selectedY, char score) {
	if (score == 2) {
		if (!(game->answer[selectedY][selectedX] == 2)) {
			game->left--;
		}
		game->answer[selectedY][selectedX] = 2;
		return;
	}
	else {
		if (game->answer[selectedY][selectedX] == 2) {
			game->left++;
		}
		game->answer[selectedY][selectedX] = 3;

	}

}

void showMenu(char** options, char* selectedOption,unsigned char size,HANDLE kolor) {
	char keyPressed;
	for (int i = 0; i < size; i++) {
		if (i == selectedOption) {
			SetConsoleTextAttribute(kolor, 224);
		}
		else {
			SetConsoleTextAttribute(kolor, 240);
		}
		printf("%s\n", options[i]);
	}
	SetConsoleTextAttribute(kolor, 15);



}

void moveInMenu(char* selectedOption, unsigned char size, char keyPressed) {
	switch(keyPressed){
	case 0:
		if (!((*selectedOption) == 0)) {
			(*selectedOption)--;
		}
		return;
	case 2:
		if (!((*selectedOption) == size - 1)) {
			(*selectedOption)++;
		}
		return;
	default:
		return;
}

}

char saveGame(char* link, game* savedGame) {
	FILE *plik;
	fopen_s(&plik, link, "wb");
	if (plik == NULL) {
		return 1;
	}
	fwrite(&(savedGame->left), sizeof(savedGame->left), 1, plik);
	fwrite(&(savedGame->map), sizeof(savedGame->map), 1, plik);
	fwrite(&(savedGame->time), sizeof(savedGame->time), 1, plik);
	for (int i = 0; i < ROZMIAR_PLANSZY; i++) {
		for (int j = 0; j < ROZMIAR_PLANSZY; j++) {
			fwrite(&((savedGame->answer)[i][j]), sizeof((savedGame->answer)[i][j]), 1, plik);
			fwrite(&((savedGame->map)[i][j]), sizeof((savedGame->map)[i][j]), 1, plik);
		}
	}
	fclose(plik);
	return 0;
}

char loadGame(char* link,game* game) {
	FILE *plik;
	fopen_s(&plik, link, "rb");
	if (plik == NULL) {
		return 1;
	}
	fread(&(game->left), sizeof(game->left), 1, plik);
	fread(&(game->map), sizeof(game->map), 1, plik);
	fread(&(game->time), sizeof(game->time), 1, plik);
	game->map = malloc(ROZMIAR_PLANSZY * sizeof(char*));
	game->answer = malloc(ROZMIAR_PLANSZY * sizeof(char*));
	for (int i = 0; i < ROZMIAR_PLANSZY; i++) {
		game->map[i] = malloc(ROZMIAR_PLANSZY * sizeof(char));
		game->answer[i] = malloc(ROZMIAR_PLANSZY * sizeof(char));
		for (int j = 0; j < ROZMIAR_PLANSZY; j++) {
			fread(&((game->answer)[i][j]), sizeof((game->answer)[i][j]), 1, plik);
			fread(&((game->map)[i][j]), sizeof((game->map)[i][j]), 1, plik);
		}
	}
	fclose(plik);
	return 0;
}

char saveRecord(char diffLevel, unsigned int time) {
	unsigned int prevRecord;
	FILE *plik = fopen(RECORDS_FILE, "r+b");
	if (plik == NULL) {
		return 2;
	}
	fseek(plik, diffLevel * sizeof(time), SEEK_SET);
	fread(&prevRecord, sizeof(prevRecord), 1, plik);
	if (time < prevRecord) {
		fseek(plik, diffLevel * sizeof(time), SEEK_SET);
		fwrite((&time), sizeof(time), 1, plik);
		fclose(plik);
		return 1;
	}
	fclose(plik);
	return 0;
}

void showRecords() {
	unsigned int record;
	FILE *plik = fopen(RECORDS_FILE, "rb");
	printf("Najlepsze wyniki:\n");

	fread(&record, sizeof(record), 1, plik);
	if (record == 4294967295) {
		printf("£atwy:  nie ukoñczono.\n", record / 60, record % 60);

	}
	else
	{
		printf("£atwy:  %i minut, %i sekund.\n", record / 60, record % 60);
	}

	fread(&record, sizeof(record), 1, plik);
	if (record == 4294967295) {
		printf("Œredni: nie ukoñczono.\n", record / 60, record % 60);

	}
	else
	{
		printf("Œredni: %i minut, %i sekund.\n", record / 60, record % 60);
	}

	fread(&record, sizeof(record), 1, plik);
	if (record == 4294967295) {
		printf("Trudny: nie ukoñczono.\n", record / 60, record % 60);

	}
	else
	{
		printf("Trudny: %i minut, %i sekund.\n", record / 60, record % 60);
	}

	fclose(plik);
	printf("\nNaciœnij dowolny przycisk...\n");
	getch();
}

void createGame(game* game, char diffLevel) {
	createMap(game);
	game->diffLevel = diffLevel;
	switch (diffLevel) {
	case 0:
		deleteSquares(game, EASY_LEVEL_MISSING);
		break;
	case 1:
		deleteSquares(game, MEDIUM_LEVEL_MISSING);
		break;
	case 2:
		deleteSquares(game, HARD_LEVEL_MISSING);
		break;
	}


}

void sudokuGame() {

	time_t tt;
	srand(time(&tt));
	game gra;
	HANDLE kolor = GetStdHandle(STD_OUTPUT_HANDLE);
	char keyPressed;
	char** menuOptions[4];
	char menuOption = 0;
	menuOptions[0] = "Nowa gra";
	menuOptions[1] = "Wczytaj";
	menuOptions[2] = "Rekordy";
	menuOptions[3] = "Wyjdz";

	char** lMenuOptions[4];
	char lMenuOption = 0;
	lMenuOptions[0] = "£atwy";
	lMenuOptions[1] = "Sredni";
	lMenuOptions[2] = "Trudny";
	lMenuOptions[3] = "Powrót";

	char sciezka[128];

	char mode = 1;
	while (mode > 0) {
		system("cls");
		showMenu(menuOptions, menuOption, 4, kolor);
		switch (getKey(&keyPressed)) {
		case 2:
			switch (menuOption) {
			case 0:
				mode = 2;
				while (mode == 2) {
					system("cls");
					showMenu(lMenuOptions, lMenuOption, 4, kolor);
					switch (getKey(&keyPressed)) {
					case 2:
						switch (lMenuOption) {
						case 0:
							createGame(&gra, 0);
							break;
						case 1:
							createGame(&gra, 1);
							break;
						case 2:
							createGame(&gra, 2);
							break;
						case 3: 
							mode = 3;
							break;
						}

						if (!(mode == 3)) {
							operateGame(&gra, kolor);
							deleteMap(&gra);
						}
						mode = 1;
						break;
					case 3:
						moveInMenu(&lMenuOption, 4, keyPressed);
						break;
					}

				}


				break;
			case 1:

				printf("\nPodaj sciezke pliku w którym jest zapisana gra.\n\n");
				scanf("%126s", &sciezka);
				switch (loadGame(&sciezka, &gra)) {
				case 0:
					operateGame(&gra,kolor);
					deleteMap(&gra);
					break;
				default:
					printf("\nB³¹d odczytu gry.");
					getch();
				}
				
				break;;
			case 2:
				showRecords();
				break;;
			default:
				return;
			}
			break;
		case 3:
			moveInMenu(&menuOption, 4, keyPressed);
			break;
		}
	}

}


