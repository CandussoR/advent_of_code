/*
 * Program that gets all the occurences of the needle (XMAS here)
 * horizontally, vertically, diagonally, forward and backwardi
 * in an input with random letters.
 * Should return 2406 with input.txt
 */

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "pt1.h"

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
	char *needle = "XMAS";
	
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
	
	if ((m->col + n_len) <= strlen(m->matrix[m->row]))
		search_horizontal(needle, reverse, m, word_count);
	if ((m->row + n_len) <= m->depth) {
		search_vertical(needle, reverse, m, word_count);
		if ((m->col - (n_len - 1)) >= 0) 
			search_diagonal_left(needle, reverse, m, word_count);
		if ((m->col + (n_len - 1)) <= strlen(m->matrix[m->row])) 
			search_diagonal_right(needle, reverse, m, word_count);
	}
}

void search_horizontal(char *needle, bool reverse, matrix *m, int *word_count)
{
	int len = strlen(needle);
	for (int i = 1; i < len ; ++i) {
		if (reverse && m->matrix[m->row][m->col + i] == needle[len-i-1]){
				continue;
		}
		else if (!reverse && m->matrix[m->row][m->col + i] == needle[i]){
			continue;	
		}
		return;
	} 
	++(*word_count);
}


void search_vertical(char *needle, bool reverse, matrix *m, int *word_count)
{
	int len = strlen(needle);
	for (int i = 1; i < len ; ++i) {
		if (reverse && m->matrix[m->row + i][m->col] == needle[len-i-1]){
				continue;
		}
		else if (!reverse && m->matrix[m->row + i][m->col] == needle[i]){
			continue;	
		}
		return;
	} 
	++(*word_count);
}

void search_diagonal_left(char *needle, bool reverse, matrix *m, int *word_count)
{
	int len = strlen(needle);
	for (int i = 1; i < len ; ++i) {
		if (reverse && m->matrix[m->row + i][m->col - i] == needle[len-i-1]){
			continue;
		}
		else if (!reverse && m->matrix[m->row + i][m->col - i] == needle[i]){
			continue;	
		}
		return;
	} 
	++(*word_count);
}

void search_diagonal_right(char *needle, bool reverse, matrix *m, int *word_count)
{
	int len = strlen(needle);
	for (int i = 1; i < len ; ++i) {
		if (reverse && m->matrix[m->row + i][m->col + i] == needle[len-i-1]){
				continue;
		}
		else if (!reverse && m->matrix[m->row + i][m->col + i] == needle[i]){
			continue;	
		}
		return;
	} 
	++(*word_count);
}