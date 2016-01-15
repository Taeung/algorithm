/*
 * Colored paper question
 *
 * Copyright (C) 2016, Taeung Song <treeze.taeung@gmail.com>
 *
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WIDTH 256

struct paper_group {
	unsigned int paper[4];
};

unsigned int white;
unsigned int blue;

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
	char input[MAX_WIDTH];
	int len;

	fgets(input, sizeof(input), stdin);
	len = atoi(input);

	if (check_range(len)) {
		int **papers_list = (int **)malloc(sizeof(int *) * len);

		for (int i = 0; i < len; i++) {
			int end, index = 0;
			int *row = (int *)malloc(sizeof(int) * len);

			fgets(input, MAX_WIDTH, stdin);
			end = strlen(input);

			for (int j = 0; j < end; j++) {
				char ch = input[j];
				if (ch == '1' || ch == '0')
					row[index++] = ch - '0';
			}

			if (index != len) {
				printf("Error: wrong length of one side "
				       "(N = %d).\n", len);
				free(row);
				for (int j; j < len; j++)
					free(papers_list[j]);
				free(papers_list);
				return -1;
			}
			papers_list[i] = row;
		}
		parse_papers(len, papers_list);
	} else
		printf("\nError: wrong range of length.\n");

	/* The numbers of white and blue paper */
	printf("%d\n", white);
	printf("%d\n", blue);
	return 0;
}
