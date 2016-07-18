/*
 * Sudoku Solver
 *
 * Copyright (C) 2016, Taeung Song <treeze.taeung@gmail.com>
 *
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX 9
#define MAX_INPUT 24

struct index {
	int x;
	int y;
};

struct sudoku_cell {
	int num;
	int cand[MAX];
	int cand_count;
	struct sudoku_cell *row;
	struct sudoku_cell *col;
	struct index box_index;
} sudoku[MAX][MAX];

int set_number(struct sudoku_cell *cell)
{
	return 0;
}

void check_box(struct sudoku_cell *cell)
{
	int i, j;
	int x = cell->box_index.x;
	int y = cell->box_index.y;
	int end_x = x + 3;
	int end_y = y + 3;

	for (i = x; i < end_x; i++) {
		for (j = y; j < end_y; j++) {
			int num = sudoku[x][y].num;

			if (num != 0 && cell->cand[num-1] != 0) {
				cell->cand[num-1] = 0;
				cell->cand_count--;
			}
		}
	}

}

void check_col(struct sudoku_cell *cell)
{
	int i;
	struct sudoku_cell *col = cell->row;

	for (i = 0; i < MAX; i++) {
		int num = col[i].num;

		if (num != 0 && cell->cand[num-1] != 0) {
			cell->cand[num-1] = 0;
			cell->cand_count--;
		}
	}
}

void check_row(struct sudoku_cell *cell)
{
	int i;
	struct sudoku_cell *row = cell->row;

	for (i = 0; i < MAX; i++) {
		int num = row[i].num;

		if (num != 0 && cell->cand[num-1] != 0) {
			cell->cand[num-1] = 0;
			cell->cand_count--;
		}
	}
}

int sudoku__check()
{
	int ret, x, y;
	bool changed = false;

	for (x = 0; x < MAX; x++) {
		for (y = 0; y < MAX; y++) {
			struct sudoku_cell *cell = &sudoku[x][y];

			if (cell->num == 0) {
				check_row(cell);
				check_col(cell);
				check_box(cell);
				ret = set_number(cell);
				if (ret == -1)
					return -1;
				if (ret == 1)
					changed = true;
			}
		}
	}

	if (changed)
		return 1;
	else
		return 0;
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
	int cand[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

	for (x = 0; x < MAX; x++) {
		fgets(input, sizeof(input), stdin);
		y = 0;
		for (i = 0; i < MAX_INPUT; i++) {
			int ch = input[i];

			if (isdigit(ch)) {
				int num = ch - '0';
				struct sudoku_cell *cell = &sudoku[x][y++];

				cell->num = num;
				if (num == 0) {
					cell->cand_count = 9;
					memcpy(cell->cand, cand, MAX);
				}
			}
		}
	}

	for (x = 0; x < MAX; x++) {
		struct sudoku_cell *row = &sudoku[x][0];

		for (y = 0; y < MAX; y++) {
			struct sudoku_cell *cell = &sudoku[x][y];

			if (cell->num == 0) {
				cell->row = row;
				cell->col = &sudoku[0][y];
				cell->box_index = which_box(x, y);
			}
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
