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
	unsigned int nr_cases = wgt/jewelry->wgt;
	unsigned int maxprice = 0;

	for (int i = 1; i <= nr_cases; i++) {
		unsigned int price, rest_wgt;

		rest_wgt = wgt - (i * jewelry->wgt);
		price = (i * jewelry->price) + knapsack_list[rest_wgt].maxprice;
		if (maxprice < price)
			maxprice = price;
	}

	return maxprice;
}

void pack_knapsack(struct jewelry *jewelry)
{
	/* Case by case pack knapsack following maximum
	 * price per limited weight.
	 */
	if (limited_wgt < jewelry->wgt)
		return;

	for (int wgt = 0; wgt <= limited_wgt; wgt++) {
		if (jewelry->wgt <= wgt) {
			unsigned int maxprice = get_cond_maxprice(wgt, jewelry);

			if (knapsack_list[wgt].maxprice < maxprice)
				knapsack_list[wgt].maxprice = maxprice;
		}
	}
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
	struct jewelry *jewels;
	char input[MAX_INPUT];
	unsigned int nr_jewels;

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

	for (int i = 0; i <= limited_wgt; i++)
		knapsack_list[i].maxprice = 0;

	for (int i = 0; i < nr_jewels; i++)
		pack_knapsack(&jewels[i]);

	printf("%d", knapsack_list[limited_wgt].maxprice);
	free(jewels);
	free(knapsack_list);
	return 0;
}
