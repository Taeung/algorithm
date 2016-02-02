/*
 * Quick sort question
 *
 * Copyright (C) 2016, Taeung Song <treeze.taeung@gmail.com>
 *
 */
#include <stdio.h>
#include <stdlib.h>

void quick_sort(int num[])
{
}

int main(int argc, const char **argv)
{
	int *num_arr;
	unsigned int nr, order, i;

	scanf("%d", &nr);
	num_arr = malloc(sizeof(int) * nr);
	scanf("%d", &order);

	for (i = 0; i < nr; i++)
		scanf("%d", &num_arr[i]);

	quick_sort(num_arr);

	return 0;
}
