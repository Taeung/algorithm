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

#define MAX_WIDTH 128

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

struct range {
	int row;
	int col;
};

struct range get_range(void)
{
	char input[MAX_WIDTH], *ptr, *args;
	struct range range;

	fgets(input, sizeof(input), stdin);
        ptr = strdup(input);
	if (!ptr) {
                printf("%s: strdup failed\n", __func__);
		range.row = 0;
		range.col = 0;
		goto out;
        }
        args = strsep(&ptr, " ");
        range.row = atoi(args);
        range.col = atoi(ptr);
out:
	return range;
}

int main(int argc, const char **argv)
{
	struct range range = get_range();

	return 0;
}
