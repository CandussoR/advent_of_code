#include <stdio.h>

#define LEN 1000

void insertion_sort(int arr[]);
int calculate_similarity_score(int arr1[], int arr2[]);

int main()
{
	int i,j;
	int first_int;
	int second_int;
	int first_list[LEN];
	int second_list[LEN];
	int sim;

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
	
	sim = calculate_similarity_score(first_list, second_list);
	printf("%i\n", sim);

	return 0;
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
}

int calculate_similarity_score(int arr1[], int arr2[])
{
	int sim = 0;
	int i, j, count, curr;
	i = 0;
	while (i < LEN) {
		count = 0;
		curr = arr1[i];
		for (j = 0; j < LEN && (arr2[j] <= curr) ; j++)
			if (arr2[j] == curr) {
				++count;
			}
		sim += curr * count;
		++i;
	}

	return sim ;
}
