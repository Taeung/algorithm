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
	int i, row, col;
	char input[MAX_INPUT] = {0};

	for (row = 0; row < MAX; row++) {
		fgets(input, sizeof(input), stdin);
		col = 0;
		for (i = 0; i < MAX_INPUT; i++) {
			int ch = input[i];

			if (isdigit(ch))
				sudoku[row][col++].num = input[i] - '0';
		}

	}

	return 0;
}

int main(int argc, const char **argv)
{
	sudoku__init();

	return 0;
}
