#include <stdio.h>
#include <regex.h>
#include <string.h>

#define ARRAY_SIZE(arr) (sizeof((arr)) / sizeof((arr)[0]))

int main()
{
	char inp[5000];
	int num1, num2;
	long mul = 0;
	regex_t preg;

	// Compile regex pattern
	if (regcomp(&preg, "mul\\([0-9]{1,3},[0-9]{1,3}\\)", REG_EXTENDED) != 0) {
		// Could handle error better but oh well
		fprintf(stderr, "Error compiling regex.\n");
		return 1;
	}

	// Read input line by line
	while(fgets(inp, sizeof(inp), stdin)){
		// Resetting the pointer
		char *s = inp;
		regmatch_t pmatch[1];
		regoff_t offset, len;

		while (regexec(&preg, s, ARRAY_SIZE(pmatch), pmatch, 0) == 0) {

			offset = pmatch[0].rm_so;
			len = pmatch[0].rm_eo - pmatch[0].rm_so;

			if (sscanf(s+offset, "mul(%i,%i)", &num1, &num2) == 2) {
				mul += num1*num2;	
			}

			s += pmatch[0].rm_eo;
		}
	}

	// Free regex resources
	regfree(&preg);
	printf("Summed instructions : %ld\n", mul);
	return 0;
}
