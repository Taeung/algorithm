/*
 * Sudoku Solver
 *
 * Copyright (C) 2016, Taeung Song <treeze.taeung@gmail.com>
 *
 */
#include <stdio.h>
#include <ctype.h>

#define MAX 9
#define MAX_INPUT 24

struct sudoku_cell {
	int num;
	int cand[MAX];
	struct sudoku_cell *row;
	struct sudoku_cell *col;
	struct sudoku_cell *box;
} sudoku[MAX][MAX];

int sudoku__init()
{
	int i, x, y;
	char input[MAX_INPUT] = {0};

	for (x = 0; x < MAX; x++) {
		fgets(input, sizeof(input), stdin);
		y = 0;
		for (i = 0; i < MAX_INPUT; i++) {
			int ch = input[i];

			if (isdigit(ch))
				sudoku[x][y++].num = input[i] - '0';
		}

	}

	for (x = 0; x < MAX; x++) {
		struct sudoku_cell *row = &sudoku[x][0];

		for (y = 0; y < MAX; y++) {
			sudoku[x][y].row = row;
			sudoku[x][y].col = &sudoku[0][y];
		}
	}

	return 0;
}

int main(int argc, const char **argv)
{
	int i, j;

	sudoku__init();

	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX; j++) {
			printf("%d", sudoku[i][j].num);
			if (j != 8)
				printf(" ");
		}
		printf("\n");
	}
	return 0;
}
