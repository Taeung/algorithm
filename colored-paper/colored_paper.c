/*
 * Colored paper question
 *
 * Copyright (C) 2016, Taeung Song <treeze.taeung@gmail.com>
 *
 */
#include <stdio.h>
#include <stdbool.h>

struct paper_group {
	unsigned int paper[4];
};

void grouping_papers(unsigned int len, int **papers_list,
		    int line_num, struct paper_group *row)
{
	/* Reading two line, group each paper
	 * following row and column.
	 */
}

void  parse_papers(unsigned int len, int **papers_list)
{
}

bool check_range(int len)
{
	if (len < 2 || len > 128)
		return false;

	while (len != 0) {
		len = len%2;
		if (len == 1)
			return false;
	}

	return true;
}

int main(int argc, const char **argv)
{
	return 0;
}
