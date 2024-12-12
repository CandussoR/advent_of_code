#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int order_string(const void *a, const void *b)
{
	return strcmp(*(char **)a, *(char **)b);
}

int main()
{
	char line[100];
	// Creating a simple array to manage the strings, and not a matrix
	char *rules[1200];
	int rules_len = 0;
	int updates_len = 0;
	bool is_rules = true;
	while(fgets(line, 100, stdin)) {
		if (is_rules) {
			if (strcmp(line, "\n") == 0) {
				is_rules = false;
				qsort(rules, rules_len, sizeof (*rules), order_string);
				for (int i = 0 ; i <= rules_len ; ++i)
					fprintf(stderr, "\t%s", rules[i]);
				continue;
			} else {
				// Allocating memory dynamically
				rules[rules_len] = malloc(strlen(line)+1);
				if (rules[rules_len] == NULL) {
					fprintf(stderr, "Memory allocation failed, exiting :(");
					return 2;
				}
				strncpy(rules[rules_len], line, strlen(line)+1);
			}
			++rules_len;	
			continue;
		}
	}

	// for line
	// begin at end of line
	// tokenize to get a number and the next
	// check if n|n-1 in rules
	// 	if found break and move on to the next line
	// 	if not found and strcomp > 0
	// 		n = n-1
	// 		tokenize new n
	// if nothing is found
	// 	get the middle number
	fprintf(stderr, "Size of rules ? %li\n", sizeof(rules));
	for (int i = 0; i < rules_len; ++i) {
		free(rules[i]);
	}
	fprintf(stderr, "Rules : %i ; Updates : %i", rules_len, updates_len);

	return 0;
}
