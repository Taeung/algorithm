/*
 * Quick sort question
 *
 * Copyright (C) 2016, Taeung Song <treeze.taeung@gmail.com>
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ASCEND true
#define DESCEND false

bool sort_order;

int *quick_sort(int num[], int len)
{
}

int main(int argc, const char **argv)
{
	int *num_arr;
	unsigned int len, order, i;

	scanf("%d", &len);
	num_arr = malloc(sizeof(int) * len);
	scanf("%d", &order);
	sort_order = order == 0 ? ASCEND : DESCEND;

	for (i = 0; i < len; i++)
		scanf("%d", &num_arr[i]);

	num_arr = quick_sort(num_arr, len);

	return 0;
}
