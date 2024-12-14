#include "hashset.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int order_string(const void *a, const void *b)
{
	return strcmp(a, b);
}

int parse_line_tokens(char *line, int *arr)
{
	int token_count = 0;
	// split line according to separators
	char *token = strtok(line, ",\n");

	while (token != NULL) {
		// converts token into int and mutating the array
		*arr = atoi(token);
		++arr;
		++token_count;
		// continuing to tokenize the same string, must pass NULL
		token = strtok(NULL, ",\n");
	}

	return token_count;
}


bool is_correctly_ordered(int *arr, int count, hashset_t *hashset)
{
	for (int i = 0 ; i < count ; ++i) {
		for (int j = i + 1 ; j <= count ; ++j) {
			char needle[10];
			sprintf(needle, "%d|%d\n", arr[j], arr[i]);
			// if we found the value, then the rule exists
			// and numbers should be the other way round
			if (hs_get(hashset, needle))
				return false;
		}
	}
	return true;
}


void order_array(int *arr, int count, int *add, hashset_t *hashset)
{
	// no for loop because we don't always increment i
	int i = 0;
	while (i < count) {
		int j = i + 1;
		while (j < count) {
			char needle[10];
			sprintf(needle, "%d|%d\n", arr[j], arr[i]);
			// No rule against the order ? All good.
			if (!hs_get(hashset, needle)) {
				++j;
				continue;
			}
			// else we swap and do iteration for new value of arr[i]
			int tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
		}
		++i;
	}
}

void part1(int *arr, int count, int *add, hashset_t *hashset) {
	bool correct = is_correctly_ordered(arr, count, hashset);
	if (correct) {
		*add += arr[count/2];
	}
}

void part2(int *arr, int count, int *add, hashset_t *hashset)
{
	if (is_correctly_ordered(arr, count, hashset))
		return;
	order_array(arr, count, add, hashset);
	*add += arr[count/2];
}

int main()
{
	hashset_t *hashset = create_hashset();
	char line[100];
	int rules_len = 0;
	bool is_rules = true;
	int correct_add = 0;
	int incorrect_add = 0;
	while(fgets(line, 100, stdin)) {
		if (is_rules) {
			if (strcmp(line, "\n") == 0) {
				is_rules = false;
				continue;
			} else {
				hs_set(hashset, line);
			}
			++rules_len;	
			continue;
		}
		//printf("line is %s\n", line);
		// Filling buffer with dynamic size with memset
		int arr[strlen(line)];
		memset(arr, -1, strlen(line)*sizeof(int));
		// tokenize to get a number and the next
		int count = parse_line_tokens(line, arr);
		part1(arr, count, &correct_add, hashset);
		part2(arr, count, &incorrect_add, hashset);
		}

	printf("Added is %i\n", correct_add);
	printf("Added is %i\n", incorrect_add);
	return 0;
}
