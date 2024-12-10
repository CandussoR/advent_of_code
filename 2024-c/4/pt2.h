#include <stdbool.h>

bool search_diagonal_left(char *needle, bool reverse, matrix *m);
bool search_diagonal_right(char *needle, bool reverse, matrix *m);
void scan_for_needle(char *needle, matrix *m, int *word_count);
void search(char *needle, bool reverse, matrix *m, int *word_count);
void search_cross(char *needle, bool reverse, matrix *m, int *count);
