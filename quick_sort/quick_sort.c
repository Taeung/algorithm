/*
 * Quick sort question
 *
 * Copyright (C) 2016, Taeung Song <treeze.taeung@gmail.com>
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ASCEND true
#define DESCEND false

bool sort_order;

int *merge_arr(int *left, int med, int *right,
	       int lft_len, int rgt_len)
{
	int *merged_arr = malloc(sizeof(int) * (lft_len + rgt_len));

	memcpy(left, merged_arr, lft_len);
	merged_arr[lft_len] = med;
	memcpy(right, &merged_arr[lft_len+1], rgt_len);
	free(left);
	free(right);

	return 0;
}

int split_arr(int *num_arr, int **left, int med,
	      int **right, int len)
{
	int i, lft_idx, rgt_rev_idx;
	int lft_len, rgt_len;
	int *temp;

	len = len - 1;
	temp = malloc(sizeof(int) * len);
	lft_idx = 0;
	rgt_rev_idx = len - 1;

	for (i = 0; i < len; i++) {
		int index;

		if (med < num_arr[i])
			index = sort_order == ASCEND ?
				rgt_rev_idx : lft_idx;
		else
			index = sort_order == ASCEND ?
				lft_idx : rgt_rev_idx;

		temp[index] = num_arr[i];
		index == lft_idx ? lft_idx++ : rgt_rev_idx--;
	}

	lft_len = lft_idx;
	rgt_len = len - lft_len;
	*left = malloc(sizeof(int) * lft_len);
	*right = malloc(sizeof(int) * rgt_len);

	memcpy(temp, left, lft_len);
	memcpy(&temp[lft_len], right, rgt_len);
	free(temp);

	return lft_len;
}

int *quick_sort(int *num_arr, int len)
{
	int med, lft_len, rgt_len;
	int *left, *right;
	if (len == 1)
		return num_arr;
	else if (len == 2) {
		if ((num_arr[0] < num_arr[1]) != sort_order) {
			int temp = num_arr[0];

			num_arr[0] = num_arr[1];
			num_arr[1] = temp;
		}
		return num_arr;
	}

	med = num_arr[0];

	lft_len = split_arr(num_arr, &left, med, &right, len);
	rgt_len = len - lft_len;
	free(num_arr);

	left = quick_sort(left, lft_len);
	right = quick_sort(right, rgt_len);

	return merge_arr(left, med, right, lft_len, rgt_len);
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

	for (i = 0; i < len; i++)
		printf("%d\n", num_arr[i]);

	return 0;
}
