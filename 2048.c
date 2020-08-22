#include <stdio.h>
#include <math.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
#define ARRAY_LENGTH 4


void setPrintNumber(int printNumber[15]);
void outputGrid(int** integerArray, int* printNumber);
int getKeyStatus();
void putAsideByGravity(int direction, int** grid);
void conbine(int direction, int** grid);
void copyToPreviousGrid(int** previousGrid, int** integerArray);
int judgeGameover(int** beforeGrid, int** afterGrid);
void clearGrid(int** grid, int size);
void createNumber(int** grid, int x, int y, int number);
int createNumberWithoutEmpty(int** grid, int a, int b);
int create1or2(int a, int b);
int createInteger(int a);


int main(void)
{
	int i, j, key, gameOver;
	srand((unsigned int)time(0));
	//ここからintegerArray作成
	int** integerArray = (int**)malloc(sizeof(int*) * ARRAY_LENGTH);
	if (integerArray == NULL) return -1;

	for (i = 0; i < ARRAY_LENGTH; i++) {
		integerArray[i] = (int*)malloc(sizeof(int) * ARRAY_LENGTH);
		if (integerArray[i] == NULL) return -1;
	}

	for (i = 0; i < ARRAY_LENGTH; i++) {
		for (j = 0; j < ARRAY_LENGTH; j++) {
			integerArray[i][j] = ARRAY_LENGTH * i + j;
		}
	}
	//ここまでintegerArray作成
	
	//ここからpreviousArray作成
	int** previousArray = (int**)malloc(sizeof(int*) * ARRAY_LENGTH);
	if (previousArray == NULL) return -1;

	for (i = 0; i < ARRAY_LENGTH; i++) {
		previousArray[i] = (int*)malloc(sizeof(int) * ARRAY_LENGTH);
		if (previousArray[i] == NULL) return -1;
	}

	for (i = 0; i < ARRAY_LENGTH; i++) {
		for (j = 0; j < ARRAY_LENGTH; j++) {
			previousArray[i][j] = ARRAY_LENGTH * i + j;
		}
	}
	//ここまでpreviousArray作成

	//ここからprintNumber作成
	int* printNumber = (int*)malloc(sizeof(int) * 15);
	if (printNumber == NULL) return -1;
	setPrintNumber(printNumber);
	//ここまでprintNumber作成

	clearGrid(integerArray, ARRAY_LENGTH);
	clearGrid(previousArray, ARRAY_LENGTH);
	createNumberWithoutEmpty(integerArray, 9, 1);
	outputGrid(integerArray, printNumber);

	while (( key = getKeyStatus()) != -1) {
		putAsideByGravity(key, integerArray);
		conbine(key, integerArray);
		putAsideByGravity(key, integerArray);
		if (gameOver = (judgeGameover(previousArray, integerArray)) == 1) {
			outputGrid(integerArray, printNumber);
			printf("GameOver!\n");
			return 0;
		}
		createNumberWithoutEmpty(integerArray, 9, 1);
		copyToPreviousGrid(previousArray, integerArray);
		outputGrid(integerArray, printNumber);
	}

	//ここから動的配列のメモリ開放
	for (i = 0; i < ARRAY_LENGTH; i++) {
		free(integerArray[i]);
		free(previousArray[i]);
	}

	free(integerArray);
	free(previousArray);
	free(printNumber);
	//ここまで動的配列のメモリ開放

	return 0;
}


void setPrintNumber(int printNumber[15]) {
	printNumber[0] = 0;
	int i;
	for (i = 1; i <= 14; i++) {
		printNumber[i] = (int)pow(2, i);
	}
}

void outputGrid(int** integerArray, int* printNumber) {
	int i;

	printf("+-----+-----+-----+-----+\n");
	printf("|     |     |     |     |\n");
	for (i = 0; i < ARRAY_LENGTH; i++) {
		if (integerArray[0][i] != 0) {
			printf("|%5d", printNumber[integerArray[0][i]]);
		}
		else {
			printf("|     ");
		}
	}
	printf("|\n");
	printf("|     |     |     |     |\n");
	printf("+-----+-----+-----+-----+\n");
	printf("|     |     |     |     |\n");
	for (i = 0; i < ARRAY_LENGTH; i++) {
		if (integerArray[1][i] != 0) {
			printf("|%5d", printNumber[integerArray[1][i]]);
		}
		else {
			printf("|     ");
		}
	}
	printf("|\n");
	printf("|     |     |     |     |\n");
	printf("+-----+-----+-----+-----+\n");
	printf("|     |     |     |     |\n");
	for (i = 0; i < ARRAY_LENGTH; i++) {
		if (integerArray[2][i] != 0) {
			printf("|%5d", printNumber[integerArray[2][i]]);
		}
		else {
			printf("|     ");
		}
	}
	printf("|\n");
	printf("|     |     |     |     |\n");
	printf("+-----+-----+-----+-----+\n");
	printf("|     |     |     |     |\n");

	for (i = 0; i < ARRAY_LENGTH; i++) {
		if (integerArray[3][i] != 0) {
			printf("|%5d", printNumber[integerArray[3][i]]);
		}
		else {
			printf("|     ");
		}
	}

	printf("|\n");
	printf("|     |     |     |     |\n");
	printf("+-----+-----+-----+-----+\n");
}

int getKeyStatus() {
	char c = 0;

	while (1) {
		if (_kbhit()) {
			c = _getch();

			if (c == 'w') return 0;
			if (c == 'd') return 1;
			if (c == 's') return 2;
			if (c == 'a') return 3;
			else return -1;
		}
	}
}

void putAsideByGravity(int direction, int** grid) {
	int i, j ,k;
	if (direction == 0) { //top
		for (i = 0; i < ARRAY_LENGTH; i++) {
			for (j = 2; j >= 0; j--) {
				for (k = j; k >= 0; k--) {
					if (grid[k][i] == 0) {
						grid[k][i] = grid[k + 1][i];
						grid[k + 1][i] = 0;
					}
				}
			}
		}

	} 
	else if (direction == 1) { //right
		for (i = 0; i < ARRAY_LENGTH; i++) {
			for (j = 0; j < 3; j++) {
				for (k = j; k <= 2; k++) {
					if (grid[i][k + 1] == 0) {
						grid[i][k + 1] = grid[i][k];
						grid[i][k] = 0;
					}
				}
			}
		}
	}
	else if (direction == 2) { //buttom
		for (i = 0; i < ARRAY_LENGTH; i++) {
			for (j = 0; j < 3; j++) {
				for (k = 0; k <= 2; k++) {
					if (grid[k + 1][i] == 0) {
						grid[k + 1][i] = grid[k][i];
						grid[k][i] = 0;
					}
				}
			}
		}
	}
	else if (direction == 3) { //left
		for (i = 0; i < ARRAY_LENGTH; i++) {
			for (j = 2; j >= 0; j--) {
				for (k = j; k >= 0; k--) {
					if (grid[i][k] == 0) {
						grid[i][k] = grid[i][k + 1];
						grid[i][k + 1] = 0;
					}
				}
			}
		}
	}
	else {
		fprintf(stderr, "error! in function putAsideByGravity\ndirection is not 0 to 3!\n");
	}
	return;
}

void conbine(int direction, int** grid) {
	int i, j;
	if (direction == 0) { //top
		for (i = 0; i < ARRAY_LENGTH; i++) {
			for (j = 0; j < 3; j++) {
				if (grid[j][i] == grid[j + 1][i] && grid[j][i] != 0) {
					grid[j][i]++;
					grid[j + 1][i] = 0;
				}
			}
		}
	}
	else if (direction == 1) { //right
		for (i = 0; i < ARRAY_LENGTH; i++) {
			for (j = 2; j >= 0; j--) {
				if (grid[i][j + 1] == grid[i][j] && grid[i][j+1] != 0) {
					grid[i][j + 1]++;
					grid[i][j] = 0;
				}
			}
		}
	}
	else if (direction == 2) { //buttom
		for (i = 0; i < ARRAY_LENGTH; i++) {
			for (j = 2; j >= 0; j--) {
				if (grid[j + 1][i] == grid[j][i] && grid[j+1][i] != 0) {
					grid[j + 1][i]++;
					grid[j][i] = 0;
				}
			}
		}
	}
	else if (direction == 3) { //left
		for (i = 0; i < ARRAY_LENGTH; i++) {
			for (j = 0; j < 3; j++) {
				if (grid[i][j] == grid[i][j + 1] && grid[i][j] != 0) {
					grid[i][j]++;
					grid[i][j + 1] = 0;
				}
			}
		}
	}
	return;
}

void copyToPreviousGrid(int** previousGrid, int** integerArray) {
	int i, j;
	for (i = 0; i < ARRAY_LENGTH; i++) {
		for (j = 0; j < ARRAY_LENGTH; j++) {
			previousGrid[i][j] = integerArray[i][j];
		}
	}
}

int judgeGameover(int** beforeGrid,int** afterGrid) { 
	int i, j, count = 0;
	for (i = 0; i < ARRAY_LENGTH; i++) {
		for (j = 0; j < ARRAY_LENGTH; j++) {
			if (beforeGrid[i][j] != afterGrid[i][j] || afterGrid[i][j] != 0) return 0;
		}
	}

	
	return 1;
}

void clearGrid(int** grid,int size) {
	int i,j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			grid[i][j] = 0;
		}
	}
}

void createNumber(int** grid, int x, int y, int number) {
	grid[y][x] = number;
}

int createNumberWithoutEmpty(int** grid, int a, int b) {
	int emptyCount = 0;
	int i, j;
	for (i = 0; i < ARRAY_LENGTH; i++) {
		for (j = 0; j < ARRAY_LENGTH; j++) {
			if (grid[i][j] == 0) emptyCount++;
		}
	}
	if (emptyCount == 0) return 1;
	int randNumber = createInteger(emptyCount);
	emptyCount = 0;

	for (i = 0; i < ARRAY_LENGTH; i++) {
		for (j = 0; j < ARRAY_LENGTH; j++) {
			if (grid[i][j] == 0) {
				if (emptyCount == randNumber) {
					grid[i][j] = create1or2(a, b);
					return;
				}
				emptyCount++;
			}
		}
	}
	return 0;
}

int create1or2(int a, int b) {
	double decimalRand = (double)rand() / RAND_MAX;
	double threshold = (double)a / (double)(a + b);
	return decimalRand < threshold ? 1 : 2;
}

int createInteger(int a) {
	return rand() % a;
}