#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define LEN 10

void parse_line_tokens(char line[], int level[]);
bool level_is_safe(int level[]);

int main()
{
	char line[100];
	int level[LEN];
	int safe_levels = 0;

	while(fgets(line, sizeof(line), stdin)) {
		
		// filling array with -1 for later upper bound
		for (int i=0; i < LEN ; ++i)
			level[i] = -1;

		parse_line_tokens(line, level);

		if (level_is_safe(level))
			++safe_levels;
	}

	printf("%i", safe_levels);

	return 0;
}

void parse_line_tokens(char line[], int level[])
{
		int i = 0;
		// split line according to separators
		char *token = strtok(line, " \n");
		while (token != NULL) {
			// converts token into int and mutating the array
			level[i] = atoi(token);
			++i;
			// continuing to tokenize the same string, must pass NULL
			token = strtok(NULL, " \n");
		}
}

bool level_is_safe(int level[])
{
	bool has_sense = false;
	bool is_incr = false;
	for (int i = 0 ; level[i+1] != -1 ; ++i) {
		int dif = level[i+1] - level[i];

		//for strong knees only
		if (!has_sense) {
			has_sense = true;
			if (dif > 0)
				is_incr = true;
		}

		if (is_incr) {
			if ((level[i+1] < level[i]) || ((dif < 1) || (dif > 3)))
				return false;
		}
		else {
			if ((level[i+1] > level[i]) || ((dif < -3) || (dif > -1)))
				return false;
		}
	}
	return true;
}
				
