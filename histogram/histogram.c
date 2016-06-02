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
};

struct hist_block *histogram__new(char *input)
{
	int i, end, nr;
	char *arg;
	struct hist_block *histogram;
	char *ptr = strdup(input);

	if (!ptr) {
		printf("%s: strdup failed\n", __func__);
		exit(1);
	}

	if (strlen(ptr) == 1 && atoi(ptr) == 0)
		return NULL;

	arg = strsep(&ptr, " ");
	if (ptr == NULL) {
		printf("Error: Need a whitespace\n");
		return NULL;
	}

	nr = atoi(arg);
	histogram = malloc(sizeof(struct hist_block) * nr);

	end = nr - 1;
	for (i = 0; i < end; i++) {
		arg = strsep(&ptr, " ");
		histogram[i].height = atoi(arg);
	}

	histogram[end].height = atoi(ptr);

	return histogram;
}

int main(int argc, const char **argv)
{
	int i, biggest_area_size = 0;
	char input[MAX_INPUT];
	struct hist_block *histogram;

	fgets(input, sizeof(input), stdin);

	histogram = histogram__new(input);
	if (histogram == NULL)
		goto out;

	/* fall through */
out:
	free(histogram);
	printf("%d\n", biggest_area_size);
	return 0;
}
