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

struct hist_block **make_groups(struct histogram *histogram, int per_nr)
{
	int i, j, nr_groups = histogram->nr - per_nr + 1;
	struct hist_block **groups = malloc(sizeof(struct hist_block *) * nr_groups);

	for (i = 0; i < nr_groups; i++) {
		int index = 0;
		struct hist_block *group = malloc(sizeof(struct hist_block *) * per_nr);

		for (j = i; j < i + per_nr; j++)
			group[index++] = histogram->blocks[j];

		groups[i] = group;
	}
	return groups;
}

void remove_groups(int nr, struct hist_block **groups)
{
	int i, j;

	if (groups == NULL)
		return;

	for (i = 0; i < nr; i++)
		free(groups[i]);

	free(groups);
}

int get_max_area(struct histogram *histogram)
{
	int i, j, max_area = 0;
	int nr_blocks = histogram->nr;
	struct hist_block *blocks = histogram->blocks;

	for (i = 0; i < nr_blocks; i++) {
		int hgt = blocks[i].height;

		if (max_area < hgt)
			max_area = hgt;
	}

	for (i = 2; i <= nr_blocks; i++) {
		int max_groups = 0;
		int nr_groups = nr_blocks - i + 1;
		struct hist_block **groups = make_groups(histogram, i);
		int *group_values = malloc(sizeof(int) * nr_groups);

		for (j = 0; j < nr_groups; j++)
			group_values[j] = get_max_area_from_group(i, groups[j]);

		max_groups = get_groups_maximum(nr_groups, group_values);
		if (max_area < max_groups)
			max_area = max_groups;
		remove_groups(nr_groups, groups);
	}
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

void histogram__delete(struct histogram *histogram)
{
	if (histogram == NULL)
		return;

	free(histogram->blocks);
	free(histogram);
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
	histogram__delete(histogram);
	printf("%d\n", biggest_area_size);
	return 0;
}
