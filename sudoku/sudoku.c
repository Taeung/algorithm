/*
 * Sudoku Solver
 *
 * Copyright (C) 2016, Taeung Song <treeze.taeung@gmail.com>
 *
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX 9
#define MAX_INPUT 24

struct sudoku_cell {
	int num;
	int cand[MAX];
	int cand_count;
	struct sudoku_cell *row;
	struct sudoku_cell *col;
	struct sudoku_cell *box;
} sudoku[MAX][MAX];

struct index {
	int x;
	int y;
};

void check_box(struct sudoku_cell *cell)
{
}

void check_col(struct sudoku_cell *cell)
{
}

void check_row(struct sudoku_cell *cell)
{
}

int sudoku__check()
{
}

struct index which_box(int x, int y)
{
	struct index box_index;

	if (x < 6)
		box_index.x = x < 3 ?  0 : 3;
	else
		box_index.x = 6;

	if (y < 6)
		box_index.y = y < 3 ?  0 : 3;
	else
		box_index.y = 6;

	return box_index;
}

int sudoku__init()
{
	int i, x, y;
	char input[MAX_INPUT] = {0};

	for (x = 0; x < MAX; x++) {
		fgets(input, sizeof(input), stdin);
		y = 0;
		for (i = 0; i < MAX_INPUT; i++) {
			int ch = input[i];

			if (isdigit(ch)) {
				int num = ch - '0';
				struct sudoku_cell *cell = &sudoku[x][y++];

				cell->num = num;
				if (num == 0)
					cell->cand_count = 9;
			}
		}
	}

	for (x = 0; x < MAX; x++) {
		struct sudoku_cell *row = &sudoku[x][0];

		for (y = 0; y < MAX; y++) {
			/* first index of a box */
			struct index box_index = which_box(x, y);

			sudoku[x][y].row = row;
			sudoku[x][y].col = &sudoku[0][y];
			sudoku[x][y].box = &sudoku[box_index.x][box_index.y];
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
