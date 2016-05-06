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
	bool in_endline;
};

struct cheese_board {
	int row, col;
	struct cell **board;
};

struct range {
	int row;
	int col;
};

void show_board(struct cheese_board *cheese_board)
{
	int i, j;

	for (i = 0; i < cheese_board->row; i++) {
		for (j = 0; j < cheese_board->col; j++) {
			printf("%d", cheese_board->board[i][j].status);
		}
		printf("\n");
	}
}

void melt_cheeses(struct cheese_board *cheese_board)
{
	int i, j;

	for (i = 0; i < cheese_board->row; i++) {
		for (j = 0; j < cheese_board->col; j++) {
			struct cell *cell = &cheese_board->board[i][j];

			if (cell->status == MELTING_CHEESE)
				cell->status = AIR;
		}
	}
}

bool is_checked_air_cell(struct cell *air_cell,
			 struct cell **checked_air_cells)
{
	int i;

	for (i = 0; checked_air_cells[i] != NULL; i++) {
		if (checked_air_cells[i] == air_cell)
			return true;
	}
	return false;
}

bool is_ventilated(struct cell *air_cell,
		   struct cell **checked_air_cells)
{
	/*
	 * Following adjoined air cells, if the first air cell
	 * can be linked with a cell of endline, it is ventilated.
	 */
	int i = 0;

	while (checked_air_cells[i] != NULL)
		i++;
	checked_air_cells[i] = air_cell;
	checked_air_cells[++i] = NULL;

	if (air_cell->in_endline) {
		return true;
	}

	for (i = 0; i < MAX_DIRECT; i++) {
		if (air_cell->direct[i]->status == AIR &&
		    !is_checked_air_cell(air_cell->direct[i], checked_air_cells) &&
		    is_ventilated(air_cell->direct[i], checked_air_cells))
			return true;
	}
	return false;
}

void check_cheese_cell(struct cell *cheese_cell, int max_cells)
{
	int i;
	struct cell **checked_air_cells;

	checked_air_cells = malloc(sizeof(struct cell *) * max_cells);

	for (i = 0; i < MAX_DIRECT; i++) {
		if (cheese_cell->direct[i]->status == AIR) {
			checked_air_cells[0] = NULL;
			if (is_ventilated(cheese_cell->direct[i], checked_air_cells)) {
				cheese_cell->status = MELTING_CHEESE;
				break;
			}
		}
	}
	free(checked_air_cells);
}

void check_board(struct cheese_board *cheese_board)
{
	int i, j;
	int max_cells = cheese_board->row * cheese_board->col;

	for (i = 0; i < cheese_board->row; i++) {
		for (j = 0; j < cheese_board->col; j++) {
			struct cell *cell = &cheese_board->board[i][j];

			if (cell->status == HAS_CHEESE)
				check_cheese_cell(cell, max_cells);
		}
	}
}

int count_remaining_cheeses(struct cheese_board *cheese_board)
{
	int i, j, remaining_cheeses = 0;

	for (i = 0; i < cheese_board->row; i++) {
		for (j = 0; j < cheese_board->col; j++) {
			struct cell *cell = &cheese_board->board[i][j];

			if (cell->status == HAS_CHEESE)
				remaining_cheeses++;
		}
	}
	return remaining_cheeses;
}

void cheese_board__delete(struct cheese_board *cheese_board)
{
	int i;

	for (i = 0; i < cheese_board->row; i++)
		free(cheese_board->board[i]);
	free(cheese_board->board);
	free(cheese_board);
}

struct cell *get_cell(struct cheese_board *cheese_board, int row, int col)
{
	if (col < 0 || col >= cheese_board->col)
                return NULL;

        if (row < 0 || row >= cheese_board->row)
                return NULL;

        return &cheese_board->board[row][col];
}

#define SET_DIRECT(_direct, _row, _col)					\
	cell->direct[_direct] = get_cell(cheese_board, _row, _col)	\

void cell_init(struct cheese_board *cheese_board,
		       struct cell *cell, int row, int col)
{
	if (row == 0 || col == 0 ||
	    row == cheese_board->row-1 || col == cheese_board->col-1)
		cell->in_endline = true;

	SET_DIRECT(TOP, row-1, col);
	SET_DIRECT(BOTTOM, row+1, col);
	SET_DIRECT(LEFT, row, col-1);
	SET_DIRECT(RIGHT, row, col+1);
}

struct cell *cheese_line__new(int size)
{
	int i, index = 0;
	char input[MAX_WIDTH] = {0};
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
	int i, j;

	cheese_board->row = row;
	cheese_board->col = col;
	for (i = 0; i < row; i++) {
		struct cell *cheese_line = cheese_line__new(col);

		if (!cheese_line)
			return -1;
		cheese_board->board[i] = cheese_line;
	}

	/* Initialize each cell for info about contiguous cell */
	for (i = 0; i < row; i++) {
		for (j = 0; j < col; j++) {
			struct cell *cell = &cheese_board->board[i][j];

			cell_init(cheese_board, cell, i, j);
		}
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
	int nr_cheeses, time_taken = 0, remaining_cheeses = -1;
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

	while (true) {
		nr_cheeses = remaining_cheeses;
		remaining_cheeses = count_remaining_cheeses(cheese_board);
		if (remaining_cheeses == 0)
			break;
		check_board(cheese_board);
		melt_cheeses(cheese_board);
		time_taken++;
	}

	printf("%d\n%d", time_taken, nr_cheeses);

	cheese_board__delete(cheese_board);
	return 0;
}
