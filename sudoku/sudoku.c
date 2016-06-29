/*
 * Sudoku Solver
 *
 * Copyright (C) 2016, Taeung Song <treeze.taeung@gmail.com>
 *
 */
#include <stdio.h>

#define MAX 9
#define MAX_INPUT 24

struct sudoku_cell {
	int num;
	int cand[MAX];
	struct sudoku_cell *row;
	struct sudoku_cell *col;
	struct sudoku_cell *box;
} sudoku[MAX][MAX];

int main(int argc, const char **argv)
{
	return 0;
}
