/*
 * Cheese problem (New version)
 *
 * Copyright (C) 2016, Taeung Song <treeze.taeung@gmail.com>
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct cheese_cell {
	bool has_cheese;
	struct cheese_cell *up,
		*down,
		*left,
		*right;
};

struct cheese_board {
	int row, col;
	struct cheese_cell **board;
};

int main(int argc, const char **argv)
{
	return 0;
}
