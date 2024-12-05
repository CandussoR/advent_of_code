#include <stdio.h>

#define LEN 1000

void insertion_sort(int arr[]);

int main()
{
	int i,j;
	int first_int;
	int second_int;
	int first_list[LEN];
	int second_list[LEN];

	i=0;
	/* parsing input file */
	while(scanf("%i   %i", &first_int, &second_int) == 2) {
		first_list[i] = first_int;
		second_list[i] = second_int;
		++i;
	}

	/* order the arrays to facilitate the difference between the two */
	/* let's do it the easy and slow way with a bubble sort to begin with */
	insertion_sort(first_list);
	insertion_sort(second_list); 
	
	int sum = 0;
	for (j = 0; j < LEN ; ++j) {
		if (first_list[j] > second_list[j])
			sum += first_list[j] - second_list[j];
		else
			sum += second_list[j] - first_list[j];
	}
	printf("%i", sum);
}


void insertion_sort(int arr[])
{
        int i, j;
        int lowest_val_index;
        i = 0;

        while (i < LEN) {
                lowest_val_index = i;
                for (j = i+1 ; j < LEN ; ++j) {
                        if (arr[j] < arr[lowest_val_index]) {
                                lowest_val_index = j;
                        }
                }
                if (lowest_val_index != i) {
                        int tmp = arr[i];
                        arr[i] = arr[lowest_val_index];
                        arr[lowest_val_index] = tmp;
                }
                ++i;
        }

	/*
	for (i = 0; i < 10; ++i) {
		printf("%i ", arr[i]);
	}
	printf("\n");
	*/
}
