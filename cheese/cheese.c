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
	bool has_cheese;
	struct cell *next;
};

/* The cheese board has all cheese cell*/
struct cell **cheese_board;

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

int get_values(int nr, struct cell *chse_bd_row, char *input)
{
	int i;
	char *ptr, *arg;

        ptr = strdup(input);
	if (!ptr) {
                printf("%s: strdup failed\n", __func__);
                return -1;
	}

	for (i = 0; i < nr; i++) {
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
        int i, ret, col, row;

        fgets(input, sizeof(input), stdin);
        ptr = strdup(input);
	if (!ptr) {
                printf("%s: strdup failed\n", __func__);
		goto err;
        }
        args = strsep(&ptr, " ");
        row = atoi(args);
        col = atoi(ptr);

        if (check_range(col, row)) {
                cheese_board = malloc(sizeof(struct cell*) * row);

                for (i = 0; i < row; i++) {
			struct cell *chse_bd_row = malloc(sizeof(struct cell) * col);

			fgets(input, sizeof(input), stdin);
			ret = get_values(col, chse_bd_row, input);
			if (ret == -1)
				goto err;
			cheese_board[i] = chse_bd_row;
                }
        }

	return 0;

err:
	return -1;
}
