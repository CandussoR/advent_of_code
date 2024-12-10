/*
 * Program that gets all the occurences of the needle (MAS here)
 * that forms a cross, hence cross diagonally in the middle,
 * in an input with random letters.
 * with input.txt, should return 1807.
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "pt2.h"

typedef struct {
	char matrix [150][150];
	unsigned char row;
	unsigned char col;
	unsigned char depth;
} matrix;

int main()
{
	matrix m;
	m.depth = 0;
	char line[150];
	int word_count = 0;
	char *needle = "MAS";
	
	while (scanf("%149s", line) == 1) {
		strncpy(m.matrix[m.depth], line, sizeof(line));
		++m.depth;
	}

	scan_for_needle(needle, &m, &word_count);

	printf("Number of %s : %i\n", needle, word_count);
	return 0;
}


void scan_for_needle(char *needle, matrix *m, int *word_count)
{
	bool reverse = true;
	for (m->row = 0 ; m->row < m->depth ; ++m->row) {
		for (m->col = 0 ; m->col <= strlen(m->matrix[m->row]) ; ++m->col) {
			if (m->matrix[m->row][m->col] == needle[0])
				search(needle, !reverse, m, word_count);
			else if (m->matrix[m->row][m->col] == needle[strlen(needle)-1])
				search(needle, reverse, m, word_count);
		}
	}
}

void search(char *needle, bool reverse, matrix *m, int *word_count)
{
	int n_len = strlen(needle);
	if (((m->row + n_len - 1) <= m->depth) 
		&& ((m->col + n_len - 1) <= strlen(m->matrix[m->row]))) {
		search_cross(needle, reverse, m, word_count);
	}
}

void search_cross(char *needle, bool reverse, matrix *m, int *count)
{
	if (strlen(needle) % 2 == 0) {
		// Don't care for the puzzle, might be interesting to do later
		return;
	}

	int middle = strlen(needle) / 2;
	if (m->matrix[m->row+1][m->col+1] != needle[middle])
		return;
	if (!search_diagonal_right(needle, reverse, m))
		return;

	// Making sure we search the good order
	int other_reverse = false;
	if (m->matrix[m->row][m->col+2] == needle[0])
		other_reverse = false;
	else if (m->matrix[m->row][m->col+2] == needle[strlen(needle)-1])
		other_reverse = true;
	else 
		return;
	

	m->col += 2;
	if (search_diagonal_left(needle, other_reverse, m))
		++(*count);
	m->col -= 2;
}

bool search_diagonal_left(char *needle, bool reverse, matrix *m)
{
	int len = strlen(needle);
	for (int i = 1; i < len ; ++i) {
		if (reverse && m->matrix[m->row + i][m->col - i] == needle[len-i-1]){
			continue;
		}
		else if (!reverse && m->matrix[m->row + i][m->col - i] == needle[i]){
			continue;	
		}
		return false;
	} 
	return true;
}

bool search_diagonal_right(char *needle, bool reverse, matrix *m)
{
	int len = strlen(needle);
	for (int i = 1; i < len ; ++i) {
		if (reverse && m->matrix[m->row + i][m->col + i] == needle[len-i-1]){
				continue;
		}
		else if (!reverse && m->matrix[m->row + i][m->col + i] == needle[i]){
			continue;	
		}
		return false;
	} 
	return true;
}
