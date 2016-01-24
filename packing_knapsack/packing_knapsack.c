/*
 * Packing knapsack question
 *
 * Copyright (C) 2016, Taeung Song <treeze.taeung@gmail.com>
 *
 */
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INPUT 16

struct knapsack {
	unsigned int maxprice;
} *knapsack_list;

struct jewelry {
	unsigned int wgt;
	unsigned int price;
};

unsigned int limited_wgt;

unsigned int get_cond_maxprice(int wgt, struct jewelry *jewelry)
{
	/* Get maximum price based on a specific weight
	 * following a specific jewelry.
	 */
}

void pack_knapsack(struct jewelry *jewelry)
{
	/* Case by case pack knapsack following maximum
	 * price per limited weight.
	 */
}

bool get_values_from(char *input, unsigned int *val1, unsigned int *val2)
{
	char *ptr = input;

	*val1 = atoi(strsep(&ptr, " "));
	if (ptr == NULL) {
		printf("Error: Need a whitespace\n");
		return false;
	}

	*val2 = atoi(ptr);

	if (*val1 == 0 || *val2 == 0) {
		printf("Error: Input have to contain only numbers\n");
		return false;
	}

	return true;
}

int main(int argc, const char **argv)
{
	char input[MAX_INPUT];
	char *ptr = input;
	int nr_jewels, limited_wgt;
	struct jewelry *jewels;
	struct knapsack *knapsack_list;

	fgets(input, sizeof(input), stdin);
	if (get_values_from(input, &nr_jewels, &limited_wgt) == false)
		return -1;

	jewels = malloc(sizeof(struct jewelry) * nr_jewels);
	for (int i = 0; i < nr_jewels; i++) {
		bool ret;

		fgets(input, sizeof(input), stdin);
		ret = get_values_from(input, &jewels[i].wgt,
				      &jewels[i].price);
		if (ret == false)
			return -1;
	}

	/* from 0 to last limited weight */
	knapsack_list = malloc(sizeof(struct knapsack) * (limited_wgt + 1));

	for (int i = 0; i < nr_jewels; i++)
		pack_knapsack(&jewels[i]);

	printf("%d\n", knapsack_list[limited_wgt].maxprice);
	free(jewels);
	free(knapsack_list);
	return 0;
}
