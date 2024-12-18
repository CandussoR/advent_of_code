#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

enum operation { ADD, MULTIPLY };

bool compute(long long int target, int *arr, int arr_len, enum operation *arr_ops)
{
	long long int res = arr[0];
	for (int i = 1; i < arr_len ; ++i) {
		if (arr_ops[i-1] == ADD){
			res += arr[i];
		}
		else {
			res *= arr[i];
		}

		if (res > target) {
			return false;
		}
	}

	if (res != target)
		return false;
	printf("\nTarget found !");
	return true;
}

bool combine_op(long long int target, int *arr, int arr_len)
{
	// Numbers of combinations = Numbers of choices (2)**(n-1).
	int poss = pow(2, arr_len - 1);

	for (int i = 0; i < poss ; ++i) {
		enum operation ops[arr_len - 1];
		for (int j=0 ; j < arr_len - 1; ++j) {
			ops[j] = (enum operation) ((i >> j) & 1);
		}
		if (compute(target, arr, arr_len, ops)) {
			return true;
		}
	}
	return false;
}


int main() {
	long long int target;
	char string_arr[80];
	char *token;
	long long int sum = 0;
	while(fgets(string_arr, 80, stdin)) {
		token = strtok(string_arr, ":");
		target = strtoll(token, NULL, 10);

		int converted_arr[10];
		int counter = 0;
		token = strtok(NULL, " \n");
		while (token) {
			converted_arr[counter] = atoi(token);
			++counter;
			token = strtok(NULL, " \n");
		}

		printf("Target is %lli ; line is ", target);
		for (int i =0; i < counter; ++i)
			printf("%i ", converted_arr[i]);
		printf("\n");
		if (combine_op(target, converted_arr, counter))
			sum += target;
		printf("Sum is now %lli\n\n", sum);
		}
	printf("sum is %lli", sum);
	return 0;
}
