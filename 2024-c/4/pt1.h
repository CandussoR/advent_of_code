#include <stdbool.h>

void search_horizontal(char *needle, bool reverse, matrix *m, int *word_count);
void search_vertical(char *needle, bool reverse, matrix *m, int *word_count);
void search_diagonal_left(char *needle, bool reverse, matrix *m, int *word_count);
void search_diagonal_right(char *needle, bool reverse, matrix *m, int *word_count);
void scan_for_needle(char *needle, matrix *m, int *word_count);
void search(char *needle, bool reverse, matrix *m, int *word_count);


