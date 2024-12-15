#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 150

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

typedef struct {
	int x;
	int y;
	enum Direction dir;
} pos;

void set_guard_pos(char **map, const int height, pos *p)
{
	pos p2 = *p;
	for (p2.x = 0 ; p2.x < height ; ++p2.x) {
		for (p2.y = 0 ; p2.y < strlen(map[p2.x]) ; ++p2.y) {
			if (map[p2.x][p2.y] == '^') {
				p->x = p2.x;
				p->y = p2.y;
				return;
			}
		}
	}
}

void switch_direction(pos *p) {
	switch (p->dir) {
		case UP:
			p->dir = RIGHT;
			break;
		case RIGHT:
			p->dir = DOWN;
			break;
		case DOWN:
			p->dir = LEFT;
			break;
		case LEFT:
			p->dir = UP;
			break;
	}
}

void update_coordinates(pos *p) {
	switch (p->dir) {
		case UP:
			--p->x;
			break;
		case RIGHT:
			++p->y;
			break;
		case DOWN:
			++p->x;
			break;
		case LEFT:
			--p->y;
			break;
	}
}

int write_patrol(char **map, const int limit_height, pos *p) {
	int count = 0;
	enum Direction dir = UP;
	set_guard_pos(map, limit_height, p);
	if (p->x == -1 && p->y == -1) {
		printf("Guard not found.");
		return -1;
	}

	pos last = *p;
	while ((p->x >= 0 && p->x < limit_height) && 
		(p->y >= 0 && p->y < strlen(map[p->x]))) {
		if (map[p->x][p->y] == '#') {
			switch_direction(p);
			p->x = last.x;
			p->y = last.y;
		} else if (map[p->x][p->y] != 'X') {
			++count;
			map[p->x][p->y] = 'X';
		}
		last = *p;
		update_coordinates(p);
	}
	return count;
}

void free_map(char **map, int length)
{
	for (int i = 0 ; i < length ; ++i)
		free(map[i]);
	free(map);
}

int main()
{

	char line[LINE_MAX];
	int nl = 0;
	pos p = {-1, -1, UP};
	char **guard_map = malloc(LINE_MAX * sizeof(char *));
	if (!guard_map) {
		printf("Couldn't allocate memory to map\n");
		return 2;
	}

	while (scanf("%149s", line) == 1) {
		if (nl >= LINE_MAX)
			break;
		guard_map[nl] = malloc(LINE_MAX * sizeof(char));
		if (guard_map[nl])
			strncpy(guard_map[nl], line, LINE_MAX);
		++nl;
	}

	int count = write_patrol(guard_map, nl, &p);
	printf("Count is %i\n", count);
	free_map(guard_map, nl);
	return 0;
}
