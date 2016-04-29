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
#define MAX_DIRECT 4

enum status {
	AIR,
	HAS_CHEESE,
	MELTING_CHEESE
};

enum direct {
	TOP,
	BOTTOM,
	LEFT,
	RIGHT
};

struct cell {
	enum status status;
	struct cell *direct[MAX_DIRECT];
};

struct cheese_board {
	int row, col;
	struct cell **board;
};

struct range {
	int row;
	int col;
};

void cheese_board__delete(struct cheese_board *cheese_board)
{
	int i;

	for (i = 0; i < cheese_board->row; i++)
		free(cheese_board->board[i]);
	free(cheese_board->board);
	free(cheese_board);
}

struct cell *cheese_line__new(int size)
{
	int i, index = 0;
	char input[MAX_WIDTH];
	struct cell *cheese_line = malloc(sizeof(struct cell) * size);

	fgets(input, sizeof(input), stdin);

	for (i = 0; i < MAX_WIDTH; i++) {
		if (input[i] == '0')
			cheese_line[index++].status = AIR;
		if (input[i] == '1')
			cheese_line[index++].status = HAS_CHEESE;
		if (index == size)
			break;
	}
	return cheese_line;
}

int cheese_board__init(struct cheese_board *cheese_board, int row, int col)
{
	int i;

	cheese_board->row = row;
	cheese_board->col = col;
	for (i = 0; i < row; i++) {
		struct cell *cheese_line = cheese_line__new(col);

		if (!cheese_line)
			return -1;
		cheese_board->board[i] = cheese_line;
	}
	return 0;
}

struct cheese_board *cheese_board__new(int row, int col)
{
	struct cheese_board *cheese_board = malloc(sizeof(*cheese_board));

	cheese_board->board = malloc(sizeof(struct cell *) * row);
	if (cheese_board__init(cheese_board, row, col) < 0) {
		cheese_board__delete(cheese_board);
		return NULL;
	}
	return cheese_board;
}

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

bool check_range(int row, int col)
{
        if (col < 3 || col > 100)
                return false;

        if (row < 3 || row > 100)
                return false;

        return true;
}

int main(int argc, const char **argv)
{
	struct cheese_board *cheese_board;
	struct range range = get_range();

	if (check_range(range.row, range.col)) {
		cheese_board = cheese_board__new(range.row, range.col);
		if (!cheese_board) {
			printf("Error: can't create cheese board\n");
			return -1;
		}
	} else {
		printf("Error: wrong range of input\n");
		return -1;
	}

	cheese_board__delete(cheese_board);
	return 0;
}
