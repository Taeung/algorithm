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

struct cell{
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

struct cell *find_linked_cheeses(struct cell *cell)
{
	return cell;
}

bool is_inner(struct cell cell)
{
	/* Check whether this cell is inner
	 * each cheese end line. Even if a cell
	 * is one of cheese end line, treat it
	 * as inner the line.
	 */

	return true;
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

int main(int argc, const char **argv)
{
        char input[MAX_WIDTH];
        char *ptr, *args;
        int i, ret;

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

	return 0;

err:
	return -1;
}
