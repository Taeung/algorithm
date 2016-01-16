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

#define MAX_WIDTH 512
#define WHITE 0
#define BLUE 1

struct paper_group {
	unsigned int paper[4];
};

unsigned int white;
unsigned int blue;

int count_papers(int len, struct paper_group *g_paper)
{
	int b, w, skip;

	b = w = skip = 0;
	for (int i = 0; i < 4; i++) {
		int paper = g_paper->paper[i];

		if (paper == BLUE)
			b++;
		else if (paper == WHITE)
			w++;
		else
			skip++;
	}

	if (w == 4) {
		/* If current length is 1, it is the last. */
		if (len == 1)
			white++;
		return WHITE;
	} else if (b == 4) {
		if (len == 1)
			blue++;
		return BLUE;
	} else if (skip == 4)
		return -1;

	blue += b;
	white += w;

	return -1;
}

void grouping_papers(unsigned int len, int **papers_list,
		    int line_num, struct paper_group *row)
{
	/* Reading two line, group each paper
	 * following row and column.
	 */
	for (int i = 0; i < 2; i++) {
		int *papers = papers_list[line_num++];
		int index = 0;

		for (int j = 0; j < len; j++) {
			row[j].paper[i*2] = papers[index++];
			row[j].paper[i*2+1] = papers[index++];
		}
		free(papers);
	}
}

void  parse_papers(unsigned int len, int **papers_list)
{
	/* Grouping and count papers */
	struct paper_group *g_papers;
	int line_num = 0;
	int *next_papers;
	int **next_papers_list;

	len = len/2;
	next_papers_list = (int **)malloc(sizeof(int *) * len);

	for (int i = 0; i < len; i++) {
		struct paper_group *row =
			(struct paper_group *)malloc(sizeof(struct paper_group) * len);

		/* A row per two line */
		grouping_papers(len, papers_list, line_num, row);
		line_num += 2;

		next_papers = (int *)malloc(sizeof(int) * len);
		for (int j = 0; j < len; j++)
			next_papers[j] = count_papers(len, &row[j]);
		next_papers_list[i] = next_papers;
		free(row);
	}
	free(papers_list);

	if (len == 1)
		return;
	else
		parse_papers(len, next_papers_list);
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
	printf("%d", blue);
	return 0;
}
