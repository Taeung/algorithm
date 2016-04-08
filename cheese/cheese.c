/*
 * Cheese problem
 *
 * Copyright (C) 2016, Taeung Song <treeze.taeung@gmail.com>
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WIDTH 128

struct cell {
	int row;
	int col;
	bool has_cheese;
	struct cell *next;
};

/*
 * The cheese board has first addresses of each row of NxN
 * square cells to contain all cheese cells that are empty or filled.
 */
struct cell **cheese_board;
int bd_row, bd_col;

/* The cheese end line mean cheese cell list
 * that are sequentially connected. But
 * it should be end line of some cheese chunk.
 */
struct cell **cheese_end_line_list;
int nr_end_line_list;

void melt_cheese_end_lines()
{
	int i;

	for (i = 0; i < nr_end_line_list; i++) {
		struct cell *cheese_end_line = cheese_end_line_list[i];

		while (cheese_end_line) {
			cheese_end_line->has_cheese = false;
			cheese_end_line = cheese_end_line->next;
		}
		free(cheese_end_line);
	}

	nr_end_line_list = 0;
	free(cheese_end_line_list);
}

bool contain(struct cell* chse_end_line, int row, int col)
{
	while (chse_end_line) {
		if (row == chse_end_line->row &&
		    col == chse_end_line->col)
			return true;
		chse_end_line = chse_end_line->next;
	}

	return false;
}

bool is_blocked_road(struct cell *cheese_end_line, struct cell *cell,
		     int r_direct, int c_direct)
{
	int r = cell->row;
	int c = cell->col;
	int end_row = bd_row - 1;
	int end_col = bd_col - 1;

	while (true) {
		r += r_direct;
		c += c_direct;
		if (r == 0 || r == end_row || c == 0 || c == end_col )
			break;

		else if (contain(cheese_end_line, r, c))
			return true;
	}

	return false;
}

#define NR_DIRECT 8

bool is_escapable(struct cell *cheese_end_line, struct cell *fugitive)
{
	/*
	 * Check whether a specific cell(fugitive) can escape
	 * from a boundary(cheese_end_line) following eight direction
	 *
	 */

	int i;
	bool escapable;
	struct direct {
		int r_direct;
		int c_direct;
	} direct[] = {
		{
			/* top */
			.r_direct = -1,
			.c_direct = 0
		},
		{
			/* bottom */
			.r_direct = 1,
			.c_direct = 0
		},
		{
			/* left */
			.r_direct = 0,
			.c_direct = -1
		},
		{
			/* right */
			.r_direct = 0,
			.c_direct = 1
		},
		{
			/* diagonally to the top left */
			.r_direct = 1,
			.c_direct = -1
		},
		{
			/* diagonally to the bottom left */
			.r_direct = -1,
			.c_direct = -1
		},
		{
			/* diagonally to the top right */
			.r_direct = 1,
			.c_direct = 1
		},
		{
			/* diagonally to the bottom right */
			.r_direct = -1,
			.c_direct = 1
		}
	};

	for (i = 0; i < NR_DIRECT; i++) {
		if (is_blocked_road(cheese_end_line, fugitive,
				    direct[i].r_direct, direct[i].c_direct)) {
			escapable = false;
			continue;
		} else {
			escapable = true;
			break;
		}
	}

	return escapable;
}

bool is_inner_end_line(struct cell *cell, struct cell *cheese_end_line)
{
	/* Check whether this cell is inner
	 * a cheese end line. Even if a cell
	 * is one of a cheese end line, treat it
	 * as inner the line.
	 */
	if (contain(cheese_end_line, cell->row, cell->col))
		return true;

	if (is_escapable(cheese_end_line, cell))
		return false;
}

bool is_inner(struct cell *cell)
{
	int i;

	for (i = 0; i < nr_end_line_list; i++) {
		if (is_inner_end_line(cell, cheese_end_line_list[i]))
			return true;
	}

	return false;
}

int count_cheeses()
{
	int i, j;
	int nr_cheese = 0;

	for (i = 0; i < bd_row; i++) {
		for (j = 0; j < bd_col; j++) {
			if (cheese_board[i][j].has_cheese)
				nr_cheese++;
		}
	}

	return nr_cheese;
}

struct cell *collect_end_line(struct cell *cell)
{
	if (!cell->has_cheese)
		return NULL;

	if (is_inner(cell))
		return NULL;

	return cell;
}


/**
 * struct result - the result of the cheese problem.
 *
 * @nr_cheeses: the number of remaining cheeses at one hour
 *              before all cheeses are melted
 * @hour: run time until all cheeses are melted
 */
struct result {
	int nr_cheeses;
	int hour;
};

/* This function contains the logic that automatically
 * melt the end line of cheeses per one hour.
 */
struct result scan_cheese_board()
{
	int i, j;
	int bef_nr, nr_cheeses = count_cheeses();
	struct result ret;

	if (nr_cheeses == 0)
		return ret;

	do {
		for (i = 0; i < bd_row; i++) {
			for (j = 0; j < bd_col; j++)
				find_linked_cheeses(&cheese_board[i][j]);
		}
		bef_nr = nr_cheeses;
		melt_cheese_end_lines();
		nr_cheeses = count_cheeses();
	} while (ret.nr_cheeses != 0);
	return ret;
}

bool check_range(int col, int row)
{
        if (col < 3 || col > 100)
                return false;

        if (row < 3 || row > 100)
                return false;

        return true;
}

int get_values(int row, struct cell *chse_bd_row, char *input)
{
	int i;
	char *ptr, *arg;

        ptr = strdup(input);
	if (!ptr) {
                printf("%s: strdup failed\n", __func__);
                return -1;
	}

	for (i = 0; i < bd_col; i++) {
		chse_bd_row[i].row = row;
		chse_bd_row[i].col = i;
		arg = strsep(&ptr, " ");
		chse_bd_row[i].has_cheese = atoi(arg);
		chse_bd_row[i].next = NULL;
	}

	return 0;
}

void free_cheese_board()
{
	int i;

	for (i = 0; i < bd_row; i++)
		free(cheese_board[i]);
}

int main(int argc, const char **argv)
{
        char input[MAX_WIDTH];
        char *ptr, *args;
        int i, ret;
	struct result output_fmt;

        fgets(input, sizeof(input), stdin);
        ptr = strdup(input);
	if (!ptr) {
                printf("%s: strdup failed\n", __func__);
		goto err;
        }
        args = strsep(&ptr, " ");
        bd_row = atoi(args);
        bd_col = atoi(ptr);

        if (check_range(bd_col, bd_row)) {
                cheese_board = malloc(sizeof(struct cell*) * bd_row);

                for (i = 0; i < bd_row; i++) {
			struct cell *chse_bd_row = malloc(sizeof(struct cell) * bd_col);

			fgets(input, sizeof(input), stdin);
			ret = get_values(i, chse_bd_row, input);
			if (ret == -1)
				goto err;
			cheese_board[i] = chse_bd_row;
                }
        }
	output_fmt = scan_cheese_board();
	printf("%d\n%d", output_fmt.hour, output_fmt.nr_cheeses);
	return 0;

err:
	free_cheese_board();
	return -1;
}
