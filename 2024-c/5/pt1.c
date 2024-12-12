#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int order_string(const void *a, const void *b)
{
	// thank you stack overflow but why does this work ??
	//fprintf(stderr, "\tcomparing %s and %s, a is %s and b is %s, finding %i\n", (char *)a, (char *)b, a, b, strcmp(a,b));
	return strcmp(a, b);
	
}

int main()
{
	char line[100];
	char rules[1200][10];
	int rules_len = 0;
	int updates_len = 0;
	bool is_rules = true;
	while(fgets(line, 100, stdin)) {
		if (is_rules) {
			if (strcmp(line, "\n") == 0) {
				is_rules = false;
				/*
				fprintf(stderr, "Printing the array before qsort\n");
				for (int i = 0 ; i <= 5 ; ++i)
					fprintf(stderr, "\t%s", rules[i]);
				fprintf(stderr, "%li is sizeof *rules", sizeof(*rules));
				*/
				// Sorting to avoid searching the array all the time
				qsort(rules, rules_len, sizeof (*rules), order_string);
				fprintf(stderr, "After qsort : ");
				for (int i = 0 ; i <= rules_len ; ++i)
					fprintf(stderr, "\t%s", rules[i]);
				continue;
			} else {
				/*line[strcspn(line, "\n")] = 0;*/
				strncpy(rules[rules_len], line, sizeof(rules[0]));
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

	fprintf(stderr, "Size of rules ? %li\n", sizeof(rules) * sizeof(rules[0]));
	fprintf(stderr, "Rules : %i ; Updates : %i", rules_len, updates_len);

	return 0;
}
