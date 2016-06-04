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

struct histogram {
	int nr;
	struct hist_block *blocks;
};

int get_groups_maximum(int nr, int *group_values)
{
	int i, max_value = 0;

	for (i = 0; i < nr; i++) {
		if (max_value < group_values[i])
			max_value = group_values[i];
	}

	return max_value;
}

int get_max_area_from_group(int nr, struct hist_block group[])
{
	int i, min_height = group[0].height;

	for (i = 1; i < nr; i++) {
		if (min_height > group[i].height)
			min_height = group[i].height;
	}

	return min_height * nr;
}

struct hist_block **make_groups(int nr, struct hist_block **groups)
{
	return groups;
}

int get_max_area(struct histogram *histogram)
{
	int max_area = 0;

	return max_area;
}

struct histogram *histogram__new(char *input)
{
	int i, end, nr;
	char *arg;
	struct histogram *histogram;
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
	histogram = malloc(sizeof(struct histogram));
	histogram->nr = nr;
	histogram->blocks = malloc(sizeof(struct hist_block) * nr);

	end = nr - 1;
	for (i = 0; i < end; i++) {
		arg = strsep(&ptr, " ");
		histogram->blocks[i].height = atoi(arg);
	}

	histogram->blocks[end].height = atoi(ptr);

	return histogram;
}

int main(int argc, const char **argv)
{
	int i, biggest_area_size = 0;
	char input[MAX_INPUT];
	struct histogram *histogram;

	fgets(input, sizeof(input), stdin);

	histogram = histogram__new(input);
	if (histogram == NULL)
		goto out;

	biggest_area_size = get_max_area(histogram);
out:
	free(histogram->blocks);
	free(histogram);
	printf("%d\n", biggest_area_size);
	return 0;
}
