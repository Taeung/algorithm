/*
 * Histogram question
 *
 * Copyright (C) 2016, Taeung Song <treeze.taeung@gmail.com>
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 1048576

struct hist_block {
	unsigned int height;
} *histogram;

unsigned int nr_block;

int get_values_from(char *input)
{
	int i, end, nr;
	char *arg;
	char *ptr = strdup(input);

	if (!ptr) {
		printf("%s: strdup failed\n", __func__);
		exit(1);
	}

	if (strlen(ptr) == 1 && atoi(ptr) == 0)
		return 0;

	arg = strsep(&ptr, " ");
	nr = atoi(arg);
	histogram = malloc(sizeof(struct hist_block) * nr);
	if (ptr == NULL) {
		printf("Error: Need a whitespace\n");
		return -1;
	}

	end = nr - 1;
	for (i = 0; i < end; i++) {
		arg = strsep(&ptr, " ");
		histogram[i].height = atoi(arg);
	}

	histogram[end].height = atoi(ptr);

	return nr;
}

int main(int argc, const char **argv)
{
	int i, biggest_area_size = 0;
	char input[MAX_INPUT];

	fgets(input, sizeof(input), stdin);

	nr_block = get_values_from(input);
	if (nr_block == 0)
		goto out;

	/* fall through */
out:
	free(histogram);
	printf("%d\n", biggest_area_size);
	return 0;
}
